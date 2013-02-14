#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <vector>
#include "boggleconstants.h"

class BoggleBoard : public QGraphicsView
{
    Q_OBJECT

public:
    explicit BoggleBoard(QWidget * parent=0 );
    ~BoggleBoard();
	void drawCube(int row, int col, QString &letter, bool highlight);
	void drawBoard(QVector<QString> &letters, int nrows, int ncols);

signals:
    
public slots:
    //void setSize(int nCols, int nRows);
    //void highlightCube(int row, int col, bool highlight);
    //void scramble();

private:
	QGraphicsScene *scene;
	QVector<QGraphicsRectItem*> *boardSquares;
    void setBoard(QVector<QString> &letters, int nRows, int nCols);
	void initialize(QVector<QRectF> &boardSquares);
	void initialize(QGraphicsScene &scene);
};

#endif BOGGLEBOARD_H
