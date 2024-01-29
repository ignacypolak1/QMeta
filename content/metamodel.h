#ifndef METAMODEL_H
#define METAMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QPointF>

struct MetaItem
{
    QString key;
    QString value;
};

class MetaModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QList<MetaItem> metadata READ getItems NOTIFY metadataChanged)
    Q_PROPERTY(QPointF coordinates READ getCoordinates NOTIFY coordinatesChanged)

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
    Q_INVOKABLE QPointF getCoordinates() const;
    void setCoordinates(float x, float y);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QPointF coordinates;
    QList<MetaItem> metadata;

signals:
    void metadataChanged();
    void coordinatesChanged();
};

#endif // METAMODEL_H
