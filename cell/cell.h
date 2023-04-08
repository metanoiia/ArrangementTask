#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QPaintEvent>

class Cell : public QObject
{
    Q_OBJECT
public:
    Cell( float x, float y, bool aval, float width, float height );

    bool isAvailable() const;
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;

    void setX( float x );
    void setY( float y );
    void setAvailable( bool value );
private:
    float m_x;
    float m_y;

    float m_width;
    float m_height;

    bool m_available;
};

#endif // CELL_H
