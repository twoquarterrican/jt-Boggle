#include "bogglegameplay.h"
//#include "sleep.h"

#include <QDebug>

//bool operator<(const BoardLocation &a, const BoardLocation &b) {
//	return ((a.row < b.row) || ((a.row == b.row) && (a.col < b.col)));
//}
bool operator ==(const BoardLocation &a, const BoardLocation &b) {
    return (a.row == b.row) && (a.col == b.col);
}
const int MAXROWS=100000;
uint qHash(const BoardLocation &bl, uint random) {
    return bl.row + MAXROWS*bl.col + random*0;
}

BoggleGamePlay::BoggleGamePlay(QObject *parent)
  :QObject(parent)
{
    currentPlayer = NONE;
	currentBoardSize = kDefaultBoardSize;
    bogglewindow = new BoggleWindow();
	//window to game logic connections
	connect(bogglewindow, SIGNAL(signalBoardSizeChanged(BoardSize)),
			this, SLOT(boardSizeChanged(BoardSize)));
	connect(bogglewindow, SIGNAL(signalShuffleBoard()),
			this, SLOT(shuffleBoard()));
	connect(bogglewindow, SIGNAL(signalHumanDone()),
			this, SLOT(computerTurnBegin()));
	connect(bogglewindow, SIGNAL(signalTextEntrySubmitted(QLineEdit *)),
			this, SLOT(processTextEntry(QLineEdit *)));
	//game logic to window connections
	connect(this, SIGNAL(signalHumanTurnBegin()),
			bogglewindow, SLOT(humanTurnBegin()));
	connect(this, SIGNAL(signalComputerTurnBegin()),
			bogglewindow, SLOT(computerTurnBegin()));
	connect(this, SIGNAL(signalComputerTurnEnd()),
			bogglewindow, SLOT(computerTurnEnd()));
	//showing bogglewindow before shuffling board makes the board not get 
	//cut off for some reason
    bogglewindow->show();
	shuffleBoard();
    englishLex.addFromFile(":/wordlists/dict.txt");
    //Lexicon e("dict.txt");
}

BoggleGamePlay::~BoggleGamePlay()
{
}

void BoggleGamePlay::humanTurnBegin() {
	//the window needs to disable board size changing while the human
	//is entering words, it must listen to this signal to do so
	emit signalHumanTurnBegin();
	//assume this is only called if currentPlayer is NONE
	currentPlayer=HUMAN;
	//make sure scores are reset
	scores[HUMAN] = scores[COMPUTER] = 0;
	bogglewindow->updateScore(0, HUMAN);
	bogglewindow->updateScore(0, COMPUTER);
	//reset words used
	wordsUsed.clear();
	//reset highlighting
	bogglewindow->turnOffHighlighting();
}

void BoggleGamePlay::computerTurnBegin() {
	emit signalComputerTurnBegin();
	currentPlayer=COMPUTER;
	computerFindWords();
	computerTurnEnd();
}

void BoggleGamePlay::computerTurnEnd() {
	emit signalComputerTurnEnd();
	currentPlayer = NONE;
	bogglewindow->startTestComputerAnimation();
	displayResults();
}

void BoggleGamePlay::displayResults() {
	QString msg;
	int sh = scores[HUMAN];
	int sc = scores[COMPUTER];
	if (sh < sc) {
		msg = QString("Nice try but I, the computer, ") + 
				QString("beat you by %1 points.").arg(sc-sh);
	} else if (sh == sc) {
		msg = "You tied me!! I can't believe it!";
	} else if (sh > sc) {
		msg = QString("You won!?? Did you cheat?  I thought I ") + 
			QString("found every word possible");
	} else {
		msg = QString("Okay we didn't tie, but neither of us ") + 
			QString("won, I am confused.");
	}
	notify(msg);
}

