#ifndef FILEEXPLORERCONTROLLER_H
#define FILEEXPLORERCONTROLLER_H

#include <QObject>
#include <QDir>
#include "filemodel.h"

class FileModel;

class FileExplorerController: public QObject {
    Q_OBJECT

    public:
        explicit FileExplorerController(FileModel* model, QObject *parent = nullptr);
    
    public slots:
        void CR(const QString& path);
    
    private:
        FileModel *model;
        QDir currentDirectory;

        void listFilesInDirectory();
};

#endif // FILEEXPLORERCONTROLLER_H