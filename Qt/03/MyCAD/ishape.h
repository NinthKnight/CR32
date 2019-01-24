#ifndef ISHAPE_H
#define ISHAPE_H
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QPainter>

class IShape
{
public:
    IShape();

    virtual bool Draw(QPainter& painter) = 0;

protected:
    QPen m_pen;
    QBrush m_brush;
};

#endif // ISHAPE_H
