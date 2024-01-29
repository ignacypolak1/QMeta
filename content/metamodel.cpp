#include "metamodel.h"
#include <QFile>
#include <QFileInfo>

MetaModel::MetaModel(QObject *parent)
    : QAbstractListModel(parent)
{
    this->metadata = QList<MetaItem>();
}

void MetaModel::addItem(const MetaItem &item)
{
    beginInsertRows(QModelIndex(), metadata.size(), metadata.size());
    metadata.append(item);
    endInsertRows();
}

void MetaModel::removeItem(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    metadata.removeAt(index);
    endRemoveRows();
}

void MetaModel::clearItems()
{
    beginRemoveRows(QModelIndex(), 0, metadata.size() - 1);
    metadata.clear();
    endRemoveRows();
}

QVariantMap MetaModel::get(int index) const
{
    if (index < 0 || index >= metadata.size())
    {
        return QVariantMap();
    }

    const MetaItem &item = metadata.at(index);

    QVariantMap map;
    map["key"] = item.key;
    map["value"] = item.value;
    return map;
}

QList<MetaItem> MetaModel::getItems() const
{
    return this->metadata;
}

int MetaModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return metadata.size();
}

QVariant MetaModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= metadata.size())
        return QVariant();

    const MetaItem &item = metadata.at(index.row());

    switch (role)
    {
    case KeyRole:
        return item.key;
    case ValueRole:
        return item.value;
    default:
        return QVariant();
    }
    return QVariant();
}

QHash<int, QByteArray> MetaModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

QPointF MetaModel::getCoordinates() const
{
    return this->coordinates;
}

void MetaModel::setCoordinates(float x, float y)
{
    this->coordinates.setX(x);
    this->coordinates.setY(y);
}