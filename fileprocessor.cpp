#include "fileprocessor.h"
#include "windows.h"

FileProcessor::FileProcessor(
    const QString &inputMask,
    const QString &outputPath,
    bool deleteInputFiles,
    bool overwriteOutputFiles,
    bool runOnce,
    const QByteArray &xorKey,
    int checkInterval,
    QObject *parent
    ) : QObject(parent),
    inputMask(inputMask),
    outputDirectory(outputPath),
    deleteInputFiles(deleteInputFiles),
    overwriteOutputFiles(overwriteOutputFiles),
    runOnce(runOnce),
    xorKey(xorKey),
    checkInterval(checkInterval)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FileProcessor::processFiles);
}

void FileProcessor::start()
{
    this->processFiles();

    if (!this->runOnce) {
        timer->start(this->checkInterval * 1000);
    }
}

void FileProcessor::processFiles()
{   
    QDir dir(QDir::currentPath());
    QStringList filters;

    filters << this->inputMask;
    dir.setNameFilters(filters);

    QFileInfoList fileList = dir.entryInfoList(QDir::Files);

    for (const QFileInfo &fileInfo : fileList) {
        qDebug() << fileInfo.filePath().toLocal8Bit();
        HANDLE fileHandle = CreateFileA(
            fileInfo.filePath().toLocal8Bit(),
            GENERIC_READ,
            0,
            NULL,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (fileHandle == INVALID_HANDLE_VALUE) {
            DWORD error = GetLastError();

            if (error == ERROR_SHARING_VIOLATION) {
                qWarning() << "File isn't closed: " << fileInfo.fileName() << error;

                continue;
            }
        }

        CloseHandle(fileHandle);

        if (!fileInfo.isReadable()) {
            qWarning() << "Skipping unreadable files: " << fileInfo.fileName();
        }

        QFile inputFile(fileInfo.filePath());

        if (!inputFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Failed to open input file: " << inputFile.fileName();

            continue;
        }

        QByteArray inputData = inputFile.readAll();
        inputFile.close();

        QByteArray outputData;

        for (int i = 0; i < inputData.size(); ++i) {
            outputData.append(inputData[i] ^ xorKey[i % xorKey.size()]);
        }

        QString outputFilePath = this->outputDirectory + QDir::separator() + fileInfo.fileName();

        if (this->overwriteOutputFiles) {
            int counter = 1;

            while (QFile::exists(outputFilePath)) {
                outputFilePath = this->outputDirectory + QDir::separator() + fileInfo.baseName()
                                 + QString("_%1.%2").arg(counter++).arg(fileInfo.suffix());
            }
        }

        QFile outputFile(outputFilePath);

        if (!outputFile.open(QIODevice::WriteOnly)) {
            qWarning() << "Failed to create file: " << outputFilePath;

            continue;
        }

        outputFile.write(outputData);
        outputFile.close();

        qDebug() << "File processed: " << fileInfo.fileName();

        if (deleteInputFiles) {
            if (!QFile::remove(fileInfo.filePath())) {
                qWarning() << "Failed to delete input file: " << fileInfo.fileName();
            }
        }
    }
}
