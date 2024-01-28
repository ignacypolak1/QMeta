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
    }
    catch (...)
    {
        return;
    }
}