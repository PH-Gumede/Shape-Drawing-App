#include "shape.h"
#include <QDebug>

Shape::Shape(int pw, QColor pc, QColor fc, QObject *parent)
    : QObject(parent), penWidth(pw), penColor(pc), fillColor(fc)
{
    qDebug()<< "Full Parameterized Shape object created";
}

Shape::~Shape()
{
    qDebug()<< "Shape object destroyed";
}

//Getters
int Shape::getPenWidth() const{
    return penWidth;
}

QColor Shape::getPenColor() const{
    return penColor;
}

QColor Shape::getFillColor() const{
    return fillColor;
}

//Setters
void Shape::setPenWidth(int width){
    penWidth = width;
}

void Shape::setPenColor(QColor &color){
    penColor = color;
}
void Shape::setFillColor(QColor &color){
    fillColor = color;
}
