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
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateRamdiskDialog *ui;
    int value;
};

#endif // CREATERAMDISKDIALOG_H
