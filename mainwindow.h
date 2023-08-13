#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QString>
#include <QTreeView>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

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

private:
    Ui::MainWindow *ui;

    QString m_darkstyle;
    QString m_lightstyle;

    QFileSystemModel *m_dirmodel;
    QFileSystemModel *m_filemodel;

    QString m_currentDir;
    QListWidgetItem m_currentFile;

    QListWidget *listWidget;
    QTreeView *treeView;
    QLineEdit *searchLineEdit;
    QPushButton *refreshButton;
    bool m_preview_on;
    bool m_lightmode_on;
    void updateListWidget(QString sPath);
};
#endif // MAINWINDOW_H
