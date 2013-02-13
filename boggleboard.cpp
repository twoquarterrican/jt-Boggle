#include "boggleboard.h"
#include <QGraphicsSimpleTextItem>
#include <string>

//const int kNumStandardCubes = 16;
//const std::string kStandardCubes[kNumStandardCubes] = {
//   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
//   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
//   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
//   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
//};

//const int kNumBigCubes = 25;
//const std::string kBigBoggleCubes[25] = {
//   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
//   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
//   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
//   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
//   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
//};

BoggleBoard::BoggleBoard(QWidget * parent)
 : QGraphicsView(parent)
{
}

BoggleBoard::~BoggleBoard()
{
}

void BoggleBoard::setSize(int nCols, int nRows) {
    numCols = nCols;
    numRows = nRows;
    QGraphicsScene * scene = new QGraphicsScene(this->parent());
    for (int cubeNum = 0; cubeNum < nCols*nRows; ++cubeNum) {
        int x = kBoggleCubeWidth*(cubeNum%nCols);
        int y = kBoggleCubeHeight*(cubeNum/nCols);
        QBrush brush = QBrush(QColor("burlywood"));
        QPen pen = QPen();
        scene->addRect(QRectF(x,y,kBoggleCubeWidth,kBoggleCubeHeight),pen,brush);
        QGraphicsSimpleTextItem * label = scene->addSimpleText("B");
        QFont font = label->font();
        font.setPointSize(24);
        label->setFont(font);
        int h = label->boundingRect().height();
        int w = label->boundingRect().width();
        label->setPos(x+kBoggleCubeWidth/2-w/2,y+kBoggleCubeHeight/2-h/2);
        }
    this->setScene(scene);
}

void BoggleBoard::highlightCube(int row, int col, bool highlight) {

}

void BoggleBoard::scramble() {
}
