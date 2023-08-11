#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDebug>
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Stegano File Explorer");

    QString sPath = "D:/Mina/Bilder/SFS_example/";
    m_dirmodel = new QFileSystemModel(this);
    m_dirmodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    m_dirmodel->setRootPath(sPath);

    ui->treeView->setModel(m_dirmodel);

    m_filemodel = new QFileSystemModel(this);

    m_filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    m_filemodel->setRootPath(sPath);

    ui->tableView->setSortingEnabled(true);

    ui->tableView->setModel(m_filemodel);
    ui->treeView->setSortingEnabled(true);
    //QHeaderView *header =
    //ui->treeView->setHeader()

    //ui->listWidget->hide();
    /*ui->listWidget->setSortingEnabled(true);

    // TESTING LISTWIDGET
    for (int i = 0; i < 10; i++){
        ui->listWidget->addItem("File " + QString::number(i));
    }*/

    ui->listWidget->hide();
    ui->listView->hide();


    ui->listView->setModel(m_filemodel);
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setIconSize(QSize(200,150));
    ui->listView->setResizeMode(QListView::Adjust);
    /*
    QString path = ui->pathLineEdit->text();
    for (int i = 0; i < m_filemodel.)

    QListView*/




    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);

    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::refreshView);

    // doesn't work
    //connect(ui->pathLineEdit, &QLineEdit::editingFinished, this, &MainWindow::on_pathLineEdit_editingFinished);
    //qDebug() << m_filemodel.head;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = m_dirmodel->fileInfo(index).absoluteFilePath();
    ui->tableView->setRootIndex(m_filemodel->setRootPath(sPath));
    ui->listView->setRootIndex(m_filemodel->setRootPath(sPath));
    ui->pathLineEdit->setText(sPath);
}

void MainWindow::handleSearchTextChanged(const QString &searchText)
{
    m_filemodel->setNameFilters(QStringList() << "*" + searchText + "*");
    m_filemodel->setNameFilterDisables(false);
}


void MainWindow::refreshView()
{
    ui->tableView->reset();
    ui->listView->reset();
}

void MainWindow::on_DisplayComboBox_currentIndexChanged(int index)
{

    if (index == 1){
        ui->tableView->hide();
//        ui->listWidget->show();
        ui->listView->show();
        ui->sortComboBox->setDisabled(true);
    } else {
//        ui->listWidget->hide();
        ui->listView->hide();
        ui->tableView->show();
        ui->sortComboBox->setDisabled(false);
    }

}

/*

void MainWindow::on_previewToolButton_triggered(QAction *arg1)
{
    ui->horizontalLayout_2->addItem()
}
*/

void MainWindow::on_pathLineEdit_editingFinished()
{
    QString newPath = ui->pathLineEdit->text();
    ui->treeView->setRootIndex(m_dirmodel->setRootPath(newPath));
    ui->tableView->setRootIndex(m_filemodel->setRootPath(newPath));
    ui->listView->setRootIndex(m_filemodel->setRootPath(newPath));
}




