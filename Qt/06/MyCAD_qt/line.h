#ifndef LINE_H
#define LINE_H

#include "ishape.h"

class line : public IShape
{
    Q_OBJECT
public:
    line(QPoint& ptBegin, QPoint& ptEnd);

    line(){
    }

    line(const line& obj){

        m_ptBegin = obj.m_ptBegin;
        m_ptEnd = obj.m_ptEnd;
    }


    bool Draw(QPainter& painter);
    virtual bool IsSelect(QPoint& pos);

    virtual bool Serialise(QDataStream& ds, bool isWrite = true);




};

Q_DECLARE_METATYPE(line);

#endif // LINE_H
