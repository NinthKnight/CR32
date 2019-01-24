#include "line.h"


line::line(QPoint &ptBegin, QPoint &ptEnd)
{
    m_ptBegin = ptBegin;
    m_ptEnd = ptEnd;
}

bool line::Draw(QPainter &painter)
{

    painter.drawLine(m_ptBegin, m_ptEnd);
    return true;
}
