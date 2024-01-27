#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>
#include <QList>

#include <iostream>
#include <exiv2/exiv2.hpp>
#include <string>

struct FileItem {
    QString name;
    QString extension;
    QString path;
    QString icon;
};

class FileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit FileModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void addFile(const FileItem &file);
    void removeFile(int index);
    void clearFiles();
    void readMeta(const QString &path);
    Q_INVOKABLE QVariantMap get(int index) const;

    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        ExtensionRole,
        PathRole,
        IconRole
    };
    Q_ENUM(FileRoles)

protected:
    QHash<int, QByteArray> roleNames() const override;


private:
    QList<FileItem> files;
    QString currentlyOpenedFilePath;
    QMap<QString, QString> fileMetadata;
};

#endif // FILEMODEL_H
