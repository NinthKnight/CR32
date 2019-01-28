#ifndef LINE_H
#define LINE_H

#include "ishape.h"

class line : public IShape
{
public:
    line(QPoint& ptBegin, QPoint& ptEnd);

    bool Draw(QPainter& painter);
    virtual bool IsSelect(QPoint& pos);

    virtual bool Serialise(QDataStream& ds, bool isWrite = true);

};

#endif // LINE_H
