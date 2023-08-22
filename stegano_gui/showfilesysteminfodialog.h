#ifndef SHOWFILESYSTEMINFODIALOG_H
#define SHOWFILESYSTEMINFODIALOG_H

#include <QDialog>

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

private slots:
    void on_closeButton_clicked();

private:
    Ui::ShowFileSystemInfoDialog *ui;
    bool m_lightmodeon;
};

#endif // SHOWFILESYSTEMINFODIALOG_H
