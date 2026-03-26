#include "shape2property.h"
#include <QDebug>

Shape2Property::Shape2Property(int pWidth, QColor pColor, QColor fColor, int p1, int p2, QObject *parent)
    : Shape1Property(pWidth, pColor, fColor, p1, parent), property2(p2)
{
    qDebug()<< "Full Parameterized Shape2Property object created";
}

Shape2Property::~Shape2Property()
{
    qDebug()<< "Shape2Property object destroyed";
}

void Shape2Property::setProperty2(int p2)
{
    property2 = p2;
}

int Shape2Property::getProperty2() const{
    return property2;
}
