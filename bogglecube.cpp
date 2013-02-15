#include "bogglecube.h"
#include "boggleconstants.h"
#include <QGraphicsItem>
#include <QBrush>
#include <QPropertyAnimation>

BoggleCube::BoggleCube(
        qreal x, qreal y, qreal width, qreal height,
        QGraphicsItem *graphicsItemParent, QObject *qObjectParent) :
    QObject(qObjectParent),
    QGraphicsRectItem(x,y,width,height,graphicsItemParent)
{
}

QColor BoggleCube::color() {
    return m_color;
}

void BoggleCube::setColor(const QColor &color) {
    QBrush brush(color);
    this->setBrush(brush);
}

QPropertyAnimation * BoggleCube::animateHighlight(bool highlight) {
    QPropertyAnimation *anim = new QPropertyAnimation(this, "color");
    anim->setDuration(kHighlightDuration);
    if(highlight) {
        anim->setStartValue(kDefaultSquareColor);
        anim->setEndValue(kHighlightSquareColor);
    } else {
        anim->setStartValue(kHighlightSquareColor);
        anim->setEndValue(kDefaultSquareColor);
    }
    //anim->start(QAbstractAnimation::DeleteWhenStopped);
    return anim;
}
