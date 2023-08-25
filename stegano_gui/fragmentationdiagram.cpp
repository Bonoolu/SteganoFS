#include "fragmentationdiagram.h"
#include "ui_fragmentationdiagram.h"
#include "fragmenttile.h"

FragmentationDiagram::FragmentationDiagram(QWidget *parent)
    :
    QWidget(parent),
    ui(new Ui::FragmentationDiagram)
{
    ui->setupUi(this);

    tiles = new QList<FragmentTile *>();

    int i = 0;
    for (size_t y = 0; y < 50; y++) {
        for (size_t x = 0; x < 50; x++) {
            int colorvalue = (i % 512) - 256;
            colorvalue = colorvalue < 0 ? -colorvalue : colorvalue;
            QColor color = QColor::fromHsv(colorvalue, 200, 255);
            auto *tile = new FragmentTile(this, color);
            ui->gridLayout->addWidget(tile, (int) y, (int) x);
            tiles->append(tile);
            i++;
        }
    }
}

FragmentationDiagram::~FragmentationDiagram()
{
    delete tiles;
    delete ui;
}
