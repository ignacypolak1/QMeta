#include "controller.h"
#include <QFileInfoList>

Controller::Controller(FileModel *fileModel, MetaModel *metaModel, QObject *parent) : QObject(parent), fileModel(fileModel), metaModel(metaModel)
{
    currentDirectory = QDir(QDir::homePath());
    listFilesInDirectory();
}

bool Controller::isImage(const QString &fileName)
{
    for (const QString &format : IMAGES_FORMATS)
    {
        if (fileName.endsWith(format, Qt::CaseSensitive))
        {
            return true;
        }
    }
    return false;
}

void Controller::CR(const QString &path)
{
    QFileInfo fileInfo(path);

    if (!fileInfo.exists())
    {
        return;
    }

    if (fileInfo.isDir())
    {
        currentDirectory = QDir(path);
        listFilesInDirectory();
    }

    else if (fileInfo.isFile())
    {

        QFile file(path);

        if (isImage(file.fileName()))
        {
            readMeta(path);
        }
        else
        {
            return;
        }
    }
}

void Controller::listFilesInDirectory()
{
    QFileInfoList fileList = currentDirectory.entryInfoList(QDir::NoDotAndDotDot | QDir::AllEntries);

    fileModel->clearItems();

    if (currentDirectory.absolutePath() != QDir::rootPath())
    {
        FileItem upItem;
        upItem.name = "..";
        QDir parentDir = currentDirectory;
        parentDir.cdUp();
        upItem.path = parentDir.absolutePath();
        fileModel->addItem(upItem);
    }

    for (const QFileInfo &fileInfo : fileList)
    {
        FileItem item;
        item.name = fileInfo.fileName();
        item.path = fileInfo.absoluteFilePath();
        item.extension = fileInfo.isDir() ? "/" : fileInfo.suffix();
        fileModel->addItem(item);
    }
}

std::string Controller::trim(std::string s)
{
    s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [](unsigned char ch)
                                        { return std::isspace(ch); }));

    s.erase(std::find_if_not(s.rbegin(), s.rend(), [](unsigned char ch)
                             { return std::isspace(ch); })
                .base(),
            s.end());

    return s;
}

bool Controller::canExtractGPSCoords(const QStringList &keys, QMap<QString, QString> &map)
{
    const QList<MetaItem> metaItems = metaModel->getItems();
    for (const QString &key : keys)
    {
        bool found = false;
        for (const MetaItem &item : metaItems)
        {
            if (item.key == key)
            {
                found = true;
                map[key] = item.value;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

QPointF Controller::convertGPSValuesToCoords(QString latRef, QString lat, QString lonRef, QString lon)
{
    auto dmsToDecimal = [](const QString &dms) -> float
    {
        QStringList parts = dms.split(' ');
        float degrees = parts[0].split("/")[0].toDouble() / parts[0].split('/')[1].toDouble();
        float minutes = parts[1].split("/")[0].toDouble() / parts[1].split('/')[1].toDouble();
        float seconds = parts[2].split("/")[0].toDouble() / parts[2].split('/')[1].toDouble();

        return degrees + (minutes / 60.0) + (seconds / 3600.0);
    };

    float latFloat = dmsToDecimal(lat);
    float lonFloat = dmsToDecimal(lon);

    if (latRef == "S")
        latFloat *= -1;
    if (latRef == "W")
        lonFloat *= -1;

    return QPointF(latFloat, lonFloat);
}

void Controller::readMeta(const QString &path)
{

    QVariantMap exifMap;

    QFileInfo fileInfo(path);
    std::string filePath = path.toStdString();

    if (fileInfo.exists() && fileInfo.isFile())
    {
        this->currentFile = path;
    }

    try
    {
        Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(filePath);

        if (!image)
        {
            std::cerr << "Can't open file: " << filePath << std::endl;
            return;
        }

        image->readMetadata();

        Exiv2::ExifData &exifData = image->exifData();

        if (exifData.empty())
        {
            std::cerr << "No metadata in file: " << filePath << std::endl;
            return;
        }

        for (const auto &metadata : exifData)
        {
            MetaItem item;

            item.key = QString::fromStdString(trim(metadata.key()));
            item.value = QString::fromStdString(trim(metadata.value().toString()));

            this->metaModel->addItem(item);
        }

        QStringList requiredKeys = {
            "Exif.GPSInfo.GPSLatitudeRef",
            "Exif.GPSInfo.GPSLatitude",
            "Exif.GPSInfo.GPSLongitudeRef",
            "Exif.GPSInfo.GPSLongitude"};

        QMap<QString, QString> tempMap;

        if (canExtractGPSCoords(requiredKeys, tempMap))
        {
            QPointF coords = convertGPSValuesToCoords(
                tempMap["Exif.GPSInfo.GPSLatitudeRef"],
                tempMap["Exif.GPSInfo.GPSLatitude"],
                tempMap["Exif.GPSInfo.GPSLongitudeRef"],
                tempMap["Exif.GPSInfo.GPSLongitude"]);
            metaModel->setCoordinates(coords.x(), coords.y());
        }
    }
    catch (...)
    {
        return;
    }
}