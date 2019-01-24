#ifndef LINE_H
#define LINE_H

#include "ishape.h"

class line : public IShape
{
public:
    line(QPoint& ptBegin, QPoint& ptEnd);

    bool Draw(QPainter& painter);


    QPoint m_ptBegin;
    QPoint m_ptEnd;
};

#endif // LINE_H
