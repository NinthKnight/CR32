#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pActGroup = new QActionGroup(this);

    m_pActGroup->addAction(ui->act_line);
    m_pActGroup->addAction(ui->act_ecl);
    m_pActGroup->addAction(ui->act_rect);

    m_FrameWnd =  QSharedPointer<FrameWnd>(new FrameWnd(this, ui));

    m_FrameWnd->setAutoFillBackground(true);
    m_FrameWnd->setBackgroundRole(QPalette::Window);

    m_FrameWnd->resize(400, 300);

    setCentralWidget(m_FrameWnd.data());
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_act_line_triggered()
{

}
