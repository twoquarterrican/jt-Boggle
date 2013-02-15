#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QRadioButton>

#include "boggleWindow.h"

BoggleWindow::BoggleWindow(QWidget * parent)
 : QWidget(parent)
{
    this->setWindowTitle("Boggle");
    setUpBoggleBoard();
    setUpOptionsContainer();
    setUpFoundWordLists();
    QLayout *layout3 = setUpNotificationArea();
    QLayout *layout4 = setUpTextEntry();
    layoutWidgets(layout3, layout4);
}

BoggleWindow::~BoggleWindow()
{
}

void BoggleWindow::layoutWidgets(QLayout *layout3, QLayout * layout4) {
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
    //third row is notification area
    layout->addLayout(layout3,2,0,1,2);
    //fourth row is text entry box and "press enter" button
    //layout->setRowMinimumHeight(2,kTextEntryYMin);
    layout->addLayout(layout4,3,0,1,2);
}

QLayout * BoggleWindow::setUpNotificationArea() {
    notificationLabel = new QLabel("Pick a board size. Shuffle if you like. Then Press start or just start entering words in the space below.");
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(notificationLabel);
    return layout;
}

QLayout * BoggleWindow::setUpTextEntry() {
    textEntry = new QLineEdit();
    connect(textEntry, SIGNAL(returnPressed()), this, SLOT(textEntrySubmitted()));
	startButton = new QPushButton("Start");
	connect(startButton, SIGNAL(pressed()), this, SLOT(startButtonPressed()));
	doneButton = new QPushButton("Done");
	doneButton->setEnabled(false);
	connect(doneButton, SIGNAL(pressed()), this, SLOT(doneButtonPressed()));
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
    shuffleButton = new QPushButton("Shuffle");
    connect(shuffleButton, SIGNAL(pressed()), this, SLOT(shuffleButtonPressed()));
    QHBoxLayout *layout = new QHBoxLayout(sizeGroup);
    layout->addWidget(rbSmallSizeSelect);
    layout->addWidget(rbLargeSizeSelect);
    layout->addWidget(shuffleButton);
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
	emit signalShuffleBoard();
}

void BoggleWindow::updateBoardSize(BoardSize size) {
	emit signalBoardSizeChanged(size);
}

void BoggleWindow::textEntrySubmitted() {
	emit signalTextEntrySubmitted(textEntry);
}

void BoggleWindow::startButtonPressed() {
	textEntrySubmitted();
}

void BoggleWindow::doneButtonPressed() {
	emit signalHumanDone();
}

void BoggleWindow::humanTurnBegin() {
	startButton->setEnabled(false);
	doneButton->setEnabled(true);
	rbLargeSizeSelect->setEnabled(false);
	rbSmallSizeSelect->setEnabled(false);
	shuffleButton->setEnabled(false);
	computerFoundWords->setText("");
	humanFoundWords->setText("");
}

void BoggleWindow::computerTurnBegin() {
	startButton->setEnabled(false);
	rbLargeSizeSelect->setEnabled(false);
	rbSmallSizeSelect->setEnabled(false);
	shuffleButton->setEnabled(false);
}

void BoggleWindow::computerTurnEnd() {
	startButton->setEnabled(true);
	doneButton->setEnabled(false);
	rbLargeSizeSelect->setEnabled(true);
	rbSmallSizeSelect->setEnabled(true);
	shuffleButton->setEnabled(true);
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

void BoggleWindow::recordWordForPlayer(QString &word, Player player) {
	if (player == HUMAN) {
		QString currentWords = humanFoundWords->toPlainText();
		humanFoundWords->setText(currentWords+" "+word);
	} else if (player == COMPUTER) {
		QString currentWords = computerFoundWords->toPlainText();
		computerFoundWords->setText(currentWords+" "+word);
	}
}

void BoggleWindow::updateScore(int score, Player player) {
	if (player == HUMAN) {
		humanScore->setText(QString("%1").arg(score));
	} else if (player == COMPUTER) {
		compScore->setText(QString("%1").arg(score));
	}
}

void BoggleWindow::notify(const QString &message) {
	notificationLabel->setText(message);
}

void BoggleWindow::highlightCube(int index, bool highlight) {
    boggleBoard->highlightCube(index,highlight);
	//this->repaint();
	//this->update();

	//qDebug() << "I will pause for 5 seconds, then repaint.. pausing";
	//qSleep(5000);
	//this->repaint();
	//this->update();
	//qDebug() << "Did that do it?";
	//qSleep(12000);
}

void BoggleWindow::turnOffHighlighting() {
    boggleBoard->turnOffHighlighting();
	this->repaint();
}
