#include "shape1property.h"
#include <QDebug>

//Full Parameterized
Shape1Property::Shape1Property(int pWidth, QColor pColor, QColor fColor, int p1, QObject *parent)
    : Shape(pWidth, pColor, fColor, parent), property1(p1)
{
    qDebug()<< "Full Parameterized Shape1Property object created";
}

Shape1Property::~Shape1Property()
{
   qDebug()<< "Shape1Property object destroyed";
}

void Shape1Property::setProperty1(int p1)
{
    property1 = p1;
}

int Shape1Property::getProperty1() const{
    return property1;
}
