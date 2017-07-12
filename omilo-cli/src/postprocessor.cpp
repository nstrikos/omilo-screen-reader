#include "postprocessor.h"
#include <QDebug>

PostProcessor::PostProcessor(QObject *parent) : QObject(parent)
{
    connect (&process, SIGNAL(finished(int)), this, SIGNAL(finished()));

}

void PostProcessor::postProcess()
{
    QString command = "sox /tmp/omilo-temp.wav /tmp/omilo.wav speed " + speed + " tempo " + tempo;
    process.start(command);
}


