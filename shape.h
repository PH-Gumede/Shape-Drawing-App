#ifndef SHAPE_H
#define SHAPE_H

#include <QObject>
#include <QPainter>
#include <QColor>

class Shape : public QObject
{
    Q_OBJECT

protected:
    int penWidth;
    QColor penColor;
    QColor fillColor;

public:
    Shape(int pWidth, QColor pColor, QColor fColor, QObject *parent = nullptr);
    virtual ~Shape();

    // Getters
    int getPenWidth() const;
    QColor getPenColor() const;
    QColor getFillColor() const;

    // Setters
    void setPenWidth(int width);
    void setPenColor(QColor &color);
    void setFillColor(QColor &color);

    // Returns the shape type name e.g. "Circle", "Square"
    // Every concrete shape must implement this
    virtual QString getType() const = 0;

    // Draw function
    virtual void draw(QPainter &painter, QWidget *widget) = 0;

signals:
};

#endif // SHAPE_H
