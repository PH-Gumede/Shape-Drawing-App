#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape2property.h"

class Ellipse : public Shape2Property
{
    Q_OBJECT
public:
    Ellipse(int pWidth, QColor pColor, QColor fColor, int radiusX, int radiusY, QObject *parent = nullptr);
    ~Ellipse() override;

    QString getType() const override { return "Ellipse"; }
    void draw(QPainter &painter, QWidget *widget) override;

signals:
};

#endif // ELLIPSE_H
