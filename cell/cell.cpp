#include "cell.h"

Cell::Cell( float x, float y, bool aval, float width, float height ):
    m_x( x ),
    m_y( y ),
    m_width( width ),
    m_height( height ),
    m_available( aval ) { }

bool Cell::isAvailable() const { return m_available; }

float Cell::getX() const { return m_x; }

float Cell::getY() const { return m_y; }

float Cell::getWidth() const { return m_width; }

float Cell::getHeight() const { return m_height; }

void Cell::setX( float x ) { m_x = x; }

void Cell::setY( float y ) { m_y = y; }

void Cell::setAvailable( bool value ) { m_available = value; }
