#include "target.h"

Target::Target( float xCoord, float yCoord, float radius, unsigned int price, unsigned int lineNum ):
    m_xCoord ( xCoord ),
    m_yCoord ( yCoord ),
    m_radius ( radius ),
    m_price  ( price ),
    m_lineNum( lineNum )
{

}

Target::~Target()
{

}

float Target::getX()
{
    return m_xCoord;
}

float Target::getY()
{
    return m_yCoord;
}

unsigned int Target::getlineNum()
{
    return m_lineNum;
}
