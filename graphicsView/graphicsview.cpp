#include "graphicsview.h"
#include <QDebug>

const qreal SCALE_FACTOR = 1.1;

GraphicsView::GraphicsView( QWidget * parent ):
    QGraphicsView( parent ),
    m_panStartX( 0 ),
    m_panStartY( 0 ),
    m_leftButtonPressed( false )
{
    setCacheMode( QGraphicsView::CacheBackground );
}

void GraphicsView::wheelEvent( QWheelEvent * event )
{

    const QPointF p0Scene = mapToScene( event->pos() );

    int angle = event->angleDelta().y();

    qreal factor;

    if ( angle > 0 )
    {
        factor = SCALE_FACTOR;
        scale( factor, factor );
    }
    else
    {
        factor = 1 / SCALE_FACTOR;
        scale( factor, factor );
    }

    const QPointF p1Mouse = mapFromScene( p0Scene );
    const QPointF move = p1Mouse - event->pos();

    horizontalScrollBar()->setValue( move.x() + horizontalScrollBar()->value() );
    verticalScrollBar()->setValue( move.y() + verticalScrollBar()->value() );

    event->accept();
}

void GraphicsView::mousePressEvent( QMouseEvent * event )
{
    if ( event->button() == Qt::LeftButton )
    {
        m_leftButtonPressed = true;
        m_panStartX = event->x();
        m_panStartY = event->y();

        setCursor( Qt::ClosedHandCursor );
        event->accept();
    }
    else
    {
        m_leftButtonPressed = false;
        event->ignore();
    }
}

void GraphicsView::mouseReleaseEvent( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
    {
        m_leftButtonPressed = false;
        setCursor( Qt::ArrowCursor );
        event->accept();
    }
    else
    {
        m_leftButtonPressed = true;
        event->ignore();
    }
}

void GraphicsView::mouseMoveEvent( QMouseEvent *event )
{
    if ( m_leftButtonPressed )
    {
        horizontalScrollBar()->setValue( horizontalScrollBar()->value() - ( event->x() - m_panStartX ) );
        verticalScrollBar()->setValue( verticalScrollBar()->value() - ( event->y() - m_panStartY ) );
        m_panStartX = event->x();
        m_panStartY = event->y();
        event->accept();
    }
    else
        event->ignore();
}

