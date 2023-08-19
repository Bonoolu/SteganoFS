#ifndef DEFRAGMENTDIALOG_H
#define DEFRAGMENTDIALOG_H

#include <QDialog>
#include "../cpp-wrapper/SteganoFsAdapter.h"

namespace Ui {
class DefragmentDialog;
}

class DefragmentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DefragmentDialog(QWidget *parent = nullptr);
    ~DefragmentDialog();

    void setLightmode_on(bool newLightmode_on);

    bool lightmode_on() const;

    void setFragmentation(float f);

    void setAdapter(SteganoFsAdapter *newAdapter);

private slots:
    void on_pushButton_clicked();

private:
    Ui::DefragmentDialog *ui;
    bool m_lightmode_on;
    SteganoFsAdapter *m_adapter;
};

#endif // DEFRAGMENTDIALOG_H
