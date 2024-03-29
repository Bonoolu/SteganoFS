#include "fragmenttile.h"
#include "ui_fragmenttile.h"

FragmentTile::FragmentTile(QWidget *parent, const QColor& color)
    :
    QWidget(parent),
    ui(new Ui::FragmentTile)
{
    ui->setupUi(this);
    this->setStyleSheet("background: " + color.toRgb().name() + "; border 1px solid black;");
}

void FragmentTile::setColor(const QColor& color)
{
    this->setStyleSheet("background: " + color.toRgb().name() + "; border 1px solid black;");
}

FragmentTile::~FragmentTile()
{
    delete ui;
}
