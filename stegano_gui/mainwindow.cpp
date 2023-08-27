#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "fragmentationdialog.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDebug>
#include <QIcon>
#include <QPixmap>
#include <QDialog>
#include <QThread>
#include <QMetaObject>
#include <QGraphicsScene>
#include <QRegularExpression>
#include <QFileInfo>
#include <QErrorMessage>
Q_DECLARE_METATYPE(SteganoFsAdapter*)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Stegano File Explorer");

    m_DefragDlg = new DefragmentDialog;
    m_DefragDlg->setLightmodeOn(false);

    m_MFPDlg = new MountFromPathDialog;
    m_MFPDlg->setLightmodeOn(false);

    m_SFIdlg = new ShowFileSystemInfoDialog;
    m_SFIdlg->setLightmodeOn(false);

    m_FFSDlg = new FormatFileSystemDialog;
    m_FFSDlg->setLightmodeOn(false);

    m_movingHistory = new QList<QString>;
    m_stepsToGoBack = 0;


    m_currentFile = nullptr;
    m_worker = new Worker();
    m_thread = new QThread();

    m_worker->moveToThread(m_thread);

    m_preview_on = false;

    m_lightmodeOn = false;

    m_pgv = new PreviewGraphicsView;
    m_previewPicture = new QGraphicsScene;

    ui->statusbar->show();

    // set dark/light style

    QFile file(":/assets/stylesheet/Darkeum.qss");
    file.open(QFile::ReadOnly);

    m_darkstyle = QLatin1String(file.readAll());

    QFile file2(":/assets/stylesheet/Darkeum_light.qss");
    file2.open(QFile::ReadOnly);

    m_lightstyle = QLatin1String(file2.readAll());


    // styling back & forth buttons
    m_bafButtonsStyle_dark =
        "QPushButton {background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #607cff, stop: 1 #445cc9); height: 20px; width: 20px; border-radius: 15px;} QPushButton::disabled { background-color: #3f476b;} QPushButton::hover {background-color: #7990fc;} QPushButton::pressed {background-color: #899dfa;} )";
    m_bafButtonsStyle_light =
        "QPushButton {background-color: qlineargradient(x1: 0, y1: 1, x2: 1, y2: 0,stop: 0 #1073b4, stop: 1 #015891); height: 20px; width: 20px; border-radius: 15px;} QPushButton::disabled { background-color: #2e5e7d;} QPushButton::hover {background-color: #1e86c9;} QPushButton::pressed {background-color: #54a8de;} )";
    ui->backButton->setStyleSheet(m_bafButtonsStyle_dark);
    ui->forwardButton->setStyleSheet(m_bafButtonsStyle_dark);

    ui->backButton->setDisabled(true);
    ui->forwardButton->setDisabled(true);

    // setting initial conditions
    ui->actionUnmount->setDisabled(true);
    ui->actionDefragment->setDisabled(true);



    // building the left side - a tree view with folders
    QString sPath = "/";
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath(QDir::rootPath());
    m_currentDir = "";

    ui->treeView->setModel(m_dirmodel);
    ui->treeView->setSortingEnabled(true);
    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);


    // the right side is displaying the selected folder's content
    m_filemodel = new QFileSystemModel(this);

    m_filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
    m_filemodel->setRootPath(sPath);
    m_filemodel->sort(QDir::DirsFirst | Qt::SortOrder::AscendingOrder);

    ui->tableView->hide();
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setModel(m_filemodel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->searchLineEdit->setPlaceholderText("Search...");
    ui->DisplayComboBox->setDisabled(false);

    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200, 150));
    ui->listWidget->setResizeMode(QListWidget::Adjust);


    ui->listWidget->setSortingEnabled(true);

    // add custom Widget PreviewGraphicsView
    ui->horizontalLayout_2->addWidget(m_pgv);

    m_pgv->setAlignment(Qt::AlignCenter);
    m_pgv->hide();




    // connecting slots and signals
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);
    connect(m_pgv, &PreviewGraphicsView::refreshScene, this, &MainWindow::refreshPreviewOnResize);
    connect(this, &MainWindow::backButtonHit, this, &MainWindow::updateHistoryBack);
    connect(this, &MainWindow::forthButtonHit, this, &MainWindow::updateHistoryForth);

    m_movingHistory->append(m_currentDir);
    ui->actionShow_Filesystem_information->setDisabled(true);
    QDir dir = QDir(QDir::currentPath());
    qDebug() << "Current Path: " << dir.absolutePath() << Qt::endl;
    dir.cdUp();
    dir.cdUp();
    QString str = dir.absolutePath();
    qDebug() << "Navigating to: " << str << Qt::endl;
    updateViews(str);
}

