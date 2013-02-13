#include "boggleboard.h"
#include <QGraphicsSimpleTextItem>
#include <QDebug>
#include <string>

const int kNumStandardCubes = 16;
const QString kStandardCubes[kNumStandardCubes] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

const int kNumBigCubes = 25;
const QString kBigBoggleCubes[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

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
    lettersFacing.clear();
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
        lettersFacing.push_back(label);
        }
    this->setScene(scene);
}

void BoggleBoard::highlightCube(int row, int col, bool highlight) {

}

void BoggleBoard::scramble() {
    QVector<int> noperm;
    for(int i = 0; i < 25; ++i) {
        noperm.push_back(i);
    }

    QVector<int> perm;
    for(int i = 25; i > 0; --i) {
        int n = qrand() % i;
        perm.push_back(noperm.at(n));
        noperm.remove(n);
    }

    for (int i = 0; i < 25; ++i) {
        int n = qrand() % 6;
        QString letter = kBigBoggleCubes[perm.at(i)][n];
        lettersFacing.at(i)->setText(letter);
    }
}
