#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <Tlhelp32.h>
#include <QMessageBox>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QObject::connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(on_pushButton2_clicked()));

    QObject::connect(this, SIGNAL(test2(int, char)), this, SLOT(onTest2(int, char)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //MessageBox(0,0,0,0);
//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.exec();

    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    if (ret == QMessageBox::Save){
        qDebug() << "QMessageBox::Save" << endl;
    }
}

bool MainWindow::EnumProcess(){

    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapShot == INVALID_HANDLE_VALUE){
           return false;
    }

    BOOL           bRet      = FALSE;
    PROCESSENTRY32 pe32      = {0};

    pe32.dwSize = sizeof(PROCESSENTRY32);

    //  Walk the snapshot of the processes, and for each process,
    //  display information.

    if (Process32First(hSnapShot, &pe32))
    {
        int nRow = 0;

        do
        {
            std::wstring strName = pe32.szExeFile;
            QString str2 = QString::fromStdWString(strName);

            QString str = QString("pid: %1 name: %2").arg(pe32.th32ProcessID).arg(str2);

            qDebug() <<  str << endl;

            ui->tableWidget->insertRow(nRow);
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(pe32.th32ProcessID));
            ui->tableWidget->setItem(nRow, 0, newItem);

            QTableWidgetItem *newItem2 = new QTableWidgetItem(tr("%1").arg(str2));
            ui->tableWidget->setItem(nRow++, 1, newItem2);
        }
        while (Process32Next(hSnapShot, &pe32));
        bRet = TRUE;
    }
    else
        bRet = FALSE;    // could not walk the list of processes

    // Do not forget to clean up the snapshot object.

    CloseHandle (hSnapShot);
    return (bRet);
}




void MainWindow::on_pushButton2_clicked()
{
    qDebug() << "on_pushButton2_clicked" << endl;


    EnumProcess();
//    QMessageBox::warning(this, "你好", "你好");

//    //MessageBoxA(NULL, "你好", "你好", 0);

//    emit test2(12, 'a');









}


void MainWindow::onTest2(int n, char ch)
{
    qDebug() << "onTest2" << n << ch << endl;
}
