#include "defragmentdialog.h"
#include "ui_defragmentdialog.h"
#include <QDebug>

DefragmentDialog::DefragmentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefragmentDialog)
{
    ui->setupUi(this);
    setWindowTitle("Defragment");
}

DefragmentDialog::~DefragmentDialog()
{
    delete ui;
}

void DefragmentDialog::setLightmodeOn(bool newLightmodeOn)
{
    m_lightmodeOn = newLightmodeOn;

    if (m_lightmodeOn) {
        setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #1073b4, stop: 1 #015891); border-radius: 5px; padding: 5px; color: white; padding: 2px 7px ; ");
    } else {
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0, stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; padding: 2px 7px ; ");
        setStyleSheet("background-color: #111111; color: #fafafa;");
    }
}

bool DefragmentDialog::lightmodeOn() const
{
    return m_lightmodeOn;
}

void DefragmentDialog::setFragmentation(float f)
{
    QString s = QString::number(f);
    ui->fragmentationPercentLabel->setText(s + "%");
}

void DefragmentDialog::on_pushButton_clicked()
{
    bool defragmentResult = m_adapter->defragmentateFilesystem();
    qDebug() << "Disk defragmented: " << QString::number(defragmentResult);

    if (defragmentResult) {
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
