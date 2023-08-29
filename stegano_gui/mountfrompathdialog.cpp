#include <QCoreApplication>
#include "mountfrompathdialog.h"
#include "ui_mountfrompathdialog.h"

MountFromPathDialog::MountFromPathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MountFromPathDialog)
{

    // initializes a new MountFromPath Dialog (preset path for easier testing)

    ui->setupUi(this);
    this->setWindowTitle("Mount from path");

    m_mountingPath = "";
    m_fsDlg = new QFileDialog;
    m_fsDlg->setFileMode(QFileDialog::ExistingFile);
    m_fsDlg->setDirectory(QDir(QCoreApplication::applicationDirPath() + "/../examples/pictures").absolutePath());

    m_mountDlg = new QFileDialog;
    m_mountDlg->setFileMode(QFileDialog::Directory);
    m_fsDlg->setDirectory(QDir(QCoreApplication::applicationDirPath() + "/../examples/mnt").absolutePath());

    m_info = new QMessageBox;
    ui->filesystemPathLineEdit->setText(QDir(QCoreApplication::applicationDirPath() + "/../examples/pictures").absolutePath());
    ui->mountPathLineEdit->setText(QDir(QCoreApplication::applicationDirPath() + "/../examples/mnt").absolutePath());

}

MountFromPathDialog::~MountFromPathDialog()
{

    delete m_fsDlg;
    delete m_mountDlg;
    delete m_adapter;
    delete m_info;
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



QString MountFromPathDialog::filesystemPath() const
{
    return m_filesystemPath;
}

void MountFromPathDialog::setFilesystemPath(const QString &newFilesystemPath)
{
    m_filesystemPath = newFilesystemPath;
}




bool MountFromPathDialog::lightmodeOn() const
{
    return m_lightmodeOn;
}

void MountFromPathDialog::setLightmodeOn(bool newLightmodeOn)
{
    m_lightmodeOn = newLightmodeOn;

     // set colors depending on lightmode status

    if (this->m_lightmodeOn){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->mountPathLineEdit->setStyleSheet("background-color: #fafafa; color: #111111; border: 1px solid #1073b4; border-radius: 5px; padding: 2px 5px;");
        ui->filesystemPathLineEdit->setStyleSheet("background-color: #fafafa; color: #111111; border: 1px solid #1073b4; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); padding: 5px; color: white; padding: 2px 7px ; ");
        ui->label->setStyleSheet("background-color: transparent; color: #111111; ");
        ui->label->setStyleSheet("background-color: transparent; color: #111111; ");
        ui->pleaseTypeInLabel->setStyleSheet("background-color: transparent; color: #111111; ");
        m_fsDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);}");
        m_mountDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);}");
        m_info->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);} QMessageBox {background-color: #fafafa; color: #111111;}");

    }

    if (!this->m_lightmodeOn) {

        this->setStyleSheet("background-color: #111111; color: #fafafa;");
        ui->mountPathLineEdit->setStyleSheet("background-color: #444444; color: white; border: 1px solid #607cff; border-radius: 5px; padding: 2px 5px;");
        ui->filesystemPathLineEdit->setStyleSheet("background-color: #444444; color: white; border: 1px solid #607cff; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; padding: 2px 7px ; ");
        ui->label->setStyleSheet("background-color: #444444; color: white; ");
        ui->pleaseTypeInLabel->setStyleSheet("background-color: #444444; color: white; ");
        m_fsDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;}");
        m_mountDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;}");
        m_info->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;} QMessageBox {background-color: #111111; color: white;}");

    }

}


// User either selects a mounting path through typing in a path or by browsing a File Dialog

void MountFromPathDialog::on_browseDirButton_clicked()
{

    if (m_mountDlg->exec() == QDialog::Accepted) {

        m_mountingPath = m_mountDlg->selectedFiles().at(0);
        std::string s = m_mountingPath.toStdString();
        m_adapter = new SteganoFsAdapter(m_mountingPath.toStdString());

        ui->mountPathLineEdit->setText(m_mountingPath);

    } else {
        m_info->setText("Warning: No directory selected!");
        m_info->exec();
    }

}


void MountFromPathDialog::on_mountPathLineEdit_textChanged(const QString &arg1)
{
    m_mountingPath = ui->mountPathLineEdit->text();
}


// User either selects a file system through typing in a path or by browsing a File Dialog

void MountFromPathDialog::on_browseFsButton_clicked()
{

    if (m_fsDlg->exec() == QDialog::Accepted) {

        m_filesystemPath = m_fsDlg->selectedFiles().at(0);
        std::string s = m_filesystemPath.toStdString();

        ui->filesystemPathLineEdit->setText(m_filesystemPath);

        } else {
        m_info->setText("Warning: No filesystem selected!");
        m_info->exec();
    }

}

void MountFromPathDialog::on_filesystemPathLineEdit_textChanged(const QString &arg1)
{
    m_filesystemPath = ui->filesystemPathLineEdit->text();
}

SteganoFsAdapter *MountFromPathDialog::adapter() const
{
        return m_adapter;
}

void MountFromPathDialog::setAdapter(SteganoFsAdapter *newAdapter)
{
        m_adapter = newAdapter;
}

