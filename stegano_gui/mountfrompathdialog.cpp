#include "mountfrompathdialog.h"
#include "ui_mountfrompathdialog.h"

MountFromPathDialog::MountFromPathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MountFromPathDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Mount from path");

    m_mountingPath = "";
    m_status = "";
}

MountFromPathDialog::~MountFromPathDialog()
{
    delete ui;
}

void MountFromPathDialog::setMountingPath(const QString &newMountingPath)
{
    m_mountingPath = newMountingPath;
}

QString MountFromPathDialog::mountingPath() const
{
    return m_mountingPath;
}

void MountFromPathDialog::on_mountPathLineEdit_textChanged(const QString &arg1)
{
    m_mountingPath = ui->mountPathLineEdit->text();
}

bool MountFromPathDialog::lightmodeon() const
{
    return m_lightmodeon;
}

void MountFromPathDialog::setLightmodeon(bool newLightmodeon)
{
    m_lightmodeon = newLightmodeon;

    if (this->m_lightmodeon == true){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->mountPathLineEdit->setStyleSheet("background-color: transparent; color: #111111; border: 1px solid #1073b4; border-radius: 15px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("background-color: #1073b4; color: white; padding: 2px 7px ; ");
        ui->pleaseTypeInLabel ->setStyleSheet("background-color: transparent; color: #111111; ");




    }

    if (this->m_lightmodeon == false) {

        this->setStyleSheet("background-color: #111111; color: #fafafa;");
        ui->mountPathLineEdit->setStyleSheet("background-color: transparent; color: black; border: 1px solid #607cff; border-radius: 15px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("background-color: #607cff; color: white; padding: 2px 7px ; ");
        ui->pleaseTypeInLabel ->setStyleSheet("background-color: transparent; color: black; ");

    }
}



