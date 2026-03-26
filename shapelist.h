#ifndef SHAPELIST_H
#define SHAPELIST_H

#include "shape.h"
#include "shapelistmemento.h"
#include <QList>

class ShapeList
{
public:
    // Returns the single instance of ShapeList
    static ShapeList& instance();

    void addShape(Shape *shape);
    Shape *getShape(int index) const;
    int size() const;
    bool isEmpty() const;

    // Navigation helpers
    Shape *next(int &currentIndex) const;
    Shape *previous(int &currentIndex) const;

    // Memento: snapshot the current list into a memento object
    ShapeListMemento createMemento() const;

    // Memento: wipe the current list and rebuild it from a memento.
    // shapeParent is passed in so new Shape objects get the correct Qt parent
    void restoreFromMemento(const ShapeListMemento &memento, QObject &shapeParent);

    // Removes all pointers from m_shapes (does NOT delete objects —
    // shapeParent owns the objects and deletes them via Qt's parent system)
    void clear();

private:
    ShapeList() = default;
    ~ShapeList() = default;

    // Prevent copying
    ShapeList(const ShapeList &) = delete;
    ShapeList &operator=(const ShapeList &) = delete;

    QList<Shape*> m_shapes;
};

#endif // SHAPELIST_H
