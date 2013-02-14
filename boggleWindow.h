#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>
#include <QRadioButton>

#include "boggleboard.h"
#include "boggleconstants.h"

class BoggleWindow : public QWidget
{
    Q_OBJECT

public:
    BoggleWindow(QWidget * parent=0);
    ~BoggleWindow();
	void drawBoard(QVector<QString> &letters,int numRows, int numCols);
	void highlightCube(int row, int col, bool flag);
	void labelCube(int row, int col, QString &letter);
	void setBoard(QVector<QString> &letters);

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

    void updateBoardSize(BoardSize size);
    void setUpBoggleBoard();
    void setUpOptionsContainer();
    void setUpFoundWordLists();
    QLayout * setUpTextEntry();
    void layoutWidgets(QLayout *layout4);
    QWidget *setUpSizeOptions();
    QLayout *setUpScoreBox();

//    void setBoard(QVector<QString> &letters, int nrows, int ncols);

signals:
	void boardSizeChanged(BoardSize newSize);
	void shuffleBoard(void);
	void signalHumanTurnBegin(void);
	void signalHumanTurnEnd(void);

public slots:
    void setBoardSizeSmall(void);
    void setBoardSizeLarge(void);
	void shuffleButtonPressed(void);
    void updateHumanWordList(void);
	void humanTurnBegin(void);
	void humanTurnEnd(void);
};

#endif // BOGGLEWINDOW_H
