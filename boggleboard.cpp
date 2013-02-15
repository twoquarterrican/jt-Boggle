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
	//animQueue->start();
	
}

BoggleBoard::~BoggleBoard()
{
}

//void BoggleBoard::drawCube(int row, int col, QString &letter, bool highlight) {
	//int x = col*kBoggleCubeWidth;
	//int y = row*kBoggleCubeHeight;
	//QColor color("burlywood");
	//if (highlight) color = QColor("chocolate");
	//QBrush brush(color);
	//QPen pen(QColor("black"));
	//scene->addRect(QRectF(x,y,kBoggleCubeWidth,kBoggleCubeHeight),pen,brush);
//}

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
}

void BoggleBoard::highlightCube(int index, bool highlight) {
	boardSquares->at(index)->setColor(
			highlight ? kHighlightSquareColor : kDefaultSquareColor);
	this->repaint(0,0,100,100);
   /* QPropertyAnimation *anim = boardSquares->at(index)->animateHighlight(highlight);*/
	//QObject::connect(anim, SIGNAL(finished()),
			//this, SLOT(startNextAnimation()));
	////if animQueue is empty before we enqueue the current anim,
	////we need to start the current animation manually (i.e. w/o finished() signal)
	//bool isEmpty = animQueue->isEmpty();
	//animQueue->enqueue(anim);
	//if ( isEmpty ) {
		//qDebug() << "kickstarting animation queue";
		//anim->start();
   /* }*/
}

void BoggleBoard::turnOffHighlighting() {
    for (int i = 0; i < boardSquares->size(); ++i) {
		boardSquares->at(i)->setColor(kDefaultSquareColor);
	}
	//make sure we can see the change right away
	//this->update();
}

void BoggleBoard::startNextAnimation() {
	if (!animQueue->isEmpty()) {
		qDebug() << "deleting queued animation";
		QPropertyAnimation * anim = animQueue->dequeue();
		delete anim;
		if (!animQueue->isEmpty()) {
			qDebug() << "starting queued animation";
			animQueue->dequeue()->start();
		}
	}
}
