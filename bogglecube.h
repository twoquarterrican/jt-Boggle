#ifndef BOGGLECUBE_H
#define BOGGLECUBE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QPropertyAnimation>

class BoggleCube : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
        //For Property animation:
        //change color
        Q_PROPERTY(QColor color READ color WRITE setColor)
public:
    explicit BoggleCube(qreal,qreal,qreal,qreal,
                        QGraphicsItem *parent=0,
                        QObject *objParent=0);

    QColor color(void);
    void setColor(const QColor&);

    QPropertyAnimation * animateHighlight(bool);
    
signals:
    void animationFinished(void);
    
public slots:

private:
    QColor m_color;

};

#endif // BOGGLECUBE_H
