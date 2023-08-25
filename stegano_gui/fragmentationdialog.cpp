#include "fragmentationdialog.h"
#include "ui_fragmentationdialog.h"
#include "fragmentationdiagram.h"
#include <QLabel>

FragmentationDialog::FragmentationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FragmentationDialog)
{
    ui->setupUi(this);
    FragmentationDiagram *fragDiagram = new FragmentationDiagram(this);
    layout()->replaceWidget(ui->widget, fragDiagram);
    ui->widget->hide();
}

FragmentationDialog::~FragmentationDialog()
{
    delete ui;
}
