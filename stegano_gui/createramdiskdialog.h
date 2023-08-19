#ifndef CREATERAMDISKDIALOG_H
#define CREATERAMDISKDIALOG_H

#include <QDialog>

namespace Ui {
class CreateRamdiskDialog;
}

class CreateRamdiskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRamdiskDialog(QWidget *parent = nullptr);
    ~CreateRamdiskDialog();

    int getValue();
    void setLightmodeOn(bool b);
    bool lightmodeOn();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_ramdiskSizeSpinBox_valueChanged(int arg1);

signals:
    void accepted();

private:
    Ui::CreateRamdiskDialog *ui;
    int m_value;
    int m_lightmodeon;
};

#endif // CREATERAMDISKDIALOG_H
