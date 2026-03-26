#include "rectangle.h"
#include <QDebug>
#include <QWidget>

Rectangle::Rectangle(int pWidth, QColor pColor, QColor fColor, int rectWidth, int rectHeight, QObject *parent)
    : Shape2Property(pWidth, pColor, fColor, rectWidth, rectHeight, parent)
{
    qDebug() << "Full Parameterized Rectangle object created";
}

Rectangle::~Rectangle()
{
    qDebug() << "Rectangle object destroyed";
}

void Rectangle::draw(QPainter &painter, QWidget *widget)
{
    QPen pen(penColor);
    pen.setWidth(penWidth);
    painter.setPen(pen);

    QBrush brush(fillColor);
    painter.setBrush(brush);

    int w = property1;
    int h = property2;

    int x = (widget->width()  / 2) - (w / 2);
    int y = (widget->height() / 2) - (h / 2);

    painter.drawRect(x, y, w, h);
}
