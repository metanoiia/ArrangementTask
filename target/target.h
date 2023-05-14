#ifndef TARGET_H
#define TARGET_H

#include <QObject>
#include <QGraphicsItem>

class Target : public QObject
{
    Q_OBJECT
private:
    float m_xCoord;
    float m_yCoord;
    float m_radius;

    unsigned int m_price;

    unsigned int m_lineNum;
public:
    Target( float xCoord, float yCoord, float radius,
            unsigned int price, unsigned int lineNum );
    ~Target();

    float getX() const;
    float getY() const;
    float getR() const;

    void setX( float x );
    void setY( float y );

    unsigned int getlineNum();

    bool isReachable( const Target * other );
};

#endif // TARGET_H
