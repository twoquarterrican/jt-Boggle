#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRectF>
#include <vector>
#include <QSequentialAnimationGroup>
#include <QQueue>
#include "boggleconstants.h"
#include "bogglecube.h"

class BoggleBoard : public QGraphicsView
{
    Q_OBJECT

public:
    explicit BoggleBoard(QWidget * parent=0 );
    ~BoggleBoard();
	void drawBoard(QVector<QString> &letters, int nrows, int ncols);
	void highlightCube(int, bool);
	void turnOffHighlighting(void);

public slots:
	void startNextAnimation(void);
	void startNextTestAnimation(void);
	void kickStartAnimationQueue(void);

private:
	QGraphicsScene *scene;
	QVector<BoggleCube*> *boardSquares;
	QQueue<QPropertyAnimation*> *animQueue;
	bool animCurrentlyPlaying;
	void startTestAnimation(void);
};

#endif BOGGLEBOARD_H
