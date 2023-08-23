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
#include <QThread>
#include <QMetaObject>
#include "../cpp-wrapper/SteganoFsAdapter.h"
#include <filesystem>
#include <QGraphicsScene>
#include <QFont>
#include <QRegularExpression>
#include <QFileInfo>
Q_DECLARE_METATYPE(SteganoFsAdapter*)


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Stegano File Explorer");

    //qRegisterMetaType(SteganoFsAdapter*);

//    QFont roboto(":/assets/fonts/Roboto-Medium.ttf");
//    QFont garet(":/assets/fonts/Garet-Book.ttf");
//    this->setFont(garet);

    m_CRDdlg = new CreateRamdiskDialog;
    m_CRDdlg->setLightmodeOn(false);

    m_DefragDlg = new DefragmentDialog;
    m_DefragDlg->setLightmode_on(false);

    m_MFPDlg = new MountFromPathDialog;
    m_MFPDlg->setLightmodeon(false);

    m_SFIdlg = new ShowFileSystemInfoDialog;
    m_SFIdlg->setLightmodeon(false);

    m_LFdlg = new LoadFileSystemDialog;
    m_LFdlg->setLightmodeon(false);

    m_movingHistory = new QList<QString>;
    m_stepsToGoBack = 0;


    m_currentFile = nullptr;
    m_worker = new Worker();
    m_thread = new QThread();

    m_worker->moveToThread(m_thread);

    m_preview_on = 0;

    m_lightmode_on = 0;

    m_pgv = new PreviewGraphicsView;
    m_previewPicture = new QGraphicsScene;

    ui->statusbar->show();

    // DARK/LIGHT STYLE
    QFile file(":/assets/stylesheet/Darkeum.qss");
    file.open(QFile::ReadOnly);

    m_darkstyle = QLatin1String(file.readAll());

    QFile file2(":/assets/stylesheet/Darkeum_light.qss");
    file2.open(QFile::ReadOnly);

    m_lightstyle = QLatin1String(file2.readAll());


    // BACK AND FORTH BUTTONS
    m_bafButtonsStyle_dark = "QPushButton {background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); height: 20px; width: 20px; border-radius: 15px;} QPushButton::disabled { background-color: #3f476b;} QPushButton::hover {background-color: #7990fc;} QPushButton::pressed {background-color: #899dfa;} )";
    m_bafButtonsStyle_light = "QPushButton {background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); height: 20px; width: 20px; border-radius: 15px;} QPushButton::disabled { background-color: #2e5e7d;} QPushButton::hover {background-color: #1e86c9;} QPushButton::pressed {background-color: #54a8de;} )";
    ui->backButton->setStyleSheet(m_bafButtonsStyle_dark);
    ui->forwardButton->setStyleSheet(m_bafButtonsStyle_dark);

    ui->backButton->setDisabled(true);
    ui->forwardButton->setDisabled(true);

    ui->actionUnmount->setDisabled(true);
    ui->actionDefragment->setDisabled(true);



    // LEFT SIDE - DISPLAYING FOLDERS
    QString sPath = "/home/minaboo/Bilder/example";
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath(sPath);
    m_currentDir = "";

    ui->treeView->setModel(m_dirmodel);
    ui->treeView->setSortingEnabled(true);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    // RIGHT SIDE - DISPLAYING FILES

    m_filemodel = new QFileSystemModel(this);

    m_filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    m_filemodel->setRootPath(sPath);

    ui->tableView->hide();
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(m_filemodel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->searchLineEdit->setPlaceholderText("Search...");
    ui->DisplayComboBox->setDisabled(true);


    //ui->listWidget->hide();
    ui->listWidget->setSortingEnabled(true);

    ui->horizontalLayout_2->addWidget(m_pgv);

    m_pgv->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    m_pgv->hide();



    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200,150));
    ui->listWidget->setResizeMode(QListWidget::Adjust);


    // CONNECT SLOTS & SIGNALS

    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);

    connect(m_pgv, &PreviewGraphicsView::refreshScene, this, &MainWindow::refreshPreviewOnResize);

    m_movingHistory->append(m_currentDir);

}

