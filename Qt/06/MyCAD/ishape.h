#ifndef ISHAPE_H
#define ISHAPE_H
#include <QPoint>
#include <QPen>
#include <QBrush>
#include <QPainter>

class IShape
{
public:
    IShape();

    virtual bool Draw(QPainter& painter) = 0;

    virtual bool IsSelect(QPoint& pos) = 0;

    virtual bool Move(QPoint& ptBegin, QPoint& ptEnd){
          int deltaX = ptEnd.x() - ptBegin.x();
          int deltaY = ptEnd.y() - ptBegin.y();

          m_ptBegin.rx() += deltaX;
          m_ptBegin.ry() += deltaY;

          m_ptEnd.rx() += deltaX;
          m_ptEnd.ry() += deltaY;
    }

    void SetSelect(bool isSel){
        m_IsSel = isSel;
    }

    virtual bool Serialise(QDataStream& ds, bool isWrite = true) = 0;

protected:
    QPen m_pen;
    QBrush m_brush;
    bool m_IsSel;
    QPoint m_ptBegin;
    QPoint m_ptEnd;
};

#endif // ISHAPE_H
