#include "createramdiskdialog.h"
#include "ui_createramdiskdialog.h"
#include <QDebug>
#include "mainwindow.h"

CreateRamdiskDialog::CreateRamdiskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRamdiskDialog)
{
    ui->setupUi(this);
    this->value = ui->ramdiskSizeSpinBox->value();

}

CreateRamdiskDialog::~CreateRamdiskDialog()
{
    delete ui;
}

void CreateRamdiskDialog::on_buttonBox_accepted()
{
    SteganoFsAdapter steganoFsAdapter("/example/path/to/pictures");
    qDebug() << "New Ramdisk created: " <<  steganoFsAdapter.formatNewRamdisk(ui->ramdiskSizeSpinBox->value());

    qDebug() << "New Ramdisk created with size " << ui->ramdiskSizeSpinBox->value() ;

}


void CreateRamdiskDialog::on_buttonBox_rejected()
{
    qDebug() << "No Ramdisk created. " ;

}

int CreateRamdiskDialog::getValue(){
    return value;
}