void BoggleGamePlay::processTextEntry(QLineEdit *textEntry) {
	if (currentPlayer == NONE) {
		//humanTurnBegin() takes care of signaling window
		humanTurnBegin();
	}
	if (currentPlayer == HUMAN) {
		QString text = textEntry->text();
		if (text == "") return;
		checkWord(text, HUMAN, wordsUsed);
		textEntry->setText("");
	}
}

int scoreWord(const QString& word) {
	if (word.length() == 3) return 1;
	if (word.length() == 4) return 1;
	if (word.length() == 5) return 2;
	if (word.length() == 6) return 3;
	if (word.length() == 7) return 5;
	if (word.length() >= 8) return 11;
}

void BoggleGamePlay::checkWord(
		QString word, Player player, QSet<QString> &wordsUsed
		) {
	word = word.toUpper();
	QString msgWordTooShort = "";
	QString msgWordNotAWord = "";
	QString msgWordUsed = "";
	//only display messages for human player
	if (player == HUMAN) {
		msgWordTooShort = "I am sorry, \"" + word +
			"\" is too short. Please enter a word of size at least 3\n";
		msgWordNotAWord = "I am sorry, \"" + word +
			"\" is not a word in my lexicon.\n";
		msgWordUsed = "You have already used the word \"" + word + "\"\n";
	}
	if (word.length() < 3) {
		notify(msgWordTooShort);
	} else if (!englishLex.contains(word)) {
		notify(msgWordNotAWord);
	} else if (wordsUsed.contains(word)) {
		notify(msgWordUsed);
	} else if (player == HUMAN && !boggleContains(word)) {
		//because of short-circuit evaluation, boggleContains() is only called
		//if player == HUMAN
		notify("\"" + word + "\" is not on the boggle board.\n");
	} else {
		//if we made it to here, the word counts toward the player's score
		wordsUsed.insert(word);
		bogglewindow->recordWordForPlayer(word,currentPlayer);
		scores[currentPlayer] += scoreWord(word);
		bogglewindow->updateScore(scores[currentPlayer], currentPlayer);
	}
}

void BoggleGamePlay::notify(const QString &message) {
	bogglewindow->notify(message);
}

bool BoggleGamePlay::inBounds(int row, int col) {
	return (0 <= row) && (row < currentBoardSize) && 
		(0 <= col) && (col < currentBoardSize);
}

int BoggleGamePlay::indexOf(int row, int col) {
	return row*currentBoardSize + col;
}

const QString BoggleGamePlay::letterAt(int row, int col) {
	if (currentBoardSize == SMALL) return lettersSmall[indexOf(row,col)];
	if (currentBoardSize == LARGE) return lettersLarge[indexOf(row,col)];
	return "";
}

bool BoggleGamePlay::boggleContains(
		const QString &uCaseWord,
		QSet<BoardLocation> &cubesWithPartOfWord,
		BoardLocation &lastLocation,
		int pos) {
	////cout << "top of recursive boggleContains function with pos = " << pos << endl;
	if(pos >= uCaseWord.length()) return true;
	//iterate over neighbors of last board location 
	for (int deltaRow = -1; deltaRow < 2; ++deltaRow) {
		for (int deltaCol = -1; deltaCol < 2; ++deltaCol) {
			//a neighbor must distinct from last location
			if (deltaRow == 0 && deltaCol == 0) continue;
			//top() is last location in stack
			int row = lastLocation.row + deltaRow;
			int col = lastLocation.col + deltaCol;
			//a neighbor must be in bounds
			if (!inBounds(row, col)) continue;
			BoardLocation thisLocation = {row, col};
			//we only look at neighbors we have not visited before
			if (cubesWithPartOfWord.contains(thisLocation)) continue;
			//we also need this location to have the correct letter
			if (letterAt(row,col) != uCaseWord[pos]) continue;
			//now we know this location contains the letter in position pos of the given word
			cubesWithPartOfWord.insert(thisLocation);
			//make search visible
			highlightCube(row,col,true);
			//qSleep(kPauseTime);
			//the recursive call
			if (boggleContains(uCaseWord, cubesWithPartOfWord, thisLocation, pos+1)) return true;
			//alas, if we mad it this far, we cannot find uCaseWord with
			//the start we have been given, so we roll back and continue searching
			highlightCube(row,col,false);
			//qSleep(kPauseTime);
			cubesWithPartOfWord.remove(thisLocation);
		}
	}
	return false;
}

