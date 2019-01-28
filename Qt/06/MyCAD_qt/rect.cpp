#include "rect.h"
#include <windows.h>


Rect::Rect(QPoint &ptBegin, QPoint &ptEnd)
{
    m_ptBegin = ptBegin;
    m_ptEnd = ptEnd;
}

bool Rect::Draw(QPainter &painter)
{
    if(!m_IsSel){
        QRectF rectangle(m_ptBegin, m_ptEnd);
        painter.drawRect(rectangle);
    }else{
       QPen pen(QColor(255, 0, 0));

       QPen oldPen = painter.pen();
       painter.setPen(pen);
       QRectF rectangle(m_ptBegin, m_ptEnd);
       painter.drawRect(rectangle);
       painter.setPen(oldPen);
    }

    return true;
}

bool Rect::IsSelect(QPoint &pos)
{
    HRGN hRgn = CreateRectRgn(m_ptBegin.x(), m_ptBegin.y(),
                              m_ptEnd.x(), m_ptEnd.y());
    return PtInRegion(
                hRgn,
                pos.x(),
                pos.y()
                );
}

bool Rect::Serialise(QDataStream &ds, bool isWrite)
{
    if (isWrite){
        ds  << m_ptBegin << m_ptEnd;
    }
    else{
        ds >> m_ptBegin >> m_ptEnd;
    }

    return true;
}
