#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "linefactroy.h"
#include "rectfactroy.h"
#include <qfiledialog.h>
#include <qdebug.h>
#include <qdatastream.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pActGroup = new QActionGroup(this);

    m_pActGroup->addAction(ui->act_line);
    m_pActGroup->addAction(ui->act_ecl);
    m_pActGroup->addAction(ui->act_rect);
    m_pActGroup->addAction(ui->act_sel);

    m_FrameWnd =  QSharedPointer<FrameWnd>(new FrameWnd(this, ui));

    m_FrameWnd->setAutoFillBackground(true);
    m_FrameWnd->setBackgroundRole(QPalette::Window);

    m_FrameWnd->resize(400, 300);

    setCentralWidget(m_FrameWnd.data());

    //绑定图形选择
    QObject::connect(m_pActGroup,
                     SIGNAL(triggered(QAction*)),
                     m_FrameWnd.data(),
                     SLOT(OnTriggered(QAction*)));

//    QObject::connect(ui->act_line,
//                     SIGNAL(triggered(QAction*)),
//                     m_FrameWnd.data(),
//                     SLOT(OnTriggered(QAction*)));

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_act_line_triggered()
{
    m_FrameWnd->setCurFactroy(new LineFactroy());
}

void MainWindow::on_act_ecl_triggered()
{
    m_FrameWnd->setCurFactroy(nullptr);
}

void MainWindow::on_act_rect_triggered()
{
     m_FrameWnd->setCurFactroy(new RectFactroy());
}

void MainWindow::on_act_sel_triggered()
{
    m_FrameWnd->setCurFactroy(nullptr);
}


void MainWindow::on_act_open_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this);

    qDebug() << fileName << endl;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly )){
        return ;
    }

    //保存当前的数据
    QDataStream ds(&file);
    //QTextStream ds(&file);

    m_FrameWnd->Serialise(ds, false);

    file.close();

}


void MainWindow::on_act_save_triggered()
{
    //保存
    QString fileName = QFileDialog::getSaveFileName(this);

    qDebug() << "Save File:" << fileName << endl;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)){
        return ;
    }

    //保存当前的数据
    QDataStream ds(&file);
    //QTextStream ds(&file);

    m_FrameWnd->Serialise(ds);

    file.close();
}
