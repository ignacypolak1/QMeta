#ifndef FILEEXPLORERCONTROLLER_H
#define FILEEXPLORERCONTROLLER_H

#include <QObject>
#include <QDir>
#include "filemodel.h"

class FileModel;

class FileExplorerController : public QObject
{
    Q_OBJECT

public:
    explicit FileExplorerController(FileModel *model, QObject *parent = nullptr);

public slots:
    void CR(const QString &path);

private:
    const QStringList IMAGES_FORMATS = {
        ".jpg", ".png", ".tiff",
        ".webp", ".xmp", ".gif",
        ".bmp"};

    FileModel *model;
    QDir currentDirectory;

    void listFilesInDirectory();
    bool isImage(const QString &fileName);
};

#endif // FILEEXPLORERCONTROLLER_H