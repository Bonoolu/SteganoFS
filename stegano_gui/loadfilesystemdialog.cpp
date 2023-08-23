#include "loadfilesystemdialog.h"
#include "ui_loadfilesystemdialog.h"

LoadFileSystemDialog::LoadFileSystemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadFileSystemDialog)
{
    ui->setupUi(this);

    m_fileDlg = new QFileDialog;
    m_fileDlg->setFileMode(QFileDialog::ExistingFile);
}

LoadFileSystemDialog::~LoadFileSystemDialog()
{
    delete ui;
    delete m_fileDlg;
}

QString LoadFileSystemDialog::loadingPath() const
{
    return m_loadingPath;
}

void LoadFileSystemDialog::setLoadingPath(const QString &newLoadingPath)
{
    m_loadingPath = newLoadingPath;
    ui->loadPathLineEdit->setText(m_loadingPath);

}

void LoadFileSystemDialog::setLightmodeon(bool b)
{
    m_lightmodeon = b;

    if (this->m_lightmodeon == true){
        this->setStyleSheet("background-color: #fafafa; color: #111111;");
        ui->loadPathLineEdit->setStyleSheet("background-color: #fafafa; color: #111111; border: 1px solid #1073b4; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); padding: 5px; color: white; padding: 2px 7px ; ");
        ui->pleaseMakeSureLabel->setStyleSheet("background-color: transparent; color: #111111; ");
        ui->typeInOrSelectLabel->setStyleSheet("background-color: transparent; color: #111111; ");
        m_fileDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891);}");

    }

    if (this->m_lightmodeon == false) {

        this->setStyleSheet("background-color: #111111; color: #fafafa;");
        ui->loadPathLineEdit->setStyleSheet("background-color: #444444; color: white; border: 1px solid #607cff; border-radius: 5px; padding: 2px 5px;");
        ui->buttonBox->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); border-radius: 5px; color: white; padding: 2px 7px ; ");
        ui->pleaseMakeSureLabel ->setStyleSheet("background-color: #444444; color: white; ");
        ui->pleaseMakeSureLabel ->setStyleSheet("background-color: #444444; color: white; ");
        m_fileDlg->setStyleSheet("QPushButton {border-radius: 5px; background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); color: white;}");

    }
}

void LoadFileSystemDialog::on_buttonBox_accepted()
{

}


void LoadFileSystemDialog::on_fileBrowserButton_clicked()
{
    if (m_fileDlg->exec() == QDialog::Accepted) {

        m_loadingPath = m_fileDlg->selectedFiles().at(0);
        std::string s = m_loadingPath.toStdString();

        ui->loadPathLineEdit->setText(m_loadingPath);



    } else {
        //ui->pleaseMakeSureLabel->setText(ui->pleaseMakeSureLabel->text() + "\n\n WARNING: no legit file selected!");
    }
}

SteganoFsAdapter *LoadFileSystemDialog::adapter() const
{
    return m_adapter;
}

void LoadFileSystemDialog::setAdapter(SteganoFsAdapter *newAdapter)
{
    m_adapter = newAdapter;
}

