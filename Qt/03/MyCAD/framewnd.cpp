#include "framewnd.h"
#include <qpainter.h>
#include <qdebug.h>
#include <QMouseEvent>
#include "ui_mainwindow.h"

FrameWnd::FrameWnd(QWidget *parent, Ui::MainWindow *u) : QWidget(parent)
{
    ui = u;
}

void FrameWnd::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

//    QPen pen(QColor(255, 0, 0));

//    painter.setPen(pen);

    //绘制链表中的图形
    for(auto shape : m_ShapeLst){

        shape->Draw(painter);
    }

    //绘制当前正在画的图形
    //painter.drawLine(m_ptBegin, m_ptEnd);

    if (ui->act_line->isChecked()){

        painter.drawLine(m_ptBegin, m_ptEnd);
    }
    else if(ui->act_rect->isChecked()){

        QSharedPointer<Rect>(new Rect(m_ptBegin, m_ptEnd))->Draw(painter);
    }

}

void FrameWnd::mousePressEvent(QMouseEvent *event)
{
    m_ptBegin = event->pos();

    qDebug() << "mousePressEvent:" << m_ptBegin << endl;
}

void FrameWnd::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "mouseMoveEvent" << endl;

    m_ptEnd = event->pos();

    //qDebug() << "mouseReleaseEvent:" << m_ptEnd << endl;

    repaint();
}

void FrameWnd::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "mouseReleaseEvent" << endl;

    m_ptEnd = event->pos();

    if (ui->act_line->isChecked()){

        m_ShapeLst.push_front(QSharedPointer<line>(new line(m_ptBegin, m_ptEnd)));
    }
    else if(ui->act_rect->isChecked()){

        m_ShapeLst.push_front(QSharedPointer<Rect>(new Rect(m_ptBegin, m_ptEnd)));
    }
    else if(ui->act_ecl->isChecked()){

        //m_ShapeLst.push_front(QSharedPointer<eclipse>(new eclipse(m_ptBegin, m_ptEnd)));
    }




    qDebug() << "mouseReleaseEvent:" << m_ptEnd << endl;

    repaint();
}

