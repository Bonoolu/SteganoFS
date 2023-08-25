#ifndef FRAGMENTATIONDIAGRAM_H
#define FRAGMENTATIONDIAGRAM_H

#include <QWidget>
#include "fragmenttile.h"

namespace Ui
{
class FragmentationDiagram;
}

class FragmentationDiagram: public QWidget
{
Q_OBJECT

public:
    explicit FragmentationDiagram(QWidget *parent = nullptr);
    ~FragmentationDiagram() override;

private:
    Ui::FragmentationDiagram *ui;
    QList<FragmentTile *> *tiles;
};

#endif // FRAGMENTATIONDIAGRAM_H
