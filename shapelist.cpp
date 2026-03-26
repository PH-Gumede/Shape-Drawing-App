#include "shapelist.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "ellipse.h"
#include <QDebug>

ShapeList& ShapeList::instance()
{
    static ShapeList s_instance;
    return s_instance;
}

void ShapeList::addShape(Shape *shape)
{
    m_shapes.append(shape);
    qDebug() << "ShapeList: shape added, total count =" << m_shapes.size();
}

Shape *ShapeList::getShape(int index) const
{
    if (index < 0 || index >= m_shapes.size())
        return nullptr;
    return m_shapes[index];
}

int ShapeList::size() const
{
    return m_shapes.size();
}

bool ShapeList::isEmpty() const
{
    return m_shapes.isEmpty();
}

Shape *ShapeList::next(int &currentIndex) const
{
    if (m_shapes.isEmpty()) return nullptr;
    currentIndex = (currentIndex + 1) % m_shapes.size();
    return m_shapes[currentIndex];
}

Shape *ShapeList::previous(int &currentIndex) const
{
    if (m_shapes.isEmpty()) return nullptr;
    currentIndex = (currentIndex - 1 + m_shapes.size()) % m_shapes.size();
    return m_shapes[currentIndex];
}

void ShapeList::clear()
{
    // Only clear the pointer list — shapeParent owns and deletes the objects
    m_shapes.clear();
    qDebug() << "ShapeList: cleared all pointers";
}

// --- Memento: Save ---
// Walk every shape pointer, extract its plain data, pack into a memento
ShapeListMemento ShapeList::createMemento() const
{
    QList<ShapeData> snapshot;

    for (Shape *s : m_shapes) {
        ShapeData data;
        data.type      = s->getType();
        data.penWidth  = s->getPenWidth();
        data.penColor  = s->getPenColor();
        data.fillColor = s->getFillColor();

        // Shape1Property and Shape2Property expose getProperty1/2
        // We can safely cast because every shape in the hierarchy has property1
        if (auto *s1 = qobject_cast<Shape1Property*>(s)) {
            data.property1 = s1->getProperty1();
        }
        // Only Rectangle and Ellipse have property2
        if (auto *s2 = qobject_cast<Shape2Property*>(s)) {
            data.property2 = s2->getProperty2();
        } else {
            data.property2 = 0;
        }

        snapshot.append(data);
    }

    qDebug() << "ShapeList: memento created with" << snapshot.size() << "shapes";
    return ShapeListMemento(snapshot);
}

// --- Memento: Restore ---
// 1. Delete all current shape objects via shapeParent
// 2. Clear the pointer list
// 3. Rebuild each shape from the saved ShapeData
void ShapeList::restoreFromMemento(const ShapeListMemento &memento, QObject &shapeParent)
{
    // Step 1: Delete all child Shape objects owned by shapeParent.
    // qDeleteAll deletes each pointer; we take a copy of the list first
    // because deleting a child modifies shapeParent.children() mid-loop.
    const QObjectList children = shapeParent.children();
    qDeleteAll(children);

    // Step 2: Clear the stale pointers from our list
    m_shapes.clear();

    // Step 3: Rebuild shapes from the plain data in the memento
    for (const ShapeData &data : memento.getData()) {
        Shape *newShape = nullptr;

        if (data.type == "Circle") {
            newShape = new Circle(data.penWidth, data.penColor, data.fillColor,
                                  data.property1, &shapeParent);
        } else if (data.type == "Square") {
            newShape = new Square(data.penWidth, data.penColor, data.fillColor,
                                  data.property1, &shapeParent);
        } else if (data.type == "Rectangle") {
            newShape = new Rectangle(data.penWidth, data.penColor, data.fillColor,
                                     data.property1, data.property2, &shapeParent);
        } else if (data.type == "Ellipse") {
            newShape = new Ellipse(data.penWidth, data.penColor, data.fillColor,
                                   data.property1, data.property2, &shapeParent);
        }

        if (newShape)
            m_shapes.append(newShape);
    }

    qDebug() << "ShapeList: restored" << m_shapes.size() << "shapes from memento";
}
