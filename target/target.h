#ifndef TARGET_H
#define TARGET_H

#include <QObject>

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

    float getX();
    float getY();
    unsigned int getlineNum();
};

#endif // TARGET_H