MainWindow::~MainWindow()
{
    m_thread->requestInterruption();
    m_thread->quit();
    m_thread->wait();

    delete m_CRDdlg;
    delete m_MFPDlg;
    delete m_DefragDlg;
    delete m_SFIdlg;

    delete m_movingHistory;
    delete m_thread;
    delete m_worker;
    delete m_pgv;
    delete m_previewPicture;
    delete ui;
}


void MainWindow::updateListWidget(QString sPath){

    ui->listWidget->clear();

    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200,150));
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setSpacing(20);

    QList<QString> path_list;
    QModelIndex parentIndex = m_filemodel->index(m_currentDir);
    int numRows = m_filemodel->rowCount(parentIndex);



    for (int row = 0; row < numRows; ++row) {
        QModelIndex childIndex = m_filemodel->index(row, 0, parentIndex);
        QString path = m_filemodel->data(childIndex).toString();
        path_list.append(path);
    }


    for (QString file : path_list) {
        QString fullPath = sPath + "/" + file;
        QPixmap pixmap;


        if ( file.contains(QRegExp(".jpg")) |  file.contains(QRegExp(".bmp")) | file.contains(QRegExp(".png")) | file.contains(QRegExp(".gif")) | file.contains(QRegExp(".jpeg")) | file.contains(QRegExp(".tif"))) {
            QImage img = QImage(fullPath);
            pixmap = QPixmap::fromImage(img, Qt::AutoColor);
        } else if (file.contains(QRegExp(".mp4")) |  file.contains(QRegExp(".avi")) | file.contains(QRegExp(".mov")) | file.contains(QRegExp(".flv"))) {
            //icon for video file
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/play-button.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/play-button.png");
            }
        } else if (file.contains(QRegExp(".m4a")) |  file.contains(QRegExp(".mp3")) | file.contains(QRegExp(".wav")) | file.contains(QRegExp(".flac"))) {
            //icon for music file
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/music-note.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/music-note.png");
            }

        } else if (file.contains(QRegExp(".c$")) |  file.contains(QRegExp(".cpp$")) | file.contains(QRegExp(".ui$")) |  file.contains(QRegExp(".h$")) | file.contains(QRegExp(".html$")) | file.contains(QRegExp(".css$")) | file.contains(QRegExp(".qss$")) | file.contains(QRegExp(".java$")) | file.contains(QRegExp(".steganofs$"))) {
            //icon for coding file
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/coding.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/coding.png");
            }

        } else if (!file.contains(QRegExp("*[.]*"))) {
            //icon for folders
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/folder_c.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/folder_c.png");
            }

        }  else {
            // docs and other files
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/file.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/file.png");
            }

        }


        QListWidgetItem *item = new QListWidgetItem(QIcon(pixmap), QString(file));
        item->setSizeHint(QSize(210, 170));
        qDebug() << fullPath << Qt::endl;
        ui->listWidget->addItem(item);
    }

    path_list.clear();
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    m_currentFile = nullptr;
    ui->listWidget->setCurrentItem(nullptr);
    m_currentDir = m_dirmodel->fileInfo(index).absoluteFilePath();
    QString sPath = m_currentDir;

    //ui->tableView->setRootIndex(m_filemodel->setRootPath(sPath));
    ui->listWidget->setRootIndex(m_filemodel->setRootPath(sPath));
    ui->pathLineEdit->setText(sPath);

    updateListWidget(m_currentDir);
    ui->forwardButton->setDisabled(true);
    ui->backButton->setDisabled(false);


    m_movingHistory->append(m_currentDir);

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

    m_previewPicture->clear();

    if (ui->listWidget->currentItem() != nullptr){
        m_currentFile = current;
        QString fullPath = m_currentDir + "/" + current->text();

        QImage img = QImage(fullPath);

        QPixmap pixmap; // = QPixmap::fromImage(img, Qt::AutoColor);

        if ( fullPath.contains(QRegExp(".jpg")) |  fullPath.contains(QRegExp(".bmp")) | fullPath.contains(QRegExp(".png")) | fullPath.contains(QRegExp(".gif")) | fullPath.contains(QRegExp(".jpeg")) | fullPath.contains(QRegExp(".tif"))) {
            pixmap = QPixmap::fromImage(img, Qt::AutoColor);

        } else if (fullPath.contains(QRegExp(".mp4")) |  fullPath.contains(QRegExp(".avi")) | fullPath.contains(QRegExp(".mov")) | fullPath.contains(QRegExp(".flv"))) {
            //icon for video fullPath
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/play-button.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/play-button.png");
            }

        } else if (fullPath.contains(QRegExp(".m4a")) |  fullPath.contains(QRegExp(".mp3")) | fullPath.contains(QRegExp(".wav")) | fullPath.contains(QRegExp(".flac"))) {
            //icon for music fullPath
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/music-note.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/music-note.png");
            }

        } else if (!fullPath.contains(QRegExp("*[.]*")) ) {
            //icon for folders
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/folder_c.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/folder_c.png");
            }

        } else if (fullPath.contains(QRegExp(".c")) |  fullPath.contains(QRegExp(".cpp")) | fullPath.contains(QRegExp(".ui")) |  fullPath.contains(QRegExp(".h")) | fullPath.contains(QRegExp(".html")) | fullPath.contains(QRegExp(".css")) | fullPath.contains(QRegExp(".qss")) | fullPath.contains(QRegExp(".java")) | fullPath.contains(QRegExp(".steganofs"))) {
            //icon for coding fullPath
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/coding.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/coding.png");
            }

        }  else {
            // docs and other files
            if (m_lightmode_on == 0){
                pixmap = QPixmap(":/assets/img/file.png");
            } else {
                pixmap = QPixmap(":/assets/img/light/file.png");
            }

        }

