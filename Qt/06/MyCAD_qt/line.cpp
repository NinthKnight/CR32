#include "line.h"
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QPolygon>

line::line(QPoint &ptBegin, QPoint &ptEnd)
{
    m_ptBegin = ptBegin;
    m_ptEnd = ptEnd;
}

bool line::Draw(QPainter &painter)
{
    if(!m_IsSel){
       painter.drawLine(m_ptBegin, m_ptEnd);
    }else{
       QPen pen(QColor(255, 0, 0));

       QPen oldPen = painter.pen();
       painter.setPen(pen);
       painter.drawLine(m_ptBegin, m_ptEnd);
       painter.setPen(oldPen);
    }

    return true;
}

bool line::IsSelect(QPoint &pos)
{
//    QGraphicsLineItem lineItem(QLine(m_ptBegin, m_ptEnd));

//    return lineItem.contains(pos);

    QVector<QPoint> points;
    points.push_back(QPoint(m_ptBegin.x() + 5, m_ptBegin.y() - 5));
    points.push_back(QPoint(m_ptBegin.x() - 5, m_ptBegin.y() + 5));
    points.push_back(QPoint(m_ptEnd.x() - 5, m_ptEnd.y() + 5));
    points.push_back(QPoint(m_ptEnd.x() + 5, m_ptEnd.y() - 5));
    QPolygon polygon(points);

    QGraphicsPolygonItem polygonItem(polygon);

    return polygonItem.contains(pos);
}

bool line::Serialise(QDataStream &ds, bool isWrite)
{
    if (isWrite){
        ds << m_ptBegin << m_ptEnd;
    }
    else{
        ds >> m_ptBegin >> m_ptEnd;
    }

    return true;
}
