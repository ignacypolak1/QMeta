#include "fileexplorercontroller.h"
#include <QFileInfoList>

FileExplorerController::FileExplorerController(FileModel *model, QObject *parent) : QObject(parent), model(model) {
    
    currentDirectory = QDir(QDir::homePath());

    listFilesInDirectory();
}

bool FileExplorerController::isImage(const QString &fileName) {
    for(const QString &format: IMAGES_FORMATS) {
        if(fileName.endsWith(format, Qt::CaseSensitive)) {
            return true;
        }
    }
    return false;
}

void FileExplorerController::CR(const QString& path) {
    QFileInfo fileInfo(path);

    if (!fileInfo.exists()) {
        return;
    }

    if(fileInfo.isDir()) {

        currentDirectory = QDir(path);
        listFilesInDirectory();    

    } else if (fileInfo.isFile()) {
        
        QFile file(path);

        if(isImage(file.fileName())) {
            model->readMeta(path);
        } else {
            return;
        }
    }
}

void FileExplorerController::listFilesInDirectory() {
    QFileInfoList fileList = currentDirectory.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);
    
    model->clearFiles();

    if (currentDirectory.absolutePath() != QDir::rootPath()) {
        FileItem upItem;
        upItem.name = "..";
        QDir parentDir = currentDirectory;
        parentDir.cdUp();
        upItem.path = parentDir.absolutePath();
        model->addFile(upItem);
    }

    for(const QFileInfo &fileInfo : fileList) {
        FileItem item;
        item.name = fileInfo.fileName();
        item.path = fileInfo.absoluteFilePath();
        item.extension = fileInfo.isDir() ? "/" : fileInfo.suffix();
        model->addFile(item);
    }
}