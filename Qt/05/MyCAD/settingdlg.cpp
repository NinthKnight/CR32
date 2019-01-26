#include "settingdlg.h"
#include "ui_settingdlg.h"
#include <qcolordialog.h>

SettingDlg::SettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDlg)
{
    ui->setupUi(this);
}

SettingDlg::~SettingDlg()
{
    delete ui;
}

void SettingDlg::on_pushButton_clicked()
{
    QColorDialog dlg;

    dlg.exec();

    m_color = dlg.selectedColor();

    QString qStyle = QString("background-color: rgb(%1, %2, %3);")
            .arg(m_color.red())
            .arg(m_color.green())
            .arg(m_color.blue());


    ui->pushButton->setStyleSheet(qStyle);
}
