#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QTextStream>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>

class DownloadManager : public QObject
{
    Q_OBJECT

public:
    DownloadManager();
    void performMaryTTSSpeak(QString text, QString voiceCommand);


private:
    void startRequest(QUrl url);
    void finishRequest();
    QFile *file;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    bool httpRequestAborted;
    QString filename;

private slots:
    void httpFinished();
    void httpReadyRead();

signals:
    void finished();
};

#endif // DOWNLOADMANAGER_H
