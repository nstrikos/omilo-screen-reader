#include "downloadmanager.h"
#include <QtNetwork/QNetworkAccessManager>

DownloadManager::DownloadManager()
{
    reply = NULL;
}

void DownloadManager::performMaryTTSSpeak(QString text, QString voiceCommand)
{
    filename = "/tmp/omilo-temp.wav";
    QString finalCommand = "http://localhost:59126/process?INPUT_TEXT=";

    //MaryTTS
    QString command1 = "&INPUT_TYPE=TEXT&OUTPUT_TYPE=AUDIO&AUDIO=AU_FILE&";
    QString command2 = voiceCommand;
    finalCommand = finalCommand + text + command1 + command2;

//    Google
//    text = text.left(100);
//    finalCommand = "http://translate.google.com/translate_tts?ie=UTF-8&tl=en&q=" + text;

    file = new QFile(filename);
    if (!this->file->open(QIODevice::WriteOnly))
    {
        delete this->file;
        this->file = 0;
        return;
    }
    // schedule the request
    httpRequestAborted = false;
    startRequest(finalCommand);
}

void DownloadManager::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()),  this, SLOT(httpFinished()));
    connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));
}

void DownloadManager::httpFinished()
{
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        reply->deleteLater();
        reply = NULL;
        return;
    }
    file->flush();
    file->close();

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
    finishRequest();
}

void DownloadManager::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}

void DownloadManager::finishRequest()
{
    emit finished();
}
