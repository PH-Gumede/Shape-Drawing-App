#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape2property.h"

class Rectangle : public Shape2Property
{
    Q_OBJECT
public:
    Rectangle(int pWidth, QColor pColor, QColor fColor, int rectWidth, int rectHeight, QObject *parent = nullptr);
    ~Rectangle() override;

    QString getType() const override { return "Rectangle"; }
    void draw(QPainter &painter, QWidget *widget) override;

signals:
};

#endif // RECTANGLE_H
