#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDir>

#include "filemodel.h"
#include "metamodel.h"

#include <iostream>
#include <exiv2/exiv2.hpp>
#include <string>

class FileModel;
class MetaModel;

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(FileModel *fileModel, MetaModel *metaModel, QObject *parent = nullptr);

public slots:
    void CR(const QString &path);

private:
    const QStringList IMAGES_FORMATS = {
        ".jpg", ".png", ".tiff",
        ".webp", ".xmp", ".gif",
        ".bmp"};

    FileModel *fileModel;
    MetaModel *metaModel;

    QDir currentDirectory;
    QString currentFile;

    void listFilesInDirectory();
    bool isImage(const QString &fileName);
    void readMeta(const QString &path);
    std::string trim(std::string str);
};

#endif // CONTROLLER_H