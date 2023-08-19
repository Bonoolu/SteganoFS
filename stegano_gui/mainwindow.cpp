#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QDialog>
#include <iostream>
#include "createramdiskdialog.h"
#include <string>
#include <thread>

SteganoFsAdapter steganoFsAdapter("/home/minaboo/Bilder/example/");

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Stegano File Explorer");

    m_CRDdlg = new CreateRamdiskDialog;
    m_CRDdlg->setLightmodeOn(false);

    m_DefragDlg = new DefragmentDialog;
    m_DefragDlg->setLightmode_on(false);
    //m_DefragDlg->setAdapter(&steganoFsAdapter);


    m_preview_on = 0;

    m_lightmode_on = 0;

    ui->statusbar->show();

    // DARK STYLE
    QFile file(":/assets/stylesheet/Darkeum.qss");
    file.open(QFile::ReadOnly);

    m_darkstyle = QLatin1String(file.readAll());

    QFile file2(":/assets/stylesheet/Darkeum_light.qss");
    file2.open(QFile::ReadOnly);

    m_lightstyle = QLatin1String(file2.readAll());

    // LEFT SIDE - DISPLAYING FOLDERS
    QString sPath = "D:\\Mina\\Bilder\\SFS_example\\";
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath(sPath);

    ui->treeView->setModel(m_dirmodel);
    ui->treeView->setSortingEnabled(true);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    // RIGHT SIDE - DISPLAYING FILES

    m_filemodel = new QFileSystemModel(this);
    m_filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    m_filemodel->setRootPath(sPath);

    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(m_filemodel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->searchLineEdit->setPlaceholderText("Search...");



    ui->listWidget->hide();
    ui->listWidget->setSortingEnabled(true);

    ui->previewLabel->hide();



    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200,150));
    ui->listWidget->setResizeMode(QListWidget::Adjust);


    // CONNECT SLOTS & SIGNALS

    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);

    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::refreshView);

    // connect(m_CRDdlg, &CreateRamdiskDialog::accepted, this, &MainWindow::createNewRamdisk);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateListWidget(QString sPath){

    ui->listWidget->clear();

    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200,150));
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setSpacing(20);

    QList<QString> path_list;
    QModelIndex parentIndex = m_filemodel->index(sPath);
    int numRows = m_filemodel->rowCount(parentIndex);
    qDebug() << "Dateien in " + sPath << ": " << numRows << Qt::endl;


    for (int row = 0; row < numRows; ++row) {
        QModelIndex childIndex = m_filemodel->index(row, 0, parentIndex);
        QString path = m_filemodel->data(childIndex).toString();
        path_list.append(path);
    }

    qDebug() << path_list << Qt::endl;

    for (QString file : path_list) {
        QString fullPath = sPath + "/" + file;
        QImage img = QImage(fullPath);
        //qiimg = img.scaled(200,150,Qt::KeepAspectRatio);
        QPixmap pixmap = QPixmap::fromImage(img, Qt::AutoColor);
        QListWidgetItem *item = new QListWidgetItem(QIcon(pixmap), QString(file));
        item->setSizeHint(QSize(210, 170));
        qDebug() << fullPath << Qt::endl;
        ui->listWidget->addItem(item);
    }

    qDebug() << path_list << Qt::endl;

    path_list.clear();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    m_currentDir = m_dirmodel->fileInfo(index).absoluteFilePath();
    QString sPath = m_currentDir;
    qDebug() << "sPath: " + sPath << Qt::endl;
    ui->tableView->setRootIndex(m_filemodel->setRootPath(sPath));
    //ui->listWidget->setRootIndex(m_filemodel->setRootPath(sPath));
    ui->pathLineEdit->setText(sPath);

    updateListWidget(sPath);

}

void MainWindow::handleSearchTextChanged(const QString &searchText)
{
    m_filemodel->setNameFilters(QStringList() << "*" + searchText + "*");
    m_filemodel->setNameFilterDisables(false);
    updateListWidget(m_currentDir);
}


void MainWindow::refreshView()
{
    ui->tableView->reset();
    ui->listWidget->clear();
}

void MainWindow::on_DisplayComboBox_currentIndexChanged(int index)
{

    if (index == 1){
        ui->tableView->hide();
        ui->listWidget->show();

        ui->sortComboBox->setDisabled(false);
    } else {
        ui->listWidget->hide();
        ui->tableView->show();
        ui->sortComboBox->setDisabled(true);
    }

}




void MainWindow::on_pathLineEdit_editingFinished()
{
    QString newPath = ui->pathLineEdit->text();
    ui->treeView->setRootIndex(m_dirmodel->setRootPath(newPath));
    ui->tableView->setRootIndex(m_filemodel->setRootPath(newPath));
    updateListWidget(newPath);

}





