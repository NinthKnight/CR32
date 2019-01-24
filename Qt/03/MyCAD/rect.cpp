#include "rect.h"



Rect::Rect(QPoint &ptBegin, QPoint &ptEnd)
{
    m_ptBegin = ptBegin;
    m_ptEnd = ptEnd;
}

bool Rect::Draw(QPainter &painter)
{
    QRectF rectangle(m_ptBegin, m_ptEnd);
    painter.drawRect(rectangle);

    return true;
}