bool BoggleGamePlay::boggleContains(const QString &uCaseWord) {
	//make sure all cubes have no highlighting
	bogglewindow->turnOffHighlighting();
	
	if (currentBoardSize == SMALL ) {
		return boggleContains(uCaseWord, lettersSmall);
	}	
	if (currentBoardSize == LARGE ) {
		return boggleContains(uCaseWord, lettersLarge);
	}
	return false;
}

void BoggleGamePlay::highlightCube(int row, int col, bool highlight) {
	bogglewindow->highlightCube(indexOf(row,col), highlight);
}

bool BoggleGamePlay::boggleContains( const QString& uCaseWord,
		const QVector<QString>& letters) {
	//search for the first letter of word anywhere in the board
	int size = letters.size();
	for (int row = 0; row < currentBoardSize; ++row) {
		for (int col = 0; col < currentBoardSize; ++ col) {
			if (letters.at(indexOf(row,col)) == uCaseWord[0]) {
				QSet<BoardLocation> cubesWithPartOfWord;
				BoardLocation bl = {row, col};
				cubesWithPartOfWord.insert(bl);
				highlightCube(row,col,true);
				if (boggleContains(
							uCaseWord,
							cubesWithPartOfWord,
							bl,
							1)) {
					return true;
				}
				highlightCube(row,col,false);
			}
		}
	}
	return false;
}


void BoggleGamePlay::boardSizeChanged(BoardSize newSize) {
	currentBoardSize = newSize;
	drawBoard();
}

void BoggleGamePlay::drawBoard() {
	if (currentBoardSize == SMALL) {
		bogglewindow->drawBoard(lettersSmall, SMALL, SMALL);
	} else if (currentBoardSize == LARGE) {
		bogglewindow->drawBoard(lettersLarge, LARGE, LARGE);
	}
}

void BoggleGamePlay::shuffleBoard() {
	shuffleSmallBoard();
	shuffleLargeBoard();
	drawBoard();
}

void BoggleGamePlay::shuffleSmallBoard() {
	shuffleBoard(kStandardCubes, kSmallNumCubes, lettersSmall);
}

void BoggleGamePlay::shuffleLargeBoard() {
    shuffleBoard(kBigBoggleCubes, kLargeNumCubes, lettersLarge);
}

//void BoggleGamePlay::startGame() {
    //currentPlayer = HUMAN;
//}

void BoggleGamePlay::shuffleBoard(const QString *cubes, const int size, QVector<QString>& shuffledLetters) {
    //{1,2,3,4,...}=noperm(utation)
    QVector<int> noperm;
    for(int i = 0; i < size; ++i) {
        noperm.push_back(i);
    }

    //{12,9,20,5,...}=perm(utation)
    QVector<int> perm;
    //count down so we don't go out of bounds,
    //since we are removing one element form noperm
    //on every iteration
    for(int i = size; i > 0; --i) {
        //pick a random element to remove
        int n = qrand() % i;
        //store the number to be removed in the permutation
        perm.push_back(noperm.at(n));
        //now remove
        noperm.remove(n);
    }

    //remove any old stuff first
    shuffledLetters.clear();
    //shuffle the boggle cubes by referencing perm,
    //pick a random side of the cube each time
    for (int i = 0; i < size; ++i) {
        int n = qrand() % 6;
        QString letter = kBigBoggleCubes[perm.at(i)][n];
        shuffledLetters.push_back(letter);
    }
}

