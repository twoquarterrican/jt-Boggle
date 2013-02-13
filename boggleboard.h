#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <QGraphicsView>
#include <vector>

const int kBoggleCubeWidth=40;
const int kBoggleCubeHeight=40;

class BoggleBoard : public QGraphicsView
{
    Q_OBJECT

public:
    explicit BoggleBoard(QWidget * parent=0 );
    ~BoggleBoard();

signals:
    
public slots:
    void setSize(int nCols, int nRows);
    void highlightCube(int row, int col, bool highlight);
    void scramble();

private:
    int numCols;
    int numRows;
    QVector<QGraphicsSimpleTextItem*> lettersFacing;
    
};

#endif BOGGLEBOARD_H
