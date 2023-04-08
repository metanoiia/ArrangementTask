#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QGraphicsItem>
#include "cell/cell.h"
#include "target/target.h"

template < typename T >
class GraphicsItem;

template<>
class GraphicsItem < Cell > : public QGraphicsItem
{

private:
    const QColor availClr = QColor( 179, 255, 179 );  //green
    const QColor unavailClr = QColor( 255, 153, 128 );//red

    QRectF   m_boundingRect;
    QPen   * m_pen;
    QBrush * m_brush;

 public:
    GraphicsItem( const Cell & cell )
    {
        if( cell.isAvailable() )
            m_brush = new QBrush( availClr );
        else
            m_brush = new QBrush( unavailClr );

        m_pen = new QPen();
        m_pen->setWidth( 1 );
        m_pen->setStyle( Qt::SolidLine );
        m_pen->setCapStyle( Qt::FlatCap );
        m_pen->setColor( Qt::darkGray );

        m_boundingRect.setRect( cell.getX() - cell.getWidth() / 2,
                                cell.getY() - cell.getHeight() / 2,
                                cell.getWidth(),
                                cell.getHeight() );
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        Q_UNUSED( option );
        Q_UNUSED( widget );

        painter->setBrush( *m_brush );
        painter->setPen  ( *m_pen );
        painter->drawRect( m_boundingRect );
    }

    virtual QRectF boundingRect() const override
    {
        return m_boundingRect;
    }

    ~GraphicsItem()
    {
        delete m_brush;
        delete m_pen;
    }
};

template<>
class GraphicsItem < Target > : public QGraphicsItem
{
private:
    const float SCALING = 0.3;
    static constexpr size_t colorsNum = 10;

    QRectF   m_boundingRect;
    QRectF   m_outgRect;      //small external circle of icon
    QRectF   m_internalgRect; //small internal circle of icon

    QPen   * m_penOut;   //external circle pen
    QBrush * m_brushOut; //external circle brush

    QPen   * m_penIn;   //internal circle pen
    QBrush * m_brushIn; //internal circle brush

    QPen   * m_areaPen; //target reach circle

    float   m_radius; //target reach radius
    QPointF m_center;

    QColor colours[ colorsNum ] = { QColor( "cyan" ),    QColor( "magenta" ),   QColor( "red" ),
                                    QColor( "darkRed" ), QColor( "darkCyan" ),  QColor( "darkMagenta" ),
                                    QColor( "green" ),   QColor( "darkGreen" ), QColor( "yellow" ),
                                    QColor( "blue" ) }; //array of QColor's to generate colorful circles

 public:
    static inline size_t & colorCounter() { static size_t colorCnt; return colorCnt; };

    GraphicsItem( const Target & target, const float & w, const float & h )
    {
        colorCounter()++;

        float cellWidth = ( w <= h ) ? w * SCALING : h * SCALING;
        float cellHeight = cellWidth;

        size_t penWidth = cellWidth / 5;

        m_radius = target.getR();
        m_center = QPointF( target.getX(), target.getY() );

        m_areaPen = new QPen();
        m_areaPen->setWidth( penWidth );
        m_areaPen->setStyle( Qt::SolidLine );
        m_areaPen->setColor( colours[ colorCounter() % colorsNum ] );

        m_brushOut = new QBrush( Qt::darkGray );

        m_penOut = new QPen();
        m_penOut->setWidth( 1 );
        m_penOut->setStyle( Qt::SolidLine );
        m_penOut->setColor( Qt::darkGray );

        m_brushIn = new QBrush( Qt::gray );

        m_penIn = new QPen();
        m_penIn->setWidth( 1 );
        m_penIn->setStyle( Qt::SolidLine );
        m_penIn->setColor( Qt::gray );

        m_outgRect.setRect( target.getX() - cellWidth / 2,
                            target.getY() - cellHeight / 2,
                            cellWidth,
                            cellHeight );

        m_internalgRect.setRect( target.getX() - cellWidth / 6,
                                 target.getY() - cellHeight / 6,
                                 cellWidth / 3,
                                 cellHeight / 3 );

        m_boundingRect.setRect( target.getX() - m_radius,
                                target.getY() - m_radius,
                                2 * m_radius,
                                2 * m_radius );
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override
    {
        Q_UNUSED( option );
        Q_UNUSED( widget );

        painter->setPen     ( *m_areaPen );
        painter->drawEllipse( m_center, m_radius, m_radius );

        painter->setBrush   ( *m_brushOut );
        painter->setPen     ( *m_penOut );
        painter->drawEllipse( m_outgRect );

        painter->setBrush   ( *m_brushIn );
        painter->setPen     ( *m_penIn );
        painter->drawEllipse( m_internalgRect );
    }

    virtual QRectF boundingRect() const override
    {
        return m_boundingRect;
    }

    ~GraphicsItem()
    {
        delete m_penOut;
        delete m_brushOut;

        delete m_penIn;
        delete m_brushIn;

        delete m_areaPen;
    }
};

#endif //GRAPHICSITEM_H
