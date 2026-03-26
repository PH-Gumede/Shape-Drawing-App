#ifndef SQUARE_H
#define SQUARE_H

#include "shape1property.h"
#include <QObject>

class Square : public Shape1Property
{
    Q_OBJECT
public:
    Square(int pWidth, QColor pColor, QColor fColor, int sideLength, QObject *parent = nullptr);
    ~Square() override;

    QString getType() const override { return "Square"; }
    void draw(QPainter &painter, QWidget *widget) override;

signals:
};

#endif // SQUARE_H
