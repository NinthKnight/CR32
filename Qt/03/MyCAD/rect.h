#ifndef RECT_H
#define RECT_H
#include "ishape.h"


class Rect : public IShape
{
public:
    Rect(QPoint& ptBegin, QPoint& ptEnd);

    bool Draw(QPainter& painter);


    QPoint m_ptBegin;
    QPoint m_ptEnd;
};

#endif // RECT_H
