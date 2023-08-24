#ifndef PREVIEWGRAPHICSVIEW_H
#define PREVIEWGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWidget>

/**
 * @brief The PreviewGraphicsView class provides a custom QGraphicsView for previewing graphics.
 *
 * This class extends QGraphicsView and adds functionality for handling resize events and emitting a signal
 * to request a scene refresh.
 */
class PreviewGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a PreviewGraphicsView.
     * @param parent The parent QWidget of this view.
     */
    explicit PreviewGraphicsView(QWidget *parent = nullptr);

    /**
     * @brief Handles resize events for the view.
     * @param event A pointer to the QResizeEvent object containing event details.
     */
    void resizeEvent(QResizeEvent *event) override;

signals:
    /**
     * @brief Signal emitted when the scene needs to be refreshed.
     */
    void refreshScene();

};

#endif // PREVIEWGRAPHICSVIEW_H
