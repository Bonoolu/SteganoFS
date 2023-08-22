#include "createramdiskdialog.h"
#include "ui_createramdiskdialog.h"
#include <QDebug>
#include "mainwindow.h"

CreateRamdiskDialog::CreateRamdiskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRamdiskDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Create a new File System");
    m_value = 0;

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
{       m_lightmodeon = b;
    if (this->m_lightmodeon == true){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->newRamdiskLabel->setStyleSheet("background-color: transparent; color: #111111;");
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); padding: 5px; color: white; padding: 2px 7px ; ");
        ui->ramdiskSizeSpinBox->setStyleSheet("background-color: transparent; color: #111111;");




    }

    if (this->m_lightmodeon == false) {

        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; padding: 2px 7px ; ");
        ui->newRamdiskLabel->setStyleSheet("background-color: transparent; color: black;");
        ui->ramdiskSizeSpinBox->setStyleSheet("background-color: transparent; color: black;");
        this->setStyleSheet("background-color: #111111; color: black;");

    }

}

bool CreateRamdiskDialog::lightmodeOn()
{
    return m_lightmodeon;
}


void CreateRamdiskDialog::on_ramdiskSizeSpinBox_valueChanged(int arg1)
{
    m_value = ui->ramdiskSizeSpinBox->value();
}

