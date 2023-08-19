#include "createramdiskdialog.h"
#include "ui_createramdiskdialog.h"
#include <QDebug>
#include "mainwindow.h"

CreateRamdiskDialog::CreateRamdiskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRamdiskDialog)
{
    ui->setupUi(this);
    m_value = 0;
    m_lightmodeon = 0;

}

CreateRamdiskDialog::~CreateRamdiskDialog()
{
    delete ui;
}

void CreateRamdiskDialog::on_buttonBox_accepted()
{

    emit accepted();

}


void CreateRamdiskDialog::on_buttonBox_rejected()
{
    qDebug() << "No Ramdisk created. " ;

}

int CreateRamdiskDialog::getValue(){
    return m_value;
}

void CreateRamdiskDialog::setLightmodeOn(bool b)
{
    m_lightmodeon = b;
}


void CreateRamdiskDialog::on_ramdiskSizeSpinBox_valueChanged(int arg1)
{
    m_value = ui->ramdiskSizeSpinBox->value();
}

