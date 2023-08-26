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
#include "defragmentdialog.h"
#include "worker.h"
#include <QThread>
#include "mountfrompathdialog.h"
#include <QFileDialog>
#include <QGraphicsScene>
#include "previewgraphicsview.h"
#include "showfilesysteminfodialog.h"
#include "formatfilesystemdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class is the main GUI window for the application.
 *
 * This class handles various UI interactions, signals, and slots.
 */
class MainWindow: public QMainWindow
{
Q_OBJECT

public:
    /**
     * @brief Constructor for the MainWindow class.
     * @param parent The parent widget.
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the MainWindow class.
     */
    ~MainWindow() override;

signals:
    /**
     * @brief Signal emitted when the path is changed.
     */
    void pathChanged();
    void backButtonHit();
    void forthButtonHit();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void handleSearchTextChanged(const QString &searchText);
    void refreshView();
    void on_pathLineEdit_editingFinished();
    void on_DisplayComboBox_currentIndexChanged(int index);
    void on_listWidget_currentItemChanged(QListWidgetItem *current, [[maybe_unused]] QListWidgetItem *previous);
    void on_previewToolButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_darkModePushButton_clicked();
    void on_actionDefragment_triggered();
    void on_actionShow_Filesystem_information_triggered();
    void on_actionMount_triggered();
    void on_actionUnmount_triggered();
    void on_actionShow_Fragmentation_triggered();
    void on_listWidget_itemDoubleClicked([[maybe_unused]] QListWidgetItem *item);
    void refreshPreviewOnResize();
    void on_backButton_clicked();
    void on_forwardButton_clicked();
    void updateHistoryBack();
    void updateHistoryForth();
    void on_sortComboBox_currentIndexChanged(int index);

    void on_actionFormat_Filesystem_triggered();

private:
    Ui::MainWindow *ui;
    DefragmentDialog *m_DefragDlg;
    MountFromPathDialog *m_MFPDlg;
    ShowFileSystemInfoDialog *m_SFIdlg;
    FormatFileSystemDialog *m_FFSDlg;
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
    QListWidget *listWidget{};
    QTreeView *treeView{};
    QLineEdit *searchLineEdit{};
    QPushButton *refreshButton{}; // TODO: Are these 4 pointers actually used?
    bool m_preview_on;
    bool m_lightmodeOn;

    /**
     * @brief Updates the QListWidget with items from the given path.
     * @param sPath The path to update the QListWidget with.
     */
    void updateViews(const QString &sPath);
    void updateListWidget(const QString &sPath);

    void updateTreeView(const QString &sPath);
};

#endif // MAINWINDOW_H
