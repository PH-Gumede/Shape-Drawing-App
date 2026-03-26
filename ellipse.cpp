#include "ellipse.h"
#include <QDebug>
#include <QWidget>

Ellipse::Ellipse(int pWidth, QColor pColor, QColor fColor, int radiusX, int radiusY, QObject *parent)
    : Shape2Property(pWidth, pColor, fColor, radiusX, radiusY, parent)
{
    qDebug() << "Full Parameterized Ellipse object created";
}

Ellipse::~Ellipse()
{
    qDebug() << "Ellipse object destroyed";
}

void Ellipse::draw(QPainter &painter, QWidget *widget)
{
    QPen pen(penColor);
    pen.setWidth(penWidth);
    painter.setPen(pen);

    QBrush brush(fillColor);
    painter.setBrush(brush);

    int rx = property1;  // x-radius
    int ry = property2;  // y-radius

    int x = (widget->width()  / 2) - rx;
    int y = (widget->height() / 2) - ry;

    painter.drawEllipse(x, y, rx * 2, ry * 2);
}
