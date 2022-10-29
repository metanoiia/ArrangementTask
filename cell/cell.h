#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
public:
    Cell( float x, float y, bool aval );

    bool isAvailable();
    float getX();
    float getY();

    void setX( float x );
    void setY( float y );
    void setAvailable( bool value );
private:
    float m_x;
    float m_y;

    bool m_available;
};

#endif // CELL_H
