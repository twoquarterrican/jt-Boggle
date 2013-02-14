#include "boggleboard.h"
#include <QGraphicsSimpleTextItem>
#include <QDebug>
#include <string>


BoggleBoard::BoggleBoard(QWidget * parent)
 : QGraphicsView(parent)
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene = new QGraphicsScene();
	scene->setSceneRect(0,0,kBoggleCubeWidth*LARGE,kBoggleCubeHeight*LARGE);
	this->setScene(scene);
	boardSquares = new QVector<QGraphicsRectItem*>;
}

BoggleBoard::~BoggleBoard()
{
}

void BoggleBoard::drawCube(int row, int col, QString &letter, bool highlight) {
	int x = col*kBoggleCubeWidth;
	int y = row*kBoggleCubeHeight;
	QColor color("burlywood");
	if (highlight) color = QColor("chocolate");
	QBrush brush(color);
	QPen pen(QColor("black"));
	scene->addRect(QRectF(x,y,kBoggleCubeWidth,kBoggleCubeHeight),pen,brush);
}

void BoggleBoard::drawBoard(QVector<QString> &letters, int nrows, int ncols) {
	scene->clear();
	boardSquares->clear();
	for (int i = 0; i < nrows*ncols; ++i) {
		int x = (i%nrows)*kBoggleCubeWidth;
		int y = (i/nrows)*kBoggleCubeHeight;
		QGraphicsRectItem *square = new QGraphicsRectItem(x,y,kBoggleCubeWidth,kBoggleCubeHeight);
		square->setBrush(kDefaultSquareColor);
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
/*
 *
 *    QVector<QGraphicsRectItem*> boardSquaress;
 *    for (int i = 8; i < nrows*ncols; ++i) {
 *        int x = (i%nrows)*kBoggleCubeWidth;
 *        int y = (i/nrows)*kBoggleCubeHeight;
 *        QGraphicsRectItem *square = new QGraphicsRectItem(x,y,kBoggleCubeWidth,kBoggleCubeHeight);
 *        boardSquaress.push_back(square);
 *        scene->addItem(square);
 *    }	
 *    boardSquaress.at(4)->setBrush(QBrush(QColor("black")));
 *    boardSquaress.at(5)->setBrush(QBrush(QColor("red")));
 */
}

//void BoggleBoard::initialize(QVector<QRectF> &boardSquares) {
	//for (int i = 0; i < kLargeNumCubes; ++i) {
		//QRectF rect(0,0,kBoggleCubeWidth,kBoggleCubeHeight);
		//boardSquares.push_back(rect);
	//}
//}

/*
 *void BoggleBoard::setSize(int nCols, int nRows) {
	 *    numCols = nCols;
 *    numRows = nRows;
 *    QGraphicsScene * scene = new QGraphicsScene(this->parent());
 *    for (int cubeNum = 0; cubeNum < nCols*nRows; ++cubeNum) {
 *        int x = kBoggleCubeWidth*(cubeNum%nCols);
 *        int y = kBoggleCubeHeight*(cubeNum/nCols);
 *        QBrush brush = QBrush(QColor("burlywood"));
 *        QPen pen = QPen();
 *        scene->addRect(QRectF(x,y,kBoggleCubeWidth,kBoggleCubeHeight),pen,brush);
 *
 *        QGraphicsSimpleTextItem * label = scene->addSimpleText("B");
 *        QFont font = label->font();
 *        font.setPointSize(24);
 *        label->setFont(font);
 *        int h = label->boundingRect().height();
 *        int w = label->boundingRect().width();
 *        label->setPos(x+kBoggleCubeWidth/2-w/2,y+kBoggleCubeHeight/2-h/2);
 *        }
 *    this->setScene(scene);
 *}
 */

//void BoggleBoard::highlightCube(int row, int col, bool highlight) {

//}

//void BoggleBoard::scramble() {
//}

//void BoggleBoard::setBoard(QVector<QString> &letters) {
	//if (letters.size() == kSmallNumCubes) {
		//setBoard(letters, SMALL, SMALL);
	//}
	//if (letters.size() == kLargeNumCubes) {
		//setBoard(letters, LARGE, LARGE);
	//}
//}

//void BoggleBoard::setBoard(QVector<QString> &letters, int nrows, int ncols) {

    //for (int cubeNum = 0; cubeNum < ncols*nrows; ++cubeNum) {
        //int x = kBoggleCubeWidth*(cubeNum%ncols);
        //int y = kBoggleCubeHeight*(cubeNum/ncols);
        //QBrush brush = QBrush(QColor("burlywood"));
        //QPen pen = QPen(QColor("white"));
		//QRectF rect = boardSquares.at(cubeNum);
		//rect.setX(x);
		//rect.setY(y);
		////rect.setTopLeft(setTopLeft(QPointF(x,y)));
		////boardSquares.at(cubeNum).setTopLeft(QPointF(x,y));
		//scene->addRect(rect,pen,brush);
        ////scene->addRect(boardSquares.at(cubeNum),pen,brush);

        //QGraphicsSimpleTextItem * label = scene->addSimpleText(letters.at(cubeNum));
        //QFont font = label->font();
        //font.setPointSize(24);
        //label->setFont(font);
        //int h = label->boundingRect().height();
        //int w = label->boundingRect().width();
        //label->setPos(x+kBoggleCubeWidth/2-w/2,y+kBoggleCubeHeight/2-h/2);
    //}
	////QRect rect = this->contentsRect();
	////this->setSceneRect(0,0, rect.width(), rect.height());
//}
