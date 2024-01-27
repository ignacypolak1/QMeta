#include "fileexplorercontroller.h"
#include <QFileInfoList>

FileExplorerController::FileExplorerController(FileModel *model, QObject *parent) : QObject(parent), model(model) {
    
    currentDirectory = QDir(QDir::homePath());

    listFilesInDirectory();
}

void FileExplorerController::CR(const QString& path) {
    QDir newDir(path);
    if (!newDir.exists()) {
        return;
    }
    
    currentDirectory = newDir;
    listFilesInDirectory();
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