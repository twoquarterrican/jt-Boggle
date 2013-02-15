#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>

#include "boggleboard.h"
#include "boggleconstants.h"

class BoggleWindow : public QWidget
{
    Q_OBJECT

public:
    BoggleWindow(QWidget * parent=0);
    ~BoggleWindow();
	void recordWordForPlayer(QString&, Player);
	void drawBoard(QVector<QString>&,int,int);
	void highlightCube(int,bool);
	void setBoard(QVector<QString>&);
	void notify(const QString&);
	void updateScore(int, Player);
	void turnOffHighlighting(void);

private:
    BoggleBoard *boggleBoard;
    //QWidget *boardContainer;
    QWidget *optionsContainer;
    QTextEdit *computerFoundWords;
    QTextEdit *humanFoundWords;
    QLineEdit *textEntry;
    QLabel *humanScore;
    QLabel *compScore;
    QRadioButton *rbSmallSizeSelect;
    QRadioButton *rbLargeSizeSelect;
	QPushButton *shuffleButton;
	QPushButton *doneButton;
	QPushButton *startButton;
	QLabel *notificationLabel;

    void updateBoardSize(BoardSize size);
    void setUpBoggleBoard();
    void setUpOptionsContainer();
    void setUpFoundWordLists();
	QLayout * setUpNotificationArea();
    QLayout * setUpTextEntry();
    void layoutWidgets(QLayout* layout3, QLayout *layout4);
    QWidget *setUpSizeOptions();
    QLayout *setUpScoreBox();

//    void setBoard(QVector<QString> &letters, int nrows, int ncols);

signals:
	void signalBoardSizeChanged(BoardSize newSize);
	void signalShuffleBoard(void);
	void signalHumanDone(void);
	void signalTextEntrySubmitted(QLineEdit *);

public slots:
	//these slots will be signaled by game logic
	void humanTurnBegin(void);
	void computerTurnBegin(void);
	void computerTurnEnd(void);

	//these slots will be signaled by user input
    void setBoardSizeSmall(void);
    void setBoardSizeLarge(void);
	void shuffleButtonPressed(void);
    void textEntrySubmitted(void);
	void startButtonPressed(void);
	void doneButtonPressed(void);
};

#endif // BOGGLEWINDOW_H
