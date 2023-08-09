#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMainWindow>
#include <QFileSystemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Stegano File Explorer");

    QString sPath = "D:/";
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


    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearchTextChanged);

    connect(ui->refreshButton, &QPushButton::clicked, this, &MainWindow::refreshView);

    // doesn't work
    // connect(ui->pathLineEdit, &QLineEdit::editingFinished, this, &MainWindow::handlePathTextEditFinished)

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
    ui->pathLineEdit->setText(sPath);
}

void MainWindow::handleSearchTextChanged(const QString &searchText)
{
    m_filemodel->setNameFilters(QStringList() << "*" + searchText + "*");
    m_filemodel->setNameFilterDisables(false);
}

void MainWindow::handlePathTextEditFinished(const QString &newPath)
{
    ui->tableView->setRootIndex(m_filemodel->setRootPath(newPath));
}

void MainWindow::refreshView()
{
    treeView->reset();
}

