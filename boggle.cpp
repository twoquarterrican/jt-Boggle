#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>

#include "boggle.h"

const int kSmallBoardSize = 4;
const int kLargeBoardSize = 5;

Boggle::Boggle(QWidget * parent)
 : QWidget(parent)
{
    setUpBoggleBoard();
    QWidget *container = setUpOptionsContainer();
    setUpFoundWordLists();
    setUpTextEntry();
    layoutWidgets(container);

}

Boggle::~Boggle()
{
}

void Boggle::layoutWidgets(QWidget *container) {
    QGridLayout *layout = new QGridLayout(this);
    //first row is boggle board on left, options interfaces on right
    //make sure we have enough room for the biggest board
    layout->setRowMinimumHeight(0,kBoggleCubeHeight*kLargeBoardSize);
    layout->addWidget(boggleBoard,0,0,Qt::AlignTop);
    layout->addWidget(container,0,1);
    //second row is human player's list of words on left,
    //computer player's list of words on right
    layout->setRowMinimumHeight(1,kWindowYMin/3-kTextEntryYMin);
    layout->addWidget(humanFoundWords,1,0);
    layout->addWidget(computerFoundWords,1,1);
    //third row is text entry box and "press enter" button
    layout->setRowMinimumHeight(2,kTextEntryYMin);
    layout->addWidget(textEntry,2,0);
    //QObject::connect(le, &QLineEdit::returnPressed(), label2, setText("blue"));
}

void Boggle::setUpTextEntry() {
    textEntry = new QLineEdit();
    connect(textEntry, SIGNAL(returnPressed()), this, SLOT(updateHumanWordList()));
}

void Boggle::setUpFoundWordLists() {
    computerFoundWords = new QTextEdit();
    computerFoundWords->setReadOnly(true);
    humanFoundWords = new QTextEdit();
    humanFoundWords->setReadOnly(true);
}

void Boggle::setUpBoggleBoard() {
    //boardContainer = new QWidget();
    boggleBoard = new BoggleBoard();
    boggleBoard->setSize(kLargeBoardSize,kLargeBoardSize);
}

QWidget * Boggle::setUpOptionsContainer() {
    QWidget *optionsContainer = new QWidget();
    QWidget *sizeOptions = setUpSizeOptions();
    QLayout *scoreBoxes = setUpScoreBox();
    QGridLayout *layout = new QGridLayout(optionsContainer);
    layout->addWidget(sizeOptions,0,0);
    layout->addLayout(scoreBoxes,1,0);
    return optionsContainer;
}

QWidget * Boggle::setUpSizeOptions() {
    QGroupBox *sizeGroup = new QGroupBox("Board Size");
    QRadioButton * rbSmallSizeSelect = new QRadioButton("4x4", sizeGroup);
    connect(rbSmallSizeSelect, SIGNAL(clicked()), this, SLOT(boardSizeFour()));
    QRadioButton * rbLargeSizeSelect = new QRadioButton("5x5", sizeGroup);
    connect(rbLargeSizeSelect, SIGNAL(clicked()), this, SLOT(boardSizeFive()));
    QPushButton * pbScramble = new QPushButton("Scramble");
    connect(pbScramble, SIGNAL(pressed()), boggleBoard, SLOT(scramble()));
    QHBoxLayout *layout = new QHBoxLayout(sizeGroup);
    layout->addWidget(rbSmallSizeSelect);
    layout->addWidget(rbLargeSizeSelect);
    layout->addWidget(pbScramble);
    return sizeGroup;
}

QLayout * Boggle::setUpScoreBox() {
    QGroupBox *humanScoreBox = new QGroupBox("Your score");
    QGroupBox *compScoreBox = new QGroupBox("Computer score");

    humanScore = new QLabel("<h1>0</h1>");
    QGridLayout *layout = new QGridLayout(humanScoreBox);
    layout->addWidget(humanScore,0,0,Qt::AlignCenter);

    compScore = new QLabel("<h1>0</h1>");
    layout = new QGridLayout(compScoreBox);
    layout->addWidget(compScore,0,0,Qt::AlignCenter);

    //the layout for the options group
    layout = new QGridLayout();
    layout->addWidget(humanScoreBox,1,0);
    layout->addWidget(compScoreBox,1,1);

    return layout;
}

void Boggle::boardSizeFour() {
    updateBoardSize(4);
}

void Boggle::boardSizeFive() {
    updateBoardSize(5);
    }

void Boggle::updateBoardSize(int size) {
    boggleBoard->setSize(size,size);
}

void Boggle::updateHumanWordList() {
    QString text = textEntry->text();
    QString currentWords = humanFoundWords->toPlainText();
    humanFoundWords->setText(currentWords+" "+text);
    textEntry->setText("");
}
