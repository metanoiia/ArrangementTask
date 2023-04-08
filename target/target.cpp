#include "target.h"

Target::Target( float xCoord, float yCoord, float radius, unsigned int price, unsigned int lineNum ):
    m_xCoord ( xCoord ),
    m_yCoord ( yCoord ),
    m_radius ( radius ),
    m_price  ( price ),
    m_lineNum( lineNum ) { }

Target::~Target() { }

float Target::getX() const { return m_xCoord; }

float Target::getY() const { return m_yCoord; }

float Target::getR() const { return m_radius; }

void Target::setX( float x ) { m_xCoord = x; }

void Target::setY( float y ) { m_yCoord = y; }

unsigned int Target::getlineNum() { return m_lineNum; }
