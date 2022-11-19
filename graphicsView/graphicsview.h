#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QScrollBar>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
    qreal m_panStartX;
    qreal m_panStartY;

    bool m_leftButtonPressed;

public:
    GraphicsView( QWidget *parent = nullptr );

protected:
    void wheelEvent( QWheelEvent * event );
    void mousePressEvent( QMouseEvent * event);
    void mouseReleaseEvent( QMouseEvent * event );
    void mouseMoveEvent( QMouseEvent * event );
};

#endif // GRAPHICSVIEW_H
