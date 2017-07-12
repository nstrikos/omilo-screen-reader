#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include <QObject>
#include <QProcess>

class PostProcessor : public QObject
{
    Q_OBJECT
public:
    explicit PostProcessor(QObject *parent = nullptr);
    QString tempo;
    QString speed;

private:
    QProcess process;

signals:
    void finished();

public slots:
    void postProcess();
};

#endif // POSTPROCESSOR_H
