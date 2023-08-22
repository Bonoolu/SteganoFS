#ifndef MOUNTFROMPATHDIALOG_H
#define MOUNTFROMPATHDIALOG_H

#include <QDialog>

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

private slots:
    void on_mountPathLineEdit_textChanged(const QString &arg1);


signals:
    void finishedMounting();

private:
    Ui::MountFromPathDialog *ui;
    QString m_mountingPath;
    QString m_status;
    bool m_lightmodeon;
};

#endif // MOUNTFROMPATHDIALOG_H
