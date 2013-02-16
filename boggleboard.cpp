#include "boggleboard.h"
#include <QGraphicsSimpleTextItem>
#include <QStateMachine>
#include <QDebug>
//#include <string>


BoggleBoard::BoggleBoard(QWidget * parent)
 : QGraphicsView(parent)
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	animQueue = new QQueue<QPropertyAnimation*>;
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,kBoggleCubeWidth*LARGE+1,kBoggleCubeHeight*LARGE+1);
	this->setScene(scene);
	boardSquares = new QVector<BoggleCube*>;
	animCurrentlyPlaying = false;
}

BoggleBoard::~BoggleBoard()
{
}

void BoggleBoard::drawBoard(QVector<QString> &letters, int nrows, int ncols) {
	scene->clear();
	boardSquares->clear();
	for (int i = 0; i < nrows*ncols; ++i) {
		int x = (i%nrows)*kBoggleCubeWidth;
		int y = (i/nrows)*kBoggleCubeHeight;
		BoggleCube *square = new BoggleCube(x,y,kBoggleCubeWidth,kBoggleCubeHeight);
		square->setColor(kDefaultSquareColor);
        boardSquares->push_back(square);
		scene->addItem(square);

        QGraphicsSimpleTextItem * label = scene->addSimpleText(letters.at(i));
        QFont font = label->font();
        font.setPointSize(24);
        label->setFont(font);
        int h = label->boundingRect().height();
        int w = label->boundingRect().width();
        label->setPos(x+kBoggleCubeWidth/2-w/2,y+kBoggleCubeHeight/2-h/2);
	}	
	scene->setSceneRect(0,0,nrows*kBoggleCubeWidth,ncols*kBoggleCubeHeight);
	//startTestAnimation();
}

void BoggleBoard::highlightCube(int index, bool highlight) {
	//boardSquares->at(index)->setColor(
			//highlight ? kHighlightSquareColor : kDefaultSquareColor);
    QPropertyAnimation *anim = boardSquares->at(index)->animateHighlight(highlight);
	QObject::connect(anim, SIGNAL(finished()),
			this, SLOT(startNextAnimation()));
	//if no animation is playing we need to start the current
	//animation manually (i.e. w/o finished() signal)
	//otherwise we just put the animation in the queue
	if (animCurrentlyPlaying) {
		animQueue->enqueue(anim);
	} else {
		anim->start(QAbstractAnimation::DeleteWhenStopped);
		animCurrentlyPlaying = true;
	}
}

void BoggleBoard::startTestAnimation() {
	for(int i = 0; i < boardSquares->size(); ++i) {
		QPropertyAnimation *anim = boardSquares->at(i)
			->animateHighlight(true);
		QObject::connect(anim, SIGNAL(finished()),
				this, SLOT(startNextTestAnimation()));
		animQueue->enqueue(anim);
	}
	for(int i = 0; i < boardSquares->size(); ++i) {
		QPropertyAnimation *anim = boardSquares->at(i)
			->animateHighlight(false);
		QObject::connect(anim, SIGNAL(finished()),
				this, SLOT(startNextTestAnimation()));
		animQueue->enqueue(anim);
	}
	startNextTestAnimation();
}

void BoggleBoard::startNextTestAnimation() {
	QPropertyAnimation *anim = animQueue->dequeue();
	anim->start();
	animQueue->enqueue(anim);
}

void BoggleBoard::turnOffHighlighting() {
	animQueue->clear();
    for (int i = 0; i < boardSquares->size(); ++i) {
		boardSquares->at(i)->setColor(kDefaultSquareColor);
	}
	//make sure we can see the change right away
	//this->update();
}

void BoggleBoard::kickStartAnimationQueue() {
	startNextAnimation();
}

void BoggleBoard::startNextAnimation() {
	//if there are no animations left, make sure we set the flag that no animations are 
	//currently playing.  To be safe, we set the flag true after we start the next animation
	//even though it should already be set to true
	if (animQueue->isEmpty()) {
		animCurrentlyPlaying = false;
	} else {
		animQueue->dequeue()->start(QAbstractAnimation::DeleteWhenStopped);
		animCurrentlyPlaying = true;
	}
}
