#ifndef OVERLAY_H
#define OVERLAY_H

#include <QGraphicsItem>

/*
 * The actual overlay class.
 * The left and right height controls make it redraw using paint()
 * */
class overlay : public QGraphicsItem
{
public:
    overlay(int width, int height, QColor color);
    ~overlay();

    QRectF boundingRect() const;
    void setLeftHeight(int value);
    void setRightHeight(int value);

    void changeColor(QColor color);
    QColor color() const;

private:
    int m_width;
    int m_left, m_right;
    QRectF m_boundingRect;
    QColor m_color;

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr);
};


#endif // OVERLAY_H

