#ifndef FRAGMENTATIONDIALOG_H
#define FRAGMENTATIONDIALOG_H

#include <QDialog>

namespace Ui
{
class FragmentationDialog;
}

class FragmentationDialog: public QDialog
{
Q_OBJECT

public:
    explicit FragmentationDialog(QWidget *parent = nullptr);
    ~FragmentationDialog() override;

private:
    Ui::FragmentationDialog *ui;

};

#endif // FRAGMENTATIONDIALOG_H
