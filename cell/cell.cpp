#include "cell.h"

Cell::Cell( float x, float y, bool aval, float width, float height ):
    m_x( x ),
    m_y( y ),
    m_width( width ),
    m_height( height ),
    m_available( aval )
{

}

bool Cell::isAvailable() const
{
    return m_available;
}

float Cell::getX() const
{
    return m_x;
}

float Cell::getY() const
{
    return m_y;
}

float Cell::getWidth() const
{
    return m_width;
}

float Cell::getHeight() const
{
    return m_height;
}

void Cell::setX( float x )
{
    m_x = x;
}

void Cell::setY( float y )
{
    m_y = y;
}

void Cell::setAvailable( bool value )
{
    m_available = value;
}

CellItem::CellItem( const Cell & cell ) : QObject()
{
    if( cell.isAvailable() )
        m_brush = new QBrush( ( QColor( 179, 255, 179 ) ) ); // green
    else
        m_brush = new QBrush( ( QColor( 255, 153, 128 ) ) ); //red

    m_pen = new QPen();
    m_pen->setWidth( 1 );
    m_pen->setStyle( Qt::SolidLine );
    m_pen->setColor( Qt::darkGray );

    m_boundingRect.setRect( cell.getX() - cell.getWidth() / 2,
                            cell.getY() - cell.getHeight() / 2,
                            cell.getWidth(),
                            cell.getHeight() );
}

void CellItem::paint( QPainter * painter,
                      const QStyleOptionGraphicsItem * option,
                      QWidget * widget )
{
    Q_UNUSED( option );
    Q_UNUSED( widget );

    painter->setBrush( *m_brush );
    painter->setPen  ( *m_pen );
    painter->drawRect( m_boundingRect );
}

QRectF CellItem::boundingRect() const
{
    return m_boundingRect;
}

CellItem::~CellItem()
{
    delete m_brush;
    delete m_pen;
}
