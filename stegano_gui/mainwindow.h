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
#include <QGraphicsScene>
#include "previewgraphicsview.h"
#include "showfilesysteminfodialog.h"
#include "loadfilesystemdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void pathChanged();


private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void handleSearchTextChanged(const QString &searchText);
    void refreshView();

    void on_pathLineEdit_editingFinished();

    void on_DisplayComboBox_currentIndexChanged(int index);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_previewToolButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_darkModePushButton_clicked();

    void on_actionDefragment_triggered();

    void on_actionNeuer_Ordner_triggered();

    void on_actionShow_Filesystem_information_triggered();

    void on_actionMount_triggered();

    void on_actionUnmount_triggered();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void refreshPreviewOnResize();

    void on_backButton_clicked();

    void on_forwardButton_clicked();

    void updateHistory();


private:
    Ui::MainWindow *ui;
    CreateRamdiskDialog *m_CRDdlg;
    DefragmentDialog *m_DefragDlg;
    MountFromPathDialog *m_MFPDlg;

    ShowFileSystemInfoDialog *m_SFIdlg;
    LoadFileSystemDialog *m_LFdlg;



    QGraphicsScene *m_previewPicture;
    PreviewGraphicsView *m_pgv;


    SteganoFsAdapter *steganoFsAdapter = nullptr;
    Worker *m_worker;
    QThread *m_thread;


    QString m_darkstyle;
    QString m_lightstyle;
    QString m_bafButtonsStyle_dark;
    QString m_bafButtonsStyle_light;

    QFileSystemModel *m_dirmodel;
    QFileSystemModel *m_filemodel;

    QString m_currentDir;
    QListWidgetItem *m_currentFile;
    QString m_currentFileString;
    QList<QString> *m_movingHistory;
    int m_stepsToGoBack;
    QList<QListWidgetItem> selectedFiles;

    QString m_lastDirectory;
    QString m_nextDirectory;

    QListWidget *listWidget;
    QTreeView *treeView;
    QLineEdit *searchLineEdit;
    QPushButton *refreshButton;
    bool m_preview_on;
    bool m_lightmode_on;
    void updateListWidget(QString sPath);
};
#endif // MAINWINDOW_H
