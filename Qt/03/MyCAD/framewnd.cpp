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

    //绘制链表中的图形
    for(auto shape : m_ShapeLst)
    {

        shape->Draw(painter);
    }

    if (ui->act_line->isChecked())
    {
        painter.drawLine(m_ptBegin, m_ptEnd);
    }
    else if(ui->act_rect->isChecked())
    {

        QSharedPointer<Rect>(new Rect(m_ptBegin, m_ptEnd))->Draw(painter);
    }

}

void FrameWnd::mousePressEvent(QMouseEvent *event)
{
    m_ptBegin = event->pos();

}

void FrameWnd::mouseMoveEvent(QMouseEvent *event)
{

    m_ptEnd = event->pos();

    repaint();
}

void FrameWnd::mouseReleaseEvent(QMouseEvent *event)
{
    m_ptEnd = event->pos();

    if (ui->act_line->isChecked()){

        m_ShapeLst.push_front(QSharedPointer<line>(new line(m_ptBegin, m_ptEnd)));
    }
    else if(ui->act_rect->isChecked()){

        m_ShapeLst.push_front(QSharedPointer<Rect>(new Rect(m_ptBegin, m_ptEnd)));
    }
    else if(ui->act_ecl->isChecked()){

        m_ShapeLst.push_front(QSharedPointer<Eclipse>(new Eclipse(m_ptBegin, m_ptEnd)));
    }


    repaint();
}

