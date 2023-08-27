#include "previewgraphicsview.h"

PreviewGraphicsView::PreviewGraphicsView(QWidget *parent)
    :
    QGraphicsView(parent){

}

void PreviewGraphicsView::resizeEvent(QResizeEvent *event)
{
    //  overwrites resizeEvent for PreviewGraphicsView
    int w = this->parentWidget()->width();

    this->setMaximumWidth(w / 4);

    update();
    emit refreshScene();
    QGraphicsView::resizeEvent(event);
}
