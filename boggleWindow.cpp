#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>
#include <QPushButton>

#include "boggleWindow.h"

BoggleWindow::BoggleWindow(QWidget * parent)
 : QWidget(parent)
{
    this->setWindowTitle("Boggle");
    setUpBoggleBoard();
    setUpOptionsContainer();
    setUpFoundWordLists();
    QLayout *layout4 = setUpTextEntry();
    layoutWidgets(layout4);
}

BoggleWindow::~BoggleWindow()
{
}

void BoggleWindow::layoutWidgets(QLayout * layout4) {
    QGridLayout *layout = new QGridLayout(this);
    //first row is boggle board on left, options interfaces on right
    //make sure we have enough room for the biggest board
    //layout->setRowMinimumHeight(0,kBoggleCubeHeight*SMALL);
    layout->addWidget(boggleBoard,0,0,Qt::AlignCenter);
    layout->addWidget(optionsContainer,0,1);
    //second row is human player's list of words on left,
    //computer player's list of words on right
    layout->setRowMinimumHeight(1,kWindowYMin/3-kTextEntryYMin);
    layout->addWidget(humanFoundWords,1,0);
    layout->addWidget(computerFoundWords,1,1);
    //third row is text entry box and "press enter" button
    layout->setRowMinimumHeight(2,kTextEntryYMin);
    layout->addLayout(layout4,2,0,1,2);
    //QObject::connect(le, &QLineEdit::returnPressed(), label2, setText("blue"));
}

QLayout * BoggleWindow::setUpTextEntry() {
    textEntry = new QLineEdit();
    connect(textEntry, SIGNAL(returnPressed()), this, SLOT(updateHumanWordList()));
	QPushButton * startButton = new QPushButton("Start");
	connect(startButton, SIGNAL(pressed()), this, SLOT(humanTurnBegin()));
	QPushButton * doneButton = new QPushButton("Done");
	connect(doneButton, SIGNAL(pressed()), this, SLOT(humanTurnEnd()));
	QHBoxLayout * layout = new QHBoxLayout();
	layout->addWidget(textEntry);
	layout->addWidget(startButton);
	layout->addWidget(doneButton);
	return layout;
}

void BoggleWindow::setUpFoundWordLists() {
    computerFoundWords = new QTextEdit();
    computerFoundWords->setReadOnly(true);
    humanFoundWords = new QTextEdit();
    humanFoundWords->setReadOnly(true);
}

void BoggleWindow::setUpBoggleBoard() {
    boggleBoard = new BoggleBoard();
	/*
	 *container->setFixedSize(
	 *        QSize(kLargeBoardSize*kBoggleCubeWidth,kLargeBoardSize*kBoggleCubeHeight)
	 *        );
	 */
}

void BoggleWindow::setUpOptionsContainer() {
    optionsContainer = new QWidget();
    QWidget *sizeOptions = setUpSizeOptions();
    QLayout *scoreBoxes = setUpScoreBox();
    QGridLayout *layout = new QGridLayout(optionsContainer);
    layout->addWidget(sizeOptions,0,0);
    layout->addLayout(scoreBoxes,1,0);
}

QWidget * BoggleWindow::setUpSizeOptions() {
    QGroupBox *sizeGroup = new QGroupBox("Board Size");
    rbSmallSizeSelect = new QRadioButton("4x4", sizeGroup);
    connect(rbSmallSizeSelect, SIGNAL(clicked()), this, SLOT(setBoardSizeSmall()));
    rbLargeSizeSelect = new QRadioButton("5x5", sizeGroup);
    connect(rbLargeSizeSelect, SIGNAL(clicked()), this, SLOT(setBoardSizeLarge()));
    QPushButton * pbScramble = new QPushButton("Scramble");
    connect(pbScramble, SIGNAL(pressed()), this, SLOT(shuffleButtonPressed()));
    QHBoxLayout *layout = new QHBoxLayout(sizeGroup);
    layout->addWidget(rbSmallSizeSelect);
    layout->addWidget(rbLargeSizeSelect);
    layout->addWidget(pbScramble);
    return sizeGroup;
}

QLayout * BoggleWindow::setUpScoreBox() {
    QGroupBox *humanScoreBox = new QGroupBox("Your score");
    QGroupBox *compScoreBox = new QGroupBox("Computer score");

    humanScore = new QLabel("<h1>0</h1>");
    QGridLayout *layout = new QGridLayout(humanScoreBox);
    layout->addWidget(humanScore,0,0,Qt::AlignCenter);

    compScore = new QLabel("<h1>0</h1>");
    layout = new QGridLayout(compScoreBox);
    layout->addWidget(compScore,0,0,Qt::AlignCenter);

    //QPushButton *startGameButton = new QPushButton("Start");
    //connect(startGameButton, SIGNAL(pressed()), game, SLOT(startGame()));

    //the layout for the options group
    layout = new QGridLayout();
    layout->addWidget(humanScoreBox,1,0);
    layout->addWidget(compScoreBox,1,1);
    //layout->addWidget(startGameButton,2,0);

    return layout;
}

void BoggleWindow::setBoardSizeSmall() {
    updateBoardSize(SMALL);
}

void BoggleWindow::setBoardSizeLarge() {
    updateBoardSize(LARGE);
}

void BoggleWindow::shuffleButtonPressed() {
	emit shuffleBoard();
}

void BoggleWindow::updateBoardSize(BoardSize size) {
	emit boardSizeChanged(size);
}

void BoggleWindow::updateHumanWordList() {
    QString text = textEntry->text();
    QString currentWords = humanFoundWords->toPlainText();
    humanFoundWords->setText(currentWords+" "+text);
    textEntry->setText("");
}

void BoggleWindow::drawBoard(QVector<QString> &letters, int nrows, int ncols) {
	boggleBoard->drawBoard(letters, nrows, ncols);
    bool small = false;
    bool large = false;
    if (nrows == SMALL && ncols == SMALL) small = true;
    if (nrows == LARGE && ncols == LARGE) large = true;
    rbSmallSizeSelect->setChecked(small);
    rbLargeSizeSelect->setChecked(large);
}

void BoggleWindow::humanTurnBegin() {
	emit signalHumanTurnBegin();
}

void BoggleWindow::humanTurnEnd() {
	emit signalHumanTurnEnd();
}
