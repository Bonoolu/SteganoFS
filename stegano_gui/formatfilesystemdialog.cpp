#include "formatfilesystemdialog.h"
#include "ui_formatfilesystemdialog.h"

FormatFileSystemDialog::FormatFileSystemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormatFileSystemDialog)
{
    ui->setupUi(this);

    m_filesystemPath = "";
    m_fsDlg = new QFileDialog;
    m_fsDlg->setFileMode(QFileDialog::ExistingFile);

}

FormatFileSystemDialog::~FormatFileSystemDialog()
{
    delete ui;
}

QString FormatFileSystemDialog::filesystemPath() const
{
    return m_filesystemPath;
}

void FormatFileSystemDialog::setFilesystemPath(const QString &newFilesystemPath)
{
    m_filesystemPath = newFilesystemPath;
}


bool FormatFileSystemDialog::lightmodeOn() const
{
    return m_lightmodeOn;
}

void FormatFileSystemDialog::setLightmodeOn(bool newLightmodeOn)
{
    m_lightmodeOn = newLightmodeOn;

    if (this->m_lightmodeOn == true){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->fileSystemLineEdit->setStyleSheet("background-color: #fafafa; color: #111111; border: 1px solid #1073b4; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); padding: 5px; color: white; padding: 2px 7px ; ");
        ui->fileSystemSizeLabel->setStyleSheet("background-color: transparent; color: #111111; ");
        ui->pleaseSelectLabel->setStyleSheet("background-color: transparent; color: #111111; ");
        m_fsDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);}");


    }

    if (this->m_lightmodeOn == false) {

        this->setStyleSheet("background-color: #111111; color: #fafafa;");

        ui->fileSystemLineEdit->setStyleSheet("background-color: #444444; color: white; border: 1px solid #607cff; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; padding: 2px 7px ; ");
        ui->fileSystemSizeLabel->setStyleSheet("background-color: #444444; color: white; ");
        ui->pleaseSelectLabel->setStyleSheet("background-color: #444444; color: white; ");
        m_fsDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;}");

    }

}




void FormatFileSystemDialog::on_fileSystemLineEdit_textChanged(const QString &arg1)
{
    m_filesystemPath = ui->fileSystemLineEdit->text();
}


void FormatFileSystemDialog::on_browseButton_clicked()
{
    if (m_fsDlg->exec() == QDialog::Accepted) {

        m_filesystemPath = m_fsDlg->selectedFiles().at(0);
        std::string s = m_filesystemPath.toStdString();
        ui->fileSystemSizeLabel->setText(QString("File system size: \t\t")); /* + filesystemsize */
        ui->fileSystemLineEdit->setText(m_filesystemPath);

    } else {

    }

}

SteganoFsAdapter *FormatFileSystemDialog::adapter() const
{
    return m_adapter;
}

void FormatFileSystemDialog::setAdapter(SteganoFsAdapter *newAdapter)
{
    m_adapter = newAdapter;
}



void FormatFileSystemDialog::on_buttonBox_accepted()
{

}

