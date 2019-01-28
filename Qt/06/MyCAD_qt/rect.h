#ifndef RECT_H
#define RECT_H
#include "ishape.h"


class Rect : public IShape
{
    Q_OBJECT
public:
    Rect(QPoint& ptBegin, QPoint& ptEnd);

    Rect(){}

    Rect(const Rect& obj){
        m_ptBegin = obj.m_ptBegin;
        m_ptEnd = obj.m_ptEnd;
    }

    bool Draw(QPainter& painter);
    virtual bool IsSelect(QPoint& pos);

    virtual bool Serialise(QDataStream& ds, bool isWrite = true);
};

Q_DECLARE_METATYPE(Rect);

#endif // RECT_H
