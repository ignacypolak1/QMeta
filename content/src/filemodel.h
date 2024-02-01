#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <iostream>
#include <string>

struct FileItem
{
    QString name;
    QString extension;
    QString path;
    QString icon;
};

class FileModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<FileItem> files READ getItems NOTIFY filesChanged)

public:
    enum FileRoles
    {
        NameRole = Qt::UserRole + 1,
        ExtensionRole,
        PathRole,
        IconRole
    };
    Q_ENUM(FileRoles)

    explicit FileModel(QObject *parent = nullptr);

    void addItem(const FileItem &item);
    void removeItem(int index);
    void clearItems();

    Q_INVOKABLE QVariantMap get(int index) const;
    Q_INVOKABLE QList<FileItem> getItems() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<FileItem> files;

signals:
    void filesChanged();
};

#endif // FILEMODEL_H
