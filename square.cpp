#include "square.h"
#include <QDebug>
#include <QWidget>

Square::Square(int pWidth, QColor pColor, QColor fColor, int sideLength, QObject *parent)
    : Shape1Property(pWidth, pColor, fColor, sideLength, parent)
{
    qDebug() << "Full Parameterized Square object created";
}

Square::~Square()
{
    qDebug() << "Square object destroyed";
}

void Square::draw(QPainter &painter, QWidget *widget)
{
    QPen pen(penColor);
    pen.setWidth(penWidth);
    painter.setPen(pen);

    QBrush brush(fillColor);
    painter.setBrush(brush);

    int side = property1;

    int x = (widget->width()  / 2) - (side / 2);
    int y = (widget->height() / 2) - (side / 2);

    painter.drawRect(x, y, side, side);
}
