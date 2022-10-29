#include "cell.h"

Cell::Cell( float x, float y, bool aval ):
    m_x( x ),
    m_y( y ),
    m_available( aval )
{

}

bool Cell::isAvailable()
{
    return m_available;
}

float Cell::getX()
{
    return m_x;
}

float Cell::getY()
{
    return m_y;
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
