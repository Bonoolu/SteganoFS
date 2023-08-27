#ifndef FRAGMENTATIONDIALOG_H
#define FRAGMENTATIONDIALOG_H

#include <QDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"

namespace Ui
{
class FragmentationDialog;
}

class FragmentationDialog: public QDialog
{
Q_OBJECT

public:
    explicit FragmentationDialog(QWidget *parent = nullptr, SteganoFsAdapter *steganoFsAdapter = nullptr);
    ~FragmentationDialog() override;

private:
    Ui::FragmentationDialog *ui;

};

#endif // FRAGMENTATIONDIALOG_H
