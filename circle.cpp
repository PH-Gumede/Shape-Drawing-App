#include "circle.h"
#include <QDebug>
#include <QWidget>

Circle::Circle(int pWidth, QColor pColor, QColor fColor, int radius, QObject *parent)
    : Shape1Property(pWidth, pColor, fColor, radius, parent)
{
    qDebug()<< "Full Parameterized Circle object created";
}

Circle::~Circle()
{
    qDebug()<< "Circle object destroyed";
}

void Circle::draw(QPainter &painter, QWidget *widget) {
    QPen pen(penColor);
    pen.setWidth(penWidth);
    painter.setPen(pen);

    QBrush brush(fillColor);
    painter.setBrush(brush);

    int radius = property1;

    // Centre the bounding rect within the widget
    int x = (widget->width()  / 2) - radius;
    int y = (widget->height() / 2) - radius;
    int diameter = radius * 2;

    painter.drawEllipse(x, y, diameter, diameter);
}
