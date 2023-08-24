#include "mountfrompathdialog.h"
#include "ui_mountfrompathdialog.h"

MountFromPathDialog::MountFromPathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MountFromPathDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Mount from path");

    m_mountingPath = "";
    m_fsDlg = new QFileDialog;
    m_fsDlg->setFileMode(QFileDialog::ExistingFile);

    m_mountDlg = new QFileDialog;
    m_mountDlg->setFileMode(QFileDialog::Directory);

    // ZWEITES EINGABEFELD MIT PFAD ZU DEM ORDNER IN DEM DAS FILESYSTEM VERSTECKT
   // also der Code von loadFilesystem
    /*
     *
     * loadFilesystemFromSteganoProvider nimmt
     * QFileDialog nutzen!!
     *
     * */

}

MountFromPathDialog::~MountFromPathDialog()
{

    delete m_fsDlg;
    delete m_mountDlg;
    delete m_adapter;
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


void MountFromPathDialog::on_mountPathLineEdit_textChanged(const QString &arg1)
{
    m_mountingPath = ui->mountPathLineEdit->text();
}


bool MountFromPathDialog::lightmodeOn() const
{
    return m_lightmodeOn;
}

void MountFromPathDialog::setLightmodeOn(bool newLightmodeOn)
{
    m_lightmodeOn = newLightmodeOn;

    if (this->m_lightmodeOn == true){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->mountPathLineEdit->setStyleSheet("background-color: #fafafa; color: #111111; border: 1px solid #1073b4; border-radius: 5px; padding: 2px 5px;");
        ui->filesystemPathLineEdit->setStyleSheet("background-color: #fafafa; color: #111111; border: 1px solid #1073b4; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); padding: 5px; color: white; padding: 2px 7px ; ");
        ui->label->setStyleSheet("background-color: transparent; color: #111111; ");
        ui->label->setStyleSheet("background-color: transparent; color: #111111; ");
        ui->pleaseTypeInLabel->setStyleSheet("background-color: transparent; color: #111111; ");
        m_fsDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);}");
        m_mountDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);}");

    }

    if (this->m_lightmodeOn == false) {

        this->setStyleSheet("background-color: #111111; color: #fafafa;");
        ui->mountPathLineEdit->setStyleSheet("background-color: #444444; color: white; border: 1px solid #607cff; border-radius: 5px; padding: 2px 5px;");
        ui->filesystemPathLineEdit->setStyleSheet("background-color: #444444; color: white; border: 1px solid #607cff; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; padding: 2px 7px ; ");
        ui->label->setStyleSheet("background-color: #444444; color: white; ");
        ui->pleaseTypeInLabel->setStyleSheet("background-color: #444444; color: white; ");
        m_fsDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;}");
        m_mountDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;}");

    }

}




void MountFromPathDialog::on_filesystemPathLineEdit_textChanged(const QString &arg1)
{
    m_filesystemPath = ui->filesystemPathLineEdit->text();
}


void MountFromPathDialog::on_browseDirButton_clicked()
{
    if (m_mountDlg->exec() == QDialog::Accepted) {

        m_mountingPath = m_mountDlg->selectedFiles().at(0);
        std::string s = m_mountingPath.toStdString();
        m_adapter = new SteganoFsAdapter(m_mountingPath.toStdString());

        ui->mountPathLineEdit->setText(m_mountingPath);

    } else {
        //ui->pleaseMakeSureLabel->setText(ui->pleaseMakeSureLabel->text() + "\n\n WARNING: no legit file selected!");
    }
}


void MountFromPathDialog::on_browseFsButton_clicked()
{
    if (m_fsDlg->exec() == QDialog::Accepted) {

        m_filesystemPath = m_fsDlg->selectedFiles().at(0);
        std::string s = m_filesystemPath.toStdString();

        ui->filesystemPathLineEdit->setText(m_filesystemPath);

        } else {
        //ui->pleaseMakeSureLabel->setText(ui->pleaseMakeSureLabel->text() + "\n\n WARNING: no legit file selected!");
    }

}

SteganoFsAdapter *MountFromPathDialog::adapter() const
{
        return m_adapter;
}

void MountFromPathDialog::setAdapter(SteganoFsAdapter *newAdapter)
{
        m_adapter = newAdapter;
}