void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

    //ui->previewLabel->setPixmap(current->icon());
    QString fullPath = m_currentDir + "/" + current->text();
    qDebug() << "Test currentItemChanged : " << fullPath;
    QImage img = QImage(fullPath);
    //img = img.scaled(500,250,Qt::KeepAspectRatio);
    QPixmap pixmap = QPixmap::fromImage(img, Qt::AutoColor);
    ui->previewLabel->setMaximumWidth(500);
    ui->previewLabel->setPixmap(pixmap);
    ui->previewLabel->setScaledContents(true);
    //ui->previewLabel->setText("PREVIEW");
    /*QListWidgetItem *currentpreview = new QListWidgetItem(QIcon(current->icon()));
    currentpreview->setSizeHint(QSize(400, 400));
    qDebug() << fullPath << Qt::endl;
    ui->previewWidget->addItem(currentpreview);*/

}


void MainWindow::on_previewToolButton_clicked()
{
    if (m_preview_on == 0){

        ui->centralwidget->setBaseSize(QSize(ui->centralwidget->width() + 500, ui->centralwidget->height()));

        ui->previewLabel->show();
        m_preview_on = 1;

    } else {

        ui->centralwidget->setBaseSize(QSize(ui->centralwidget->width() - 500, ui->centralwidget->height()));

        ui->previewLabel->hide();
        m_preview_on = 0;
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{

}


void MainWindow::on_darkModePushButton_clicked()
{

    if (m_lightmode_on == 0){
        qApp->setStyleSheet(m_lightstyle);
        m_lightmode_on = 1;
        m_CRDdlg->setLightmodeOn(true);
        m_DefragDlg->setLightmode_on(true);
        qDebug() << m_CRDdlg->lightmodeOn() << "(lightmode CRDdlg) \n";

        ui->newFolderPushButton->setIcon(QIcon(":/assets/img/light/folder.png"));
        ui->newFilePushButton->setIcon(QIcon(":/assets/img/light/document.png"));
        ui->deletePushButton->setIcon(QIcon(":/assets/img/light/delete.png"));
        ui->cutPushButton->setIcon(QIcon(":/assets/img/light/scissors.png"));
        ui->copyPushButton->setIcon(QIcon(":/assets/img/light/copy.png"));
        ui->pastePushButton->setIcon(QIcon(":/assets/img/light/paste.png"));
        ui->previewToolButton->setIcon(QIcon(":/assets/img/light/preview.png"));
        ui->darkModePushButton->setIcon(QIcon(":/assets/img/light/night-mode.png"));


    } else {

        qApp->setStyleSheet(m_darkstyle);
        m_lightmode_on = 0;
        m_CRDdlg->setLightmodeOn(false);
        m_DefragDlg->setLightmode_on(false);

        ui->newFolderPushButton->setIcon(QIcon(":/assets/img/folder.png"));
        ui->newFilePushButton->setIcon(QIcon(":/assets/img/document.png"));
        ui->deletePushButton->setIcon(QIcon(":/assets/img//delete(1).png"));
        ui->cutPushButton->setIcon(QIcon(":/assets/img/scissors(1).png"));
        ui->copyPushButton->setIcon(QIcon(":/assets/img/copy.png"));
        ui->pastePushButton->setIcon(QIcon(":/assets/img/paste.png"));
        ui->previewToolButton->setIcon(QIcon(":/assets/img/preview (2).png"));
        ui->darkModePushButton->setIcon(QIcon(":/assets/img/light-bulb.png"));
        qDebug() << m_CRDdlg->lightmodeOn() << "(lightmode CRDdlg) \n";
    }

}


/*
    bool formatNewRamdisk(size_t diskSize);
    bool loadRamdisk();
    bool mount(const std::string& mntPoint);
    bool unloadRamdisk();
    bool umount();
    float getFragmentationInPercent();
    std::vector<size_t> getFilesystemVector();
    bool checkFilesystemIntegrity();
    bool defragmentateFilesystem();
    struct statfs getFilesystemInfo();

*/


void MainWindow::on_actionCreate_new_triggered()
{

    if (m_CRDdlg->exec() == QDialog::Accepted) {
        steganoFsAdapter.createNewFilesystem(m_CRDdlg->getValue());
        ui->statusbar->showMessage(QString("New Ramdisk created! Size: ") + QString::number(m_CRDdlg->getValue()), 10000);
    } else {
        std::cout << "No Ramdisk created. ";
    }


}



void MainWindow::on_actionLoad_triggered()
{
    std::string s = steganoFsAdapter.steganoImageFolder();
    steganoFsAdapter.loadFilesytemFromSteganoProvider();
    ui->statusbar->showMessage(QString("Filesystem loaded: ") + QString::fromStdString(s), 10000);
}




void MainWindow::on_actionDefragment_triggered()
{
    //float fragmentation = steganoFsAdapter.getFragmentationInPercent();
    m_DefragDlg->setFragmentation(steganoFsAdapter.getFragmentationInPercent());
    m_DefragDlg->exec();
}


void MainWindow::on_actionNeuer_Ordner_triggered()
{

}


void MainWindow::on_actionShow_Filesystem_information_triggered()
{

}


void MainWindow::on_actionMount_triggered()
{
    std::string s = steganoFsAdapter.steganoImageFolder() + "anything";

//    std::thread t1([steganoFsAdapter](){
//        steganoFsAdapter.mount(s);
//    });

    std::thread t1(steganoFsAdapter.mount(s));

    t1.join();

}


void MainWindow::on_actionUnmount_triggered()
{
    steganoFsAdapter.umount();
}

