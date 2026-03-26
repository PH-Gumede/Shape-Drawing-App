#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QColor>
#include "shapelist.h"

class File
{
public:
    File();

    static bool saveToXml(const QString &filePath, const ShapeList &list);
    static bool loadFromXml(const QString &filePath, ShapeList &list, QObject *parent);

    static QString colorToString(const QColor &color);
    static QColor  colorFromString(const QString &name);
};

#endif // FILE_H