MainWindow::~MainWindow()
{
    m_thread->requestInterruption();
    m_thread->quit();
    m_thread->wait();

    delete m_MFPDlg;
    delete m_DefragDlg;
    delete m_SFIdlg;
    delete m_FFSDlg;

    delete m_filemodel;
    delete m_dirmodel;

    delete m_movingHistory;
    delete m_thread;
    delete m_worker;
    delete m_pgv;
    delete m_previewPicture;
    delete ui;
}

void MainWindow::updateTreeView(const QString &sPath)
{
    QModelIndex index = m_dirmodel->index(QDir::rootPath());
    ui->treeView->setExpanded(index, true);
    for (const QString &component : sPath.split("/")) {
        int row = -1;
        for (int i = 0; i < m_dirmodel->rowCount(index); ++i) {
            QModelIndex childIndex = index.child(i, 0);
            if (childIndex.data().toString() == component) {
                row = i;
                break;
            }
        }

        if (row != -1) {
            index = index.child(row, 0);
            ui->treeView->setExpanded(index, true);
        }
    }
    QItemSelectionModel *selectionModel = ui->treeView->selectionModel();
    selectionModel->clearSelection(); // Clear previous selections
    selectionModel->select(index, QItemSelectionModel::Select);

    if (sPath == m_currentDir)
        disconnect(m_dirmodel, &QFileSystemModel::directoryLoaded, this, &MainWindow::updateTreeView);
}

