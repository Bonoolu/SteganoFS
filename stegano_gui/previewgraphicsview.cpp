#include "previewgraphicsview.h"

PreviewGraphicsView::PreviewGraphicsView(QWidget *parent)
{

}

void PreviewGraphicsView::resizeEvent(QResizeEvent *event)
{

//    if (width() > image.width() || height() > image.height()) {
//        int newWidth = qMax(width() + 128, image.width());
//        int newHeight = qMax(height() + 128, image.height());
//        this.
//        resizeImage(&image, QSize(newWidth, newHeight));
//        update();
//    }

   //QGraphicsItem *scene = this->scene()->activePanel() ;
    int w = this->parentWidget()->width();
    //this->setFixedWidth(w/3);
    this->setMaximumWidth(w/4);
//    this->scene()->clear();
//    this->scene()->items().clear();
//    this->scene()->addPixmap(this->scene().)
    update();
    emit refreshScene();
    QGraphicsView::resizeEvent(event);
}
