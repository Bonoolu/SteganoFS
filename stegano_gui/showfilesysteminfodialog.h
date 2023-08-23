#ifndef SHOWFILESYSTEMINFODIALOG_H
#define SHOWFILESYSTEMINFODIALOG_H

#include <QDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"
#include <sys/statfs.h>

namespace Ui {
class ShowFileSystemInfoDialog;
}

class ShowFileSystemInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowFileSystemInfoDialog(QWidget *parent = nullptr);
    ~ShowFileSystemInfoDialog();

    void setLightmodeon(bool newLightsmodeon);
    void showFilesystemInfo(SteganoFsAdapter &sfa);

private slots:
    void on_closeButton_clicked();

private:
    Ui::ShowFileSystemInfoDialog *ui;
    bool m_lightmodeon;

};

#endif // SHOWFILESYSTEMINFODIALOG_H
