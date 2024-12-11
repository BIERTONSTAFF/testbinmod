#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QDir>
#include <QDebug>

class FileProcessor : public QObject
{
    Q_OBJECT

private:
    QString inputMask;
    QString outputDirectory;
    bool deleteInputFiles;
    bool overwriteOutputFiles;
    bool runOnce;
    QByteArray xorKey;
    int checkInterval;
    QTimer *timer;

public:
    FileProcessor(
        const QString &inputMask,
        const QString &outputPath,
        bool deleteInputFiles,
        bool overwriteOutputFiles,
        bool runOnce,
        const QByteArray &xorKey,
        int checkInterval,
        QObject *parent = nullptr
    );

    void start();

private slots:
    void processFiles();
};

#endif // FILEPROCESSOR_H
