#include "filemodel.h"
#include <QFile>
#include <QFileInfo>

FileModel::FileModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int FileModel::rowCount(const QModelIndex &parent) const {
    if(parent.isValid())
        return 0;
    return files.size();
}

QVariant FileModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() || index.row() >= files.size())
        return QVariant();

    const FileItem &item = files.at(index.row());
    switch(role) {
    case NameRole:
        return item.name;
    case ExtensionRole:
        return item.extension;
    case PathRole:
        return item.path;
    case IconRole:
        return item.icon;
    default:
        return QVariant();
    }

    return QVariant();
}

QHash<int, QByteArray> FileModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ExtensionRole] = "extension";
    roles[PathRole] = "path";
    roles[IconRole] = "icon";
    return roles;
}

void FileModel::addFile(const FileItem &file) {
    beginInsertRows(QModelIndex(), files.size(), files.size());
    files.append(file);
    endInsertRows();
}

void FileModel::removeFile(int index) {
    beginRemoveRows(QModelIndex(), index, index);
    files.removeAt(index);
    endRemoveRows();
}

void FileModel::clearFiles() {
    beginRemoveRows(QModelIndex(), 0, files.size() - 1);
    files.clear();
    endRemoveRows();
}

QVariantMap FileModel::get(int index) const {
    if (index < 0 || index >= files.size())
        return QVariantMap();
    const FileItem &item = files.at(index);
    QVariantMap map;
    map["name"] = item.name;
    map["extension"] = item.extension;
    map["path"] = item.path;
    map["icon"] = item.icon;
    return map;
}

void FileModel::readMeta(const QString &path) {

    QMap<QString, QString> exifMap;

    QFileInfo fileInfo(path);
    std::string filePath = path.toStdString();

    if(fileInfo.exists() && fileInfo.isFile()) {
        currentlyOpenedFilePath = path;
    }

    try {
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(filePath);
        if(!image) {
            std::cerr << "Nie można otworzyć pliku: " << filePath << std::endl;
            return;
        }
        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();
        if(exifData.empty()) {
            std::cerr << "Brak metadanych w pliku: " << filePath << std::endl;
            return;
        }

        for(const auto &metadata: exifData) {
            exifMap[QString::fromStdString(metadata.key())] = QString::fromStdString(metadata.value().toString());
        }

        if(exifMap.isEmpty()) {
            return;
        } else {
            this->fileMetadata = exifMap;
        }
    } catch (...) {
        return;
    }
}
