#ifndef FRAGMENTATIONDIAGRAM_H
#define FRAGMENTATIONDIAGRAM_H

#include <QWidget>
#include "fragmenttile.h"
#include "../cpp-wrapper/SteganoFsAdapter.h"

namespace Ui
{
class FragmentationDiagram;
}

class FragmentationDiagram: public QWidget
{
Q_OBJECT

public:
    explicit FragmentationDiagram(QWidget *parent = nullptr, SteganoFsAdapter *steganoFsAdapter = nullptr);
    ~FragmentationDiagram() override;

private:
    Ui::FragmentationDiagram *ui;
    QList<FragmentTile *> *tiles;
};

#endif // FRAGMENTATIONDIAGRAM_H
