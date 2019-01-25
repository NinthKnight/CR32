#include "eclipse.h"

Eclipse::Eclipse(QPoint &ptBegin, QPoint &ptEnd)
{
    m_ptBegin = ptBegin;
    m_ptEnd = ptEnd;
}

bool Eclipse::Draw(QPainter &painter)
{
    QRectF rectangle(m_ptBegin, m_ptEnd);
    painter.drawEllipse(rectangle);
    return true;
}