void MainWindow::updateListWidget(const QString &sPath)
{
    QModelIndex newIndex = m_filemodel->index(sPath);

    if (m_filemodel->isDir(newIndex)) {
        ui->listWidget->setRootIndex(newIndex);

    }

    if (m_stepsToGoBack == 0) {
        ui->backButton->setDisabled(true);
    }
    else if (m_stepsToGoBack == m_movingHistory->size()) {
        ui->forwardButton->setDisabled(true);
    }

    ui->listWidget->clear();

    ui->listWidget->setViewMode(QListWidget::IconMode);
    ui->listWidget->setIconSize(QSize(200, 150));
    ui->listWidget->setResizeMode(QListWidget::Adjust);
    ui->listWidget->setSpacing(20);

    QList<QString> pathList;
    QModelIndex parentIndexFile = m_filemodel->index(m_currentDir);
    m_filemodel->fetchMore(parentIndexFile);
    QModelIndex parentIndexDir = m_dirmodel->index(m_currentDir);
    m_dirmodel->fetchMore(parentIndexDir);
    int numRows = m_filemodel->rowCount(parentIndexFile);


    for (int row = 0; row < numRows; ++row) {
        QModelIndex childIndex = m_filemodel->index(row, 0, parentIndexFile);
        QString path = m_filemodel->data(childIndex).toString();
        pathList.append(path);
    }


    // differentiates between most common formats and applies icon according to file type

    for (const QString &file : pathList) {
        QString fullPath = sPath + "/" + file;
        QPixmap pixmap;


        if (fullPath.contains(QRegExp("[.]jpg")) | fullPath.contains(QRegExp("[.]bmp")) | fullPath.contains(QRegExp("[.]png"))
            | fullPath.contains(QRegExp("[.]gif")) | fullPath.contains(QRegExp("[.]jpeg")) | fullPath.contains(QRegExp("[.]tif"))) {
            QImage img = QImage(fullPath);
            pixmap = QPixmap::fromImage(img, Qt::AutoColor);
        }
        else if (fullPath.contains(QRegExp("[.]mp4")) | fullPath.contains(QRegExp("[.]avi")) | fullPath.contains(QRegExp("[.]mov"))
                 | fullPath.contains(QRegExp("[.]flv"))) {
            //icon for video file
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/play-button.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/play-button.png");
            }
        }
        else if (fullPath.contains(QRegExp("[.]m4a")) | fullPath.contains(QRegExp("[.]mp3")) | fullPath.contains(QRegExp("[.]wav"))
                 | fullPath.contains(QRegExp("[.]flac"))) {
            //icon for music file
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/music-note.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/music-note.png");
            }

        }
        else if (fullPath.contains(QRegExp("[.]c$")) | fullPath.contains(QRegExp("[.]cpp$")) | fullPath.contains(QRegExp("[.]ui$"))
                 | fullPath.contains(QRegExp("[.]h$")) | fullPath.contains(QRegExp("[.]html$")) | fullPath.contains(QRegExp("[.]css$"))
                 | fullPath.contains(QRegExp("[.]qss$")) | fullPath.contains(QRegExp("[.]java$"))
                 | fullPath.contains(QRegExp("[.]steganofs$"))) {
            //icon for coding file
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/coding.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/coding.png");
            }

        }
        else if ( (!fullPath.contains(QRegExp("*[.]*")) && QFileInfo(fullPath).isDir()) | fullPath.contains(QRegExp("[.]zip$"))
                       | fullPath.contains(QRegExp("[.]tar")) || fullPath.contains(QRegExp("[.]gz$")) ) {
            //icon for folders
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/folder_c.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/folder_c.png");
            }

        } else {
            // docs and other files
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/file.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/file.png");
            }

        }

        // add pixmap icon
        auto *item = new QListWidgetItem(QIcon(pixmap), QString(file));
        item->setSizeHint(QSize(210, 170));
        qDebug() << fullPath << Qt::endl;
        ui->listWidget->addItem(item);
    }

    pathList.clear();
    if (sPath == m_currentDir)
        disconnect(m_filemodel, &QFileSystemModel::directoryLoaded, this, &MainWindow::updateListWidget);
}

void MainWindow::updateViews(const QString &sPath)
{
    QModelIndex newIndex = m_filemodel->index(sPath);
    QModelIndex newIndex2 = m_dirmodel->index(sPath);

    if (m_filemodel->isDir(newIndex)) {
        connect(m_filemodel, &QFileSystemModel::directoryLoaded, this, &MainWindow::updateListWidget);
        connect(m_dirmodel, &QFileSystemModel::directoryLoaded, this, &MainWindow::updateTreeView);
        m_currentDir = sPath;
        m_dirmodel->fetchMore(newIndex2);
        m_filemodel->fetchMore(newIndex);
        m_filemodel->setRootPath(sPath);
    }

}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{

    QString newdir = m_dirmodel->fileInfo(index).absoluteFilePath();

    if (m_currentDir != newdir) {
        m_currentFile = nullptr;
        m_stepsToGoBack++;
        ui->listWidget->setCurrentItem(nullptr);
        m_currentDir = newdir;

        ui->pathLineEdit->setText(m_currentDir);

        updateViews(m_currentDir);
        ui->forwardButton->setDisabled(true);
        ui->backButton->setDisabled(false);

        if (m_currentDir != m_movingHistory->last()) {
            m_movingHistory->append(m_currentDir);
        }
    }

}

