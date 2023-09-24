#include <QPainter>
#include "overlay.h"


overlay::overlay(int width, int height, QColor color)
    : QGraphicsItem()
    , m_width(width)
    , m_left(0)
    , m_right(0)
    , m_boundingRect(0, 0, width, height) // draw within this rectangle
    , m_color(color)
{
}

overlay::~overlay()
{
}

QRectF overlay::boundingRect() const
{
    return m_boundingRect;
}

void overlay::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* )
{
    // compositing of pixels in original <-> overlay image
    // QPainter::CompositionMode_Difference / Overlay / Darken / HardLight / SoftLight
    painter->setCompositionMode(QPainter::CompositionMode_SoftLight);
    painter->setBrush(m_color);

	// the four vertices of the polygon for overlay
    const QPointF points[4] = {
            QPointF(0.0, 0.0),
            QPointF(0.0 , 0.0 + float(m_left)),
            QPointF(m_width, 0.0 + float(m_right)),
            QPointF(m_width, 0.0)
    };
    painter->drawPolygon(points, 4);
}


void overlay::setLeftHeight(int value)
{
    m_left = value;
}

void overlay::setRightHeight(int value)
{
    m_right = value;
}

void overlay::changeColor(QColor color)
{
    m_color = color;
}

QColor overlay::color() const
{
    return m_color;
}

