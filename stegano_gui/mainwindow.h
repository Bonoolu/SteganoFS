#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QString>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "../cpp-wrapper/SteganoFsAdapter.h"
#include <QDebug>
#include "createramdiskdialog.h"
#include "defragmentdialog.h"
#include "worker.h"
#include <QThread>
#include "mountfrompathdialog.h"
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void handleSearchTextChanged(const QString &searchText);
    void refreshView();
//    void handlePathTextEditFinished(const QString &newPath);

//    void on_DisplayComboBox_activated(int index);


    void on_pathLineEdit_editingFinished();

    void on_DisplayComboBox_currentIndexChanged(int index);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_previewToolButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_darkModePushButton_clicked();

    void on_actionCreate_new_triggered();

    //void createNewRamdisk();
    //void on_actionLoad_triggered();

    void on_actionDefragment_triggered();

    void on_actionNeuer_Ordner_triggered();

    void on_actionShow_Filesystem_information_triggered();

    //void on_actionMount_triggered();

    void on_actionUnmount_triggered();



    void on_actionCurrent_directory_triggered();

    void on_actionFrom_Path_triggered();

    void mountFinished();

    void on_actionChoose_from_explorer_triggered();

    void on_actionLoad_selected_file_triggered();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    CreateRamdiskDialog *m_CRDdlg;
    DefragmentDialog *m_DefragDlg;
    MountFromPathDialog *m_MFPDlg;
    QFileDialog *m_fileDlg;


    SteganoFsAdapter *steganoFsAdapter = new SteganoFsAdapter("filesystem.steganofs");
    Worker *m_worker;
    QThread *m_thread;


    QString m_darkstyle;
    QString m_lightstyle;

    QFileSystemModel *m_dirmodel;
    QFileSystemModel *m_filemodel;

    QString m_currentDir;
    QListWidgetItem *m_currentFile;
    QString m_currentFileString;

    QListWidget *listWidget;
    QTreeView *treeView;
    QLineEdit *searchLineEdit;
    QPushButton *refreshButton;
    bool m_preview_on;
    bool m_lightmode_on;
    void updateListWidget(QString sPath);
};
#endif // MAINWINDOW_H
