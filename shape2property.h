#ifndef SHAPE2PROPERTY_H
#define SHAPE2PROPERTY_H

#include "shape1property.h"

#include <QObject>

class Shape2Property : public Shape1Property
{
    Q_OBJECT

protected:
    int property2;

public:
    //Full Param
    Shape2Property(int pWidth, QColor pColor, QColor fColor, int p1, int p2, QObject *parent = nullptr);

    ~Shape2Property() override;

    virtual void draw(QPainter &painter, QWidget *widget) = 0;

    void setProperty2(int p2);

    int getProperty2() const;

signals:
};

#endif // SHAPE2PROPERTY_H
