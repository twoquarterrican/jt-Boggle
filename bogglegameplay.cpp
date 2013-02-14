#include "bogglegameplay.h"
#include <QDebug>
#include "sleep.h"


BoggleGamePlay::BoggleGamePlay(QObject *parent)
  :QObject(parent)
{
    currentPlayer = NONE;
	currentBoardSize = kDefaultBoardSize;
    bogglewindow = new BoggleWindow();
	connect(bogglewindow, SIGNAL(boardSizeChanged(BoardSize)),
			this, SLOT(boardSizeChanged(BoardSize)));
	connect(bogglewindow, SIGNAL(shuffleBoard()),
			this, SLOT(shuffleBoard()));
    //bogglewindow->setBoard(lettersSmall);
    bogglewindow->show();
	shuffleBoard();
}

BoggleGamePlay::~BoggleGamePlay()
{
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
