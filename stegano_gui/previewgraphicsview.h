#ifndef PREVIEWGRAPHICSVIEW_H
#define PREVIEWGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

class PreviewGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    PreviewGraphicsView();
    void resizeEvent(QResizeEvent *event);

signals:
    void refreshScene();

};

#endif // PREVIEWGRAPHICSVIEW_H
