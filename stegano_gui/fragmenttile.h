#ifndef FRAGMENTTILE_H
#define FRAGMENTTILE_H

#include <QWidget>

namespace Ui
{
class FragmentTile;
}

class FragmentTile: public QWidget
{
Q_OBJECT

public:
    explicit FragmentTile(QWidget *parent = nullptr, const QColor &color = QColor("white"));
    void setColor(const QColor &color);
    ~FragmentTile() override;

private:
    Ui::FragmentTile *ui;
};

#endif // FRAGMENTTILE_H
