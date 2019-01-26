#ifndef RECT_H
#define RECT_H
#include "ishape.h"


class Rect : public IShape
{
public:
    Rect(QPoint& ptBegin, QPoint& ptEnd);

    bool Draw(QPainter& painter);
    virtual bool IsSelect(QPoint& pos);
};

#endif // RECT_H
