#ifndef SHAPELISTMEMENTO_H
#define SHAPELISTMEMENTO_H

#include <QString>
#include <QColor>
#include <QList>

// Plain data struct — no pointers, no QObject, just raw values
// describing one shape completely
struct ShapeData {
    QString type;       // "Circle", "Square", "Rectangle", "Ellipse"
    int     penWidth;
    QColor  penColor;
    QColor  fillColor;
    int     property1;  // radius / side length
    int     property2;  // height / y-radius  (0 if unused)
};

// The Memento — holds a snapshot of the entire ShapeList at one point in time
// ShapeList creates it, MainWindow stores it, ShapeList reads it on restore
class ShapeListMemento
{
public:
    // Called by ShapeList::createMemento() to build the snapshot
    explicit ShapeListMemento(const QList<ShapeData> &data) : m_data(data) {}

    // Called by ShapeList::restoreFromMemento() to read the snapshot
    QList<ShapeData> getData() const {
        return m_data;
    }

private:
    QList<ShapeData> m_data;  // one ShapeData entry per shape in the list
};

#endif // SHAPELISTMEMENTO_H
