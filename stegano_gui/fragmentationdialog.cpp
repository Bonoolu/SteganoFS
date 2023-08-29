#include "fragmentationdialog.h"
#include "ui_fragmentationdialog.h"
#include "fragmentationdiagram.h"
#include <QLabel>

FragmentationDialog::FragmentationDialog(QWidget *parent, SteganoFsAdapter *steganoFsAdapter)
    :
    QDialog(parent),
    ui(new Ui::FragmentationDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Fragmentation Diagramm");
    auto *fragDiagram = new FragmentationDiagram(this, steganoFsAdapter);
    layout()->replaceWidget(ui->widget, fragDiagram);
    ui->widget->hide();
}

FragmentationDialog::~FragmentationDialog()
{
    delete ui;
}
