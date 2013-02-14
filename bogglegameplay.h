#ifndef BOGGLEGAMEPLAY_H
#define BOGGLEGAMEPLAY_H

#include <QObject>
#include "boggleWindow.h"
#include "boggleconstants.h"
#include <QVector>
#include <QString>

class BoggleGamePlay : public QObject
{
    Q_OBJECT

public:
    BoggleGamePlay(QObject *parent=0);
    ~BoggleGamePlay();

public slots:
    //void startGame();
	void shuffleBoard(void);
	void boardSizeChanged(BoardSize newSize);

private:
    Player currentPlayer;
	BoardSize currentBoardSize;
    QVector<QString> lettersSmall;
	QVector<QString> lettersLarge;
    BoggleWindow *bogglewindow;

	void drawBoard(void);
	void shuffleSmallBoard(void);
	void shuffleLargeBoard(void);
    void shuffleBoard(const QString*, const int, QVector<QString>&);

};

#endif // BOGGLEGAMEPLAY_H
