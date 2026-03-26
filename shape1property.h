#ifndef SHAPE1PROPERTY_H
#define SHAPE1PROPERTY_H

#include <QObject>
#include "shape.h"

class Shape1Property : public Shape
{
    Q_OBJECT
protected:
    int property1;

public:
    //Full Parameterized
    Shape1Property(int pWidth, QColor pColor, QColor fColor, int p1, QObject *parent = nullptr);

    ~Shape1Property() override;

    virtual void draw(QPainter &painter, QWidget *widget) = 0;

    void setProperty1(int p1);

    int getProperty1() const;

signals:
};

#endif // SHAPE1PROPERTY_H
