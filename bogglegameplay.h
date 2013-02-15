#ifndef BOGGLEGAMEPLAY_H
#define BOGGLEGAMEPLAY_H

#include "boggleWindow.h"
#include "boggleconstants.h"
#include "lexicon.h"

#include <QObject>
#include <QVector>
#include <QString>
#include <QSet>
#include <QStack>
#include <QMap>

struct BoardLocation {
	int row;
	int col;
};



class BoggleGamePlay : public QObject
{
    Q_OBJECT

public:
    BoggleGamePlay(QObject *parent=0);
    ~BoggleGamePlay();

signals:
	//assuming computer turn begin is human turn end
	//and computer turn end sets player to NONE
	void signalHumanTurnBegin(void);
	void signalComputerTurnBegin(void);
	void signalComputerTurnEnd(void);

public slots:
    //void startGame();
	void shuffleBoard(void);
	void boardSizeChanged(BoardSize newSize);
	void humanTurnBegin(void);
	void processTextEntry(QLineEdit *);
	void computerTurnBegin(void);

private:
    Player currentPlayer;
	BoardSize currentBoardSize;
    QVector<QString> lettersSmall;
	QVector<QString> lettersLarge;
    BoggleWindow *bogglewindow;
    QSet<QString> wordsUsed;
    Lexicon englishLex;
	QMap<Player, int> scores;

	void drawBoard(void);
	void shuffleSmallBoard(void);
	void shuffleLargeBoard(void);
    void shuffleBoard(const QString*, const int, QVector<QString>&);
	void notify(const QString &);
	void displayResults(void);
	
	void checkWord(QString, Player, QSet<QString> &);
	bool boggleContains(const QString&);
	bool boggleContains(const QString&, const QVector<QString>&);
	bool boggleContains(const QString&, QSet<BoardLocation>&, BoardLocation&, int);

	void computerTurnEnd(void);
	void computerFindWords(QSet<QString>&, QSet<BoardLocation>&, BoardLocation, QString&);	
	void computerFindWords(void);

	void highlightCube(int,int,bool);
	
	int indexOf(int,int);
	bool inBounds(int,int);
	const QString letterAt(int,int);

};

#endif // BOGGLEGAMEPLAY_H
