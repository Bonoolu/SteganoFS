#ifndef LOADFILESYSTEMDIALOG_H
#define LOADFILESYSTEMDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"

namespace Ui {
class LoadFileSystemDialog;
}

class LoadFileSystemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadFileSystemDialog(QWidget *parent = nullptr);
    ~LoadFileSystemDialog();


    QString loadingPath() const;
    void setLoadingPath(const QString &newLoadingPath);
    void setLightmodeon(bool b);

    SteganoFsAdapter *adapter() const;
    void setAdapter(SteganoFsAdapter *newAdapter);

private slots:
    void on_buttonBox_accepted();

    void on_fileBrowserButton_clicked();

private:
    Ui::LoadFileSystemDialog *ui;
    QFileDialog *m_fileDlg;
    QString m_loadingPath;
    bool m_lightmodeon;
    SteganoFsAdapter *m_adapter;

};

#endif // LOADFILESYSTEMDIALOG_H
