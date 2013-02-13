#ifndef BOGGLEWINDOW_H
#define BOGGLEWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>

#include "boggleboard.h"

const int kWindowXMin = 300;
const int kWindowYMin = 300;
const int kTextEntryYMin = 20;
const int kDefaultBoardSize = 4;

class BoggleWindow : public QWidget
{
    Q_OBJECT

public:
    BoggleWindow(QWidget * parent=0);
    ~BoggleWindow();

private:
    BoggleBoard *boggleBoard;
    //QWidget *boardContainer;
    //QWidget *optionsContainer;
    QTextEdit *computerFoundWords;
    QTextEdit *humanFoundWords;
    QLineEdit *textEntry;
    QLabel *humanScore;
    QLabel *compScore;
    void updateBoardSize(int size);
    void setUpBoggleBoard();
    QWidget *setUpOptionsContainer();
    QWidget *setUpSizeOptions();
    QLayout *setUpScoreBox();
    void setUpFoundWordLists();
    void setUpTextEntry();
    void layoutWidgets(QWidget *container);

signals:

public slots:
    void boardSizeFour();
    void boardSizeFive();
    void updateHumanWordList();
};

#endif // BOGGLEWINDOW_H
