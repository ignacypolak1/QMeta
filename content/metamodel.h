#ifndef METAMODEL_H
#define METAMODEL_H

#include <QAbstractListModel>
#include <QList>

struct MetaItem
{
    QString key;
    QString value;
};

class MetaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<MetaItem> metadata READ getItems NOTIFY metadataChanged)

public:
    enum MetaRoles
    {
        KeyRole = Qt::UserRole + 1,
        ValueRole,
    };
    Q_ENUM(MetaRoles)

    explicit MetaModel(QObject *parent = nullptr);

    void addItem(const MetaItem &item);
    void removeItem(int index);
    void clearItems();

    Q_INVOKABLE QVariantMap get(int index) const;
    Q_INVOKABLE QList<MetaItem> getItems() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<MetaItem> metadata;

signals:
    void metadataChanged();
};

#endif // METAMODEL_H
