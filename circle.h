#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape1property.h"
#include <QObject>

class Circle : public Shape1Property
{
    Q_OBJECT
public:
    Circle(int pWidth, QColor pColor, QColor fColor, int radius, QObject *parent = nullptr);
    ~Circle() override;

    QString getType() const override { return "Circle"; }
    void draw(QPainter &painter, QWidget *widget) override;

signals:
};

#endif // CIRCLE_H
