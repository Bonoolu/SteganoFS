#include "defragmentdialog.h"
#include "ui_defragmentdialog.h"
#include <QDebug>

DefragmentDialog::DefragmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefragmentDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Defragment");
}

DefragmentDialog::~DefragmentDialog()
{
    delete ui;
}

void DefragmentDialog::setLightmode_on(bool newLightmode_on)
{
    m_lightmode_on = newLightmode_on;

    if (this->m_lightmode_on == true){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->buttonBox->setStyleSheet("background-color: #1073b4; color: white; padding: 2px 7px ; ");




    }

    if (this->m_lightmode_on == false) {

        ui->buttonBox->setStyleSheet("background-color: #607cff; color: white; padding: 2px 7px ; ");
        this->setStyleSheet("background-color: #111111; color: #fafafa;");

    }
}

bool DefragmentDialog::lightmode_on() const
{
    return m_lightmode_on;
}

void DefragmentDialog::setFragmentation(float f)
{
    QString s = QString::number(f);
    ui->fragmentationPercentLabel->setText(s + "%");
}

void DefragmentDialog::on_pushButton_clicked()
{   bool b = false;
    //qDebug() << "Disk defragmented: " << QString::number(m_adapter->defragmentateFilesystem());
    qDebug() << "Disk defragmented: " << QString::number(b);

    if (m_adapter->defragmentateFilesystem() == true){
        ui->actualStatusLabel->setStyleSheet("color: green;");
        ui->actualStatusLabel->setText("DONE");
    } else {
        ui->actualStatusLabel->setStyleSheet("color: red;");
        ui->actualStatusLabel->setText("ERROR");
    }

}

void DefragmentDialog::setAdapter(SteganoFsAdapter *newAdapter)
{
    m_adapter = newAdapter;
}