void MainWindow::on_listWidget_itemDoubleClicked([[maybe_unused]] QListWidgetItem *item)
{

    QString newdir = m_currentDir + "/" + ui->listWidget->currentItem()->text();

    if (ui->pathLineEdit->text() == "/") {

        m_movingHistory->append(newdir);
        ui->pathLineEdit->clear();
        m_currentDir = "";
        m_stepsToGoBack++;
        m_lastDirectory = "/";
    }
    else {


        if (QFileInfo(newdir).isDir()) {

            if (m_currentDir != newdir) {

                if (!m_movingHistory->empty()) {
                    while (m_currentDir != m_movingHistory->last()) {
                        m_movingHistory->removeLast();
                        m_stepsToGoBack--;
                        ui->forwardButton->setDisabled(true);

                    }

                }
                ui->pathLineEdit->clear();
                m_currentDir = newdir;
                m_movingHistory->append(m_currentDir);
                m_stepsToGoBack++;

                ui->backButton->setDisabled(false);
            }

            updateViews(m_currentDir);

            ui->pathLineEdit->setText(m_currentDir);
            m_movingHistory->append(m_currentDir);
        }

    }

}


void MainWindow::handleSearchTextChanged(const QString &searchText)
{
    // functionality to search through displayed files

    m_filemodel->setNameFilters(QStringList() << "*" + searchText + "*");
    m_filemodel->setNameFilterDisables(false);
    updateViews(m_currentDir);
}


void MainWindow::on_DisplayComboBox_currentIndexChanged(int index)
{

    if (index == 1) {
        ui->tableView->hide();
        ui->listWidget->show();
    }
    else {
        ui->listWidget->hide();
        ui->tableView->show();
    }

}

void MainWindow::on_pathLineEdit_editingFinished()
{
    // sets new current directory according to path text input
    QString newPath = ui->pathLineEdit->text();
    ui->treeView->setRootIndex(m_dirmodel->setRootPath(newPath));
    ui->tableView->setRootIndex(m_filemodel->setRootPath(newPath));
    updateViews(newPath);

}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, [[maybe_unused]] QListWidgetItem *previous)
{

    // sets the preview picture according to type of current selected file

    m_previewPicture->clear();

    if (ui->listWidget->currentItem() != nullptr) {
        m_currentFile = current;
        QString fullPath = m_currentDir + "/" + current->text();

        QImage img = QImage(fullPath);

        QPixmap pixmap;

        if (fullPath.contains(QRegExp("[.]jpg")) | fullPath.contains(QRegExp("[.]bmp")) | fullPath.contains(QRegExp("[.]png"))
            | fullPath.contains(QRegExp("[.]gif")) | fullPath.contains(QRegExp("[.]jpeg")) | fullPath.contains(QRegExp("[.]tif"))) {
            pixmap = QPixmap::fromImage(img, Qt::AutoColor);

        }
        else if (fullPath.contains(QRegExp("[.]mp4")) | fullPath.contains(QRegExp("[.]avi")) | fullPath.contains(QRegExp("[.]mov"))
                   | fullPath.contains(QRegExp("[.]flv")))  {
            //icon for video fullPath
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/play-button.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/play-button.png");
            }

        }
        else if (fullPath.contains(QRegExp("[.]m4a")) | fullPath.contains(QRegExp("[.]mp3")) | fullPath.contains(QRegExp("[.]wav"))
                   | fullPath.contains(QRegExp("[.]flac"))) {
            //icon for music fullPath
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/music-note.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/music-note.png");
            }

        }
        else if ( (!fullPath.contains(QRegExp("*[.]*")) && QFileInfo(fullPath).isDir()) | fullPath.contains(QRegExp("[.]zip$"))
                       | fullPath.contains(QRegExp("[.]tar")) || fullPath.contains(QRegExp("[.]gz$")) ) {
            //icon for folders
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/folder_c.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/folder_c.png");
            }

        }
        else if (fullPath.contains(QRegExp("[.]c$")) | fullPath.contains(QRegExp("[.]cpp$")) | fullPath.contains(QRegExp("[.]ui$"))
                   | fullPath.contains(QRegExp("[.]h$")) | fullPath.contains(QRegExp("[.]html$")) | fullPath.contains(QRegExp("[.]css$"))
                   | fullPath.contains(QRegExp("[.]qss$")) | fullPath.contains(QRegExp("[.]java$"))
                   | fullPath.contains(QRegExp("[.]steganofs$"))) {
            //icon for coding fullPath
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/coding.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/coding.png");
            }

        }
        else {
            // docs and other files
            if (m_lightmodeOn == 0) {
                pixmap = QPixmap(":/assets/img/file.png");
            }
            else {
                pixmap = QPixmap(":/assets/img/light/file.png");
            }

        }

        int w = m_pgv->width();
        m_previewPicture->addPixmap(pixmap.scaledToWidth(w));
        m_pgv->setScene(m_previewPicture);

    }

}