void BoggleGamePlay::computerFindWords() {
	/* this function is the wrapper to iterate over k trees, where k is the
	 * number of boggle cubes in the boggle board.  Each vertex of the tree
	 * is labelled by a board location.  Fix a vertex v.  Then the path from
	 * the root vertex to v gives a sequence of boggle cubes.  This sequence
	 * is the potential word.  We only need to enforce the following rules:
	 * 1.  each cube in the sequence is adjacent to the previous cube.
	 * 2.  each cube appears at most once in the sequence.
	 * Given such a sequence, we simply check if it is a word in the lexicon
	 * of size >= 4.
	 * We truncate each tree by cutting off any sequence which is not a
	 * prefix in the lexicon.  This shortens the list of possibilities
	 * considerably.
	 */

	// using the same word list holder for human and computer, so clear it
	// before starting computer turn
	wordsUsed.clear();
	//QSet<string> wordsUsedByComputer;

	for (int row = 0; row < currentBoardSize; ++row) {
		for (int col = 0; col < currentBoardSize; ++col) {
			// start off with an empty set of locations which we have searched in 
			// this branch
			QSet<BoardLocation> usedLocations;
			// record our location on the board
			BoardLocation currentLocation = {row, col};
			// add this location to the set of locations we have visited in 
			// this branch
			usedLocations.insert(currentLocation);
			// start to build the word
            QString word = "";
			word += letterAt(row,col);
			highlightCube(row,col,true);
			// Note that in this implementation, the currentLocation variable
			// is added to the set of locations, but we also pass it along
			// as an argument since the Set data construct will not tell us
			// which BoardLocation was added last
			computerFindWords(
                wordsUsed,
				usedLocations,
				currentLocation,
				word);
			highlightCube(row,col,false);
		}
	}
}

void BoggleGamePlay::computerFindWords(
        QSet<QString> &wordsUsed,
		QSet<BoardLocation> &usedLocations,
		BoardLocation currentLocation,
		QString &wordSoFar
		) {
	/* at every iteration, we see if the word we have earns points, and
	 * record it if it does
	 */
	checkWord(wordSoFar, COMPUTER, wordsUsed);

	/* the main body of this function iterates over all possible word
	 * combinations.  To avoid checking too many, we terminate a branch if
	 * the word we have built so far is not a prefix of any word in the lexicon
	 */
	
	// Iterate over neighbors of the current position
	for (int deltaRow = -1; deltaRow < 2; ++deltaRow) {
		for (int deltaCol = -1; deltaCol < 2; ++deltaCol) {
			int row = currentLocation.row + deltaRow;
			int col = currentLocation.col + deltaCol;
			/* check that (row,col) really is a neighbor: 
			 * 1. position is on the board, 
			 * 2. position is different than current position.
			 * we only check condition 1, as condition 2 will get checked later,
			 * (see below)
			 */
			if (inBounds(row,col)) {
				// the position (row,col) still has more tests to pass,
				// but we need to store this position in a BoardLocation 
				// struct to do this test
				BoardLocation nextLocation = {row,col};
				// the next test is: have we used this location in this
				// branch of the search? Note that chosenLocations contains the
				// currentLocation, so checking this also ensures we are not
				// checking the case deltaRow = deltaCol = 0, i.e. condition 2
				// above is checked here
				if (!usedLocations.contains(nextLocation)) {
					// the next test of this location sees if the word we make
					// by appending the character at this location is the prefix
					// of any word in the lexicon
					wordSoFar += letterAt(row,col);
					if (englishLex.containsPrefix(wordSoFar)) {
						highlightCube(row,col,true);
						//record that we have used this location,
						//so we don't use it again in this branch
                        usedLocations.insert(nextLocation);
						//now continue the search
						computerFindWords(
                            wordsUsed,
                            usedLocations,
							nextLocation,
							wordSoFar);
					} 
					// roll back the addition of the character at (row,col)
					wordSoFar.remove(wordSoFar.length()-1,1);
					highlightCube(row,col,false);
					// roll back the addition of this location to the set of chosen
					// Locations
                    usedLocations.remove(nextLocation);
				}
			}
		}
	}
}
