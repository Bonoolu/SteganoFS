#ifndef MOUNTFROMPATHDIALOG_H
#define MOUNTFROMPATHDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"

namespace Ui {
class MountFromPathDialog;
}

class MountFromPathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MountFromPathDialog(QWidget *parent = nullptr);
    ~MountFromPathDialog();

    void setMountingPath(const QString &newMountingPath);

    QString mountingPath() const;

    bool lightmodeon() const;
    void setLightmodeon(bool newLightmodeon);

    QString filesystemPath() const;
    void setFilesystemPath(const QString &newFilesystemPath);

    SteganoFsAdapter *adapter() const;
    void setAdapter(SteganoFsAdapter *newAdapter);

private slots:
    void on_mountPathLineEdit_textChanged(const QString &arg1);


    void on_filesystemPathLineEdit_textChanged(const QString &arg1);

    void on_browseDirButton_clicked();

    void on_browseFsButton_clicked();

signals:
    void finishedMounting();

private:
    Ui::MountFromPathDialog *ui;
    QString m_mountingPath;
    QString m_filesystemPath;
    QString m_status;
    bool m_lightmodeon;

    QFileDialog *m_mountDlg = nullptr;
    QFileDialog *m_fsDlg = nullptr;
    SteganoFsAdapter *m_adapter = nullptr;
};

#endif // MOUNTFROMPATHDIALOG_H