void MainWindow::on_previewToolButton_clicked()
{
    // show or hide the preview
    if (m_preview_on == 0) {

        m_pgv->show();

        m_preview_on = true;

    }
    else {

        m_pgv->hide();
        m_preview_on = true;
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    m_currentFileString = item->text();
}

void MainWindow::on_darkModePushButton_clicked()
{
    // sets from light to dark mode and vice versa

    if (m_lightmodeOn == 0) {
        qApp->setStyleSheet(m_lightstyle);
        m_lightmodeOn = true;
        m_DefragDlg->setLightmodeOn(true);
        m_MFPDlg->setLightmodeOn(true);
        m_SFIdlg->setLightmodeOn(true);
        m_FFSDlg->setLightmodeOn(true);


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

    }
    else {

        qApp->setStyleSheet(m_darkstyle);
        m_lightmodeOn = false;
        m_DefragDlg->setLightmodeOn(false);
        m_MFPDlg->setLightmodeOn(false);
        m_SFIdlg->setLightmodeOn(false);
        m_FFSDlg->setLightmodeOn(false);


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

    updateViews(m_currentDir);
    updateListWidget(m_currentDir);

}

void MainWindow::on_actionMount_triggered()
{
    auto *err = new QErrorMessage;

    // opens a dialog to mount a folder and load a filesystem

    if (m_MFPDlg->exec() == QDialog::Accepted) {

        // dialog receives a SteganoFsAdapter pointer from which a QVariant will be initialized
        auto *sfa = new SteganoFsAdapter(m_MFPDlg->filesystemPath().toStdString());
        sfa->umount(m_MFPDlg->mountingPath().toStdString());

        if (sfa->loadFilesytemFromSteganoProvider()) {
            ui->statusbar->showMessage(QString("Loaded file: " + m_MFPDlg->filesystemPath()), 10000);

            m_thread->start();
            // QVariant is needed to invoke Worker method
            QVariant qSteganoFsAdapter = QVariant::fromValue(sfa);


            // mount has to be called in thread, otherwise GUI will freeze

            if (QMetaObject::invokeMethod(m_worker,
                                          "mountFolder",
                                          Q_ARG(QVariant, qSteganoFsAdapter),
                                          Q_ARG(QString, m_MFPDlg->mountingPath()))) {
                ui->actionMount->setDisabled(true);
                ui->actionShow_Filesystem_information->setDisabled(false);
                ui->actionUnmount->setDisabled(false);
                ui->actionDefragment->setDisabled(false);
                steganoFsAdapter = sfa;
                ui->statusbar->showMessage(QString("Mount of" + m_MFPDlg->mountingPath() + " successfull"), 18000);
                updateViews(m_MFPDlg->mountingPath());
            }
            else {
                ui->actionMount->setDisabled(false);
                ui->actionUnmount->setDisabled(true);
                ui->actionShow_Filesystem_information->setDisabled(true);
                steganoFsAdapter = nullptr;
                delete sfa;

                err->showMessage("Unable to mount path!");
            }

        }
        else {
            ui->actionMount->setDisabled(false);
            ui->actionUnmount->setDisabled(true);
            ui->actionShow_Filesystem_information->setDisabled(true);
            steganoFsAdapter = nullptr;
            delete sfa;
            err->showMessage("Unable to load file system!");

        }

    }
    else {
        ui->statusbar->showMessage(QString("Mount aborted."));
    }

    delete err;

}

void MainWindow::on_actionUnmount_triggered()
{
    // functionality to unmount a mounted folder
    if (steganoFsAdapter->umount()) {
        if (steganoFsAdapter->writeFilesystemToSteganoProvider()) {
            ui->actionUnmount->setDisabled(true);
            ui->actionMount->setDisabled(false);
            ui->actionDefragment->setDisabled(true);
            ui->actionShow_Filesystem_information->setDisabled(true);
            delete steganoFsAdapter;
            steganoFsAdapter = nullptr;
            ui->statusbar->showMessage("Successfully unmounted!", 18000);
        }
        else {
            ui->statusbar->showMessage("Writing to filesystem failed!", 18000);
        }
    }
    else {
        ui->actionUnmount->setDisabled(false);
        ui->actionMount->setDisabled(true);
        ui->statusbar->showMessage("Umount was not successfull", 18000);
    }

}

void MainWindow::on_actionShow_Filesystem_information_triggered()
{
    // opens dialog to display File system Information in a seperate dialog
    m_SFIdlg->showFilesystemInfo(*steganoFsAdapter);
    m_SFIdlg->exec();

}

void MainWindow::on_actionDefragment_triggered()
{
    // opens dialog for defragmentation
    m_DefragDlg->setAdapter(steganoFsAdapter);
    m_DefragDlg->setFragmentation(steganoFsAdapter->getFragmentationInPercent());
    m_DefragDlg->exec();
}

void MainWindow::on_actionFormat_Filesystem_triggered()
{

    // opens dialog for formatting a loaded file system

    auto *err = new QErrorMessage;

    if (m_FFSDlg->exec() == QDialog::Accepted) {

        auto *sfa = new SteganoFsAdapter(m_FFSDlg->filesystemPath().toStdString());
        size_t filesystem_size = sfa->formatNewFilesystem();
        if (filesystem_size) {
            ui->statusbar
                ->showMessage(QString("Formatted new filesystem with size: ") + QString::number(filesystem_size),
                              10000);
        }
        else {
            ui->statusbar->showMessage(QString("Failed to format new filesystem!"), 10000);
        }

    }
    else {
        ui->statusbar->showMessage(QString("Filesystem formatting aborted by user"), 10000);
    }
    delete err;
}

void MainWindow::on_actionShow_Fragmentation_triggered()
{
    auto *dialog = new FragmentationDialog(this);
    dialog->exec();
}



void MainWindow::refreshPreviewOnResize()
{
    //m_pgv->scene()->clear();
    m_pgv->setScene(m_previewPicture);
}

void MainWindow::on_backButton_clicked()
{

    if (m_stepsToGoBack != 0) {

        m_currentDir = m_movingHistory->at(m_stepsToGoBack-1);
        m_stepsToGoBack--;


        ui->statusbar->showMessage(m_currentDir);

        updateViews(m_currentDir);
        ui->pathLineEdit->clear();
        ui->pathLineEdit->setText(m_currentDir);

        ui->forwardButton->setDisabled(false);

        emit backButtonHit();
    }

}

void MainWindow::on_forwardButton_clicked()
{

    if (m_stepsToGoBack != m_movingHistory->size()) {
        m_stepsToGoBack++;
        m_currentDir = m_movingHistory->at(m_stepsToGoBack);

        updateViews(m_currentDir);
        ui->pathLineEdit->setText(m_currentDir);

    }
}

void MainWindow::updateHistoryBack()
{
    if (m_movingHistory->isEmpty()){
        ui->backButton->setDisabled(true);
        ui->forwardButton->setDisabled(true);

    }

    if (m_stepsToGoBack == 0) {
        ui->backButton->setDisabled(true);
    }

}

void MainWindow::updateHistoryForth()
{
    if (!m_movingHistory->isEmpty()){
        if (m_movingHistory->last() == m_currentDir) {
            ui->backButton->setDisabled(false);
            ui->forwardButton->setDisabled(true);
        }

    }

    if (m_stepsToGoBack >= m_movingHistory->size()-1){
        ui->forwardButton->setDisabled(true);
    }
}

