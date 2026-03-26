#include "file.h"
#include "circle.h"
#include "square.h"
#include "rectangle.h"
#include "ellipse.h"

#include <QFile>
#include <QDebug>
#include <QtXml/QtXml>

File::File() {}

static const QMap<QString, QColor> &colorMap()
{
    static const QMap<QString, QColor> map = {
        {"Black",   Qt::black},  {"Red",     Qt::red},
        {"Green",   Qt::green},  {"Blue",    Qt::blue},
        {"Yellow",  Qt::yellow}, {"White",   Qt::white},
        {"Gray",    Qt::gray},   {"Cyan",    Qt::cyan},
        {"Magenta", Qt::magenta}
    };
    return map;
}

QString File::colorToString(const QColor &color)
{
    for (auto it = colorMap().begin(); it != colorMap().end(); ++it)
        if (it.value().rgb() == color.rgb())
            return it.key();
    return "Black";
}

QColor File::colorFromString(const QString &name)
{
    return colorMap().value(name, Qt::black);
}

bool File::saveToXml(const QString &filePath, const ShapeList &list)
{
    QDomDocument doc;
    QDomElement root = doc.createElement("shapeList");
    doc.appendChild(root);

    for (int i = 0; i < list.size(); ++i)
    {
        Shape *s = list.getShape(i);
        QDomElement elem = doc.createElement("shape");

        if (auto *c = dynamic_cast<Circle*>(s)) {
            elem.setAttribute("type", "Circle");
            elem.setAttribute("p1", c->getProperty1());
            elem.setAttribute("p2", "");
        } else if (auto *sq = dynamic_cast<Square*>(s)) {
            elem.setAttribute("type", "Square");
            elem.setAttribute("p1", sq->getProperty1());
            elem.setAttribute("p2", "");
        } else if (auto *r = dynamic_cast<Rectangle*>(s)) {
            elem.setAttribute("type", "Rectangle");
            elem.setAttribute("p1", r->getProperty1());
            elem.setAttribute("p2", r->getProperty2());
        } else if (auto *e = dynamic_cast<Ellipse*>(s)) {
            elem.setAttribute("type", "Ellipse");
            elem.setAttribute("p1", e->getProperty1());
            elem.setAttribute("p2", e->getProperty2());
        } else {
            continue;
        }

        elem.setAttribute("pw", s->getPenWidth());
        elem.setAttribute("pc", colorToString(s->getPenColor()));
        elem.setAttribute("fc", colorToString(s->getFillColor()));
        root.appendChild(elem);
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "File::saveToXml – could not open" << filePath;
        return false;
    }
    QTextStream stream(&file);
    stream << doc.toString();
    file.close();
    qDebug() << "File::saveToXml – saved" << list.size() << "shapes";
    return true;
}

bool File::loadFromXml(const QString &filePath, ShapeList &list, QObject *parent)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File::loadFromXml – file not found, starting fresh:" << filePath;
        return false;
    }

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        qDebug() << "File::loadFromXml – failed to parse XML";
        file.close();
        return false;
    }
    file.close();

    QDomElement root = doc.firstChildElement("shapeList");
    QDomNodeList items = root.elementsByTagName("shape");

    for (int i = 0; i < items.count(); ++i)
    {
        QDomElement e = items.at(i).toElement();
        if (e.isNull()) continue;

        QString type = e.attribute("type");
        int     pw   = e.attribute("pw").toInt();
        QColor  pc   = colorFromString(e.attribute("pc"));
        QColor  fc   = colorFromString(e.attribute("fc"));
        int     p1   = e.attribute("p1").toInt();
        int     p2   = e.attribute("p2").toInt();

        Shape *s = nullptr;
        if      (type == "Circle")    s = new Circle    (pw, pc, fc, p1,     parent);
        else if (type == "Square")    s = new Square     (pw, pc, fc, p1,     parent);
        else if (type == "Rectangle") s = new Rectangle  (pw, pc, fc, p1, p2, parent);
        else if (type == "Ellipse")   s = new Ellipse    (pw, pc, fc, p1, p2, parent);

        if (s)
            list.addShape(s);
    }

    qDebug() << "File::loadFromXml – loaded" << items.count() << "shapes";
    return true;
}