//        ui->previewLabel->setScaledContents(true);
//        //ui->previewLabel->setMaximumWidth(this->width() / 4);
//        ui->previewLabel->setPixmap(pixmap.scaledToWidth(w));


        //m_previewPicture->setSceneRect(0,0,300,450);

//        PreviewGraphicsView *pgv = new PreviewGraphicsView;
//        int w = ui->graphicsView->width();
//        int h = ui->graphicsView->height();
//        m_previewPicture->addPixmap(pixmap.scaledToWidth(w));
//        ui->horizontalLayout_2->addWidget(pgv);
//        ui->horizontalLayout_2->removeWidget(ui->graphicsView);
//        pgv->setScene(m_previewPicture);



        int w = m_pgv->width();
        m_previewPicture->addPixmap(pixmap.scaledToWidth(w));

        m_pgv->setScene(m_previewPicture);

    }


    }


void MainWindow::on_previewToolButton_clicked()
{


    if (m_preview_on == 0){

        m_pgv->show();

        m_preview_on = 1;

    } else {

        m_pgv->hide();
        m_preview_on = 0;
    }
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{


    m_currentFileString = item->text();

}


void MainWindow::on_darkModePushButton_clicked()
{

    if (m_lightmode_on == 0){
        qApp->setStyleSheet(m_lightstyle);
        m_lightmode_on = 1;
        m_CRDdlg->setLightmodeOn(true);
        m_DefragDlg->setLightmode_on(true);
        m_MFPDlg->setLightmodeon(true);
        m_SFIdlg->setLightmodeon(true);
        m_LFdlg->setLightmodeon(true);

        ui->newFolderPushButton->setIcon(QIcon(":/assets/img/light/folder.png"));
        ui->newFilePushButton->setIcon(QIcon(":/assets/img/light/document.png"));
        ui->deletePushButton->setIcon(QIcon(":/assets/img/light/delete.png"));
        ui->cutPushButton->setIcon(QIcon(":/assets/img/light/scissors.png"));
        ui->copyPushButton->setIcon(QIcon(":/assets/img/light/copy.png"));
        ui->pastePushButton->setIcon(QIcon(":/assets/img/light/paste.png"));
        ui->previewToolButton->setIcon(QIcon(":/assets/img/light/preview.png"));
        ui->darkModePushButton->setIcon(QIcon(":/assets/img/light/night-mode.png"));
        ui->backButton->setStyleSheet(m_bafButtonsStyle_light);

        ui->forwardButton->setStyleSheet(m_bafButtonsStyle_light);

        ui->forwardButton->setIcon(QIcon(":/assets/img/light/arrow-forth.png"));
        ui->backButton->setIcon(QIcon(":/assets/img/light/arrow-back.png"));


    } else {

        qApp->setStyleSheet(m_darkstyle);
        m_lightmode_on = 0;
        m_CRDdlg->setLightmodeOn(false);
        m_DefragDlg->setLightmode_on(false);
        m_MFPDlg->setLightmodeon(false);
        m_SFIdlg->setLightmodeon(false);
        m_LFdlg->setLightmodeon(false);

        ui->newFolderPushButton->setIcon(QIcon(":/assets/img/folder.png"));
        ui->newFilePushButton->setIcon(QIcon(":/assets/img/document.png"));
        ui->deletePushButton->setIcon(QIcon(":/assets/img//delete(1).png"));
        ui->cutPushButton->setIcon(QIcon(":/assets/img/scissors(1).png"));
        ui->copyPushButton->setIcon(QIcon(":/assets/img/copy.png"));
        ui->pastePushButton->setIcon(QIcon(":/assets/img/paste.png"));
        ui->previewToolButton->setIcon(QIcon(":/assets/img/preview (2).png"));
        ui->darkModePushButton->setIcon(QIcon(":/assets/img/light-bulb.png"));
        ui->backButton->setStyleSheet(m_bafButtonsStyle_dark);
        ui->forwardButton->setStyleSheet(m_bafButtonsStyle_dark);

        ui->forwardButton->setIcon(QIcon(":/assets/img/arrow-forth.png"));
        ui->backButton->setIcon(QIcon(":/assets/img/arrow-back.png"));


    }

   updateListWidget(m_currentDir);

}




void MainWindow::on_actionDefragment_triggered()
{
    m_DefragDlg->setAdapter(steganoFsAdapter);
    m_DefragDlg->setFragmentation(steganoFsAdapter->getFragmentationInPercent());
    m_DefragDlg->exec();
}


void MainWindow::on_actionNeuer_Ordner_triggered()
{

}


void MainWindow::on_actionShow_Filesystem_information_triggered()
{
        m_SFIdlg->showFilesystemInfo(*steganoFsAdapter);
        m_SFIdlg->exec();


}

void MainWindow::on_actionMount_triggered()
{

        //steganoFsAdapter->umount();

//        auto path = m_filemodel->rootPath();
//        m_filemodel->setRootPath("");


        if (m_MFPDlg->exec() == QDialog::Accepted) {

        SteganoFsAdapter *sfa = new SteganoFsAdapter(m_MFPDlg->filesystemPath().toStdString());

        if (sfa->loadFilesytemFromSteganoProvider()){
            ui->statusbar->showMessage(QString("Loaded file: " + m_MFPDlg->filesystemPath()), 10000);

            m_thread->start();
            // QVariant qSteganoFSAdapter = QVariant::fromValue(steganoFsAdapter);
             QVariant qSteganoFSAdapter = QVariant::fromValue(sfa);

            if (QMetaObject::invokeMethod(m_worker, "mountFolder", Q_ARG(QVariant, qSteganoFSAdapter), Q_ARG(QString, m_MFPDlg->mountingPath()))){
                ui->actionMount->setDisabled(true);
                ui->actionUnmount->setDisabled(false);
                ui->actionDefragment->setDisabled(false);
                steganoFsAdapter = sfa;

            } else {
                ui->actionMount->setDisabled(false);
                ui->actionUnmount->setDisabled(true);
                steganoFsAdapter = nullptr;
                delete sfa;

                //TODO fehlermeldung dialog
            }

        } else {
            ui->actionMount->setDisabled(false);
            ui->actionUnmount->setDisabled(true);
            steganoFsAdapter = nullptr;
            delete sfa;

            //TODO fehlermeldung dialog

        }


        } else {
        ui->statusbar->showMessage(QString("Mount aborted."));
        }

//        m_filemodel->setRootPath(path);
}




void MainWindow::on_actionUnmount_triggered()
{
    if (steganoFsAdapter->umount()){
        if (steganoFsAdapter->writeFilesystemToSteganoProvider()){
            ui->actionUnmount->setDisabled(true);
            ui->actionMount->setDisabled(false);
            ui->actionDefragment->setDisabled(true);
            delete steganoFsAdapter;
            steganoFsAdapter = nullptr;
            ui->statusbar->showMessage("Successfully unmounted!",18000);

        } else {
            ui->statusbar->showMessage("writeFilesystemTo... = false!", 18000);
        }
    } else {
        ui->actionUnmount->setDisabled(false);
        ui->actionMount->setDisabled(true);
        ui->statusbar->showMessage("umount was not successfull", 18000);
    }


}





void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{

    if (ui->pathLineEdit->text() == "/"){
        ui->pathLineEdit->clear();
        m_currentDir = "";
        m_lastDirectory = "/";
    } else {

        QString path = m_currentDir + "/" + ui->listWidget->currentItem()->text();


        if ( QFileInfo(path).isDir()  /*!path.contains(QRegExp("*[.]*"))*/){
            ui->pathLineEdit->clear();
            m_currentDir = path;

            if (m_currentDir != m_movingHistory->last()){
                m_movingHistory->removeLast();
                m_stepsToGoBack -= 1;
            }

            //m_lastDirectory = tmp;
            ui->forwardButton->setDisabled(true);
            ui->backButton->setDisabled(false);


            //std::future<QString> fut = std::async(m_filemodel->directoryLoaded(path));
            updateListWidget(path);

            m_movingHistory->append(m_currentDir);

            if (ui->listWidget->count() != 0){
                ui->listWidget->setCurrentRow(1);
                m_currentFile = ui->listWidget->currentItem();
            }

            ui->pathLineEdit->setText(m_currentDir);
    }

    }






}

void MainWindow::refreshPreviewOnResize()
{
    //m_pgv->scene()->clear();
    m_pgv->setScene(m_previewPicture);
}



void MainWindow::on_backButton_clicked()
{
//    QString tmp = m_currentDir;

//    m_currentDir = m_lastDirectory;
//    m_nextDirectory = tmp;

    m_currentDir = m_movingHistory->at(m_movingHistory->size() - 2);
    ui->statusbar->showMessage(m_currentDir);
    m_nextDirectory = m_movingHistory->last();

    updateListWidget(m_currentDir);
    ui->pathLineEdit->clear();
    ui->pathLineEdit->setText(m_currentDir);

    ui->forwardButton->setDisabled(false);

    /*
     * CAN ONLY BE EXECUTED ONCE
     * */
}


void MainWindow::on_forwardButton_clicked()
{
    QString tmp = m_currentDir;
    m_currentDir = m_nextDirectory;
    m_lastDirectory = tmp;

    updateListWidget(m_currentDir);
    ui->pathLineEdit->setText(m_currentDir);

    ui->forwardButton->setDisabled(true);

    /*
     * CAN ONLY BE EXECUTED ONCE
     * */
}

void MainWindow::updateHistory()
{

}






