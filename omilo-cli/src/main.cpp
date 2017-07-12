#include <QtCore/QCoreApplication>
#include "downloadmanager.h"
#include "postprocessor.h"

#define KalFestival "KalFestival"
#define AwbCmuFestival "AwbCmuFestival"
#define BdlCmuFestival "BdlCmuFestival"
#define ClbCmuFestival "ClbCmuFestival"
#define JmkCmuFestival "JmkCmuFestival"
#define KspCmuFestival "KspCmuFestival"
#define RmsCmuFestival "RmsCmuFestival"
#define SltCmuFestival "SltCmuFestival"
#define RmsFlite "RmsFlite"
#define SltFlite "SltFlite"
#define AwbFlite "AwbFlite"
#define Kal16Flite "Kal16Flite"
#define ItalianMary "MaryItalian"
#define GermanMary "MaryGerman"
#define TurkishMary "MaryTurkish"
#define GreekMary "MaryGreek"
#define GreekGoogleMary "GoogleMaryGreek"
#define GreekHerculesMary "HerculesGreek"
#define FrenchMary "MaryFrench"
#define CmuRmsMary "MaryCmuRms"
#define CmuSltMary "MaryCmuSlt"
#define ObadiahMary "MaryObadiah"
#define PoppyMary "MaryPoppy"
#define PrudenceMary "MaryPrudence"
#define SpikeMary "MarySpike"
#define CoriMary "MaryCori"

void festivalSpeak(QString text, QString voiceCommand)
{
    QString textFile = "/tmp/omiloCli.txt";
    QFile outputFile(textFile);
    outputFile.open(QIODevice::WriteOnly);
    QTextStream outStream(&outputFile);
    outStream << text;
    outputFile.close();

    QString wavFile = "/tmp/omilo.wav";
    QString command = "/usr/share/omilo-screen-reader/festival/bin/text2wave -o " + wavFile + " " + textFile + voiceCommand;
    int result = system(command.toLocal8Bit());
    exit(result);
}

void fliteSpeak(QString text, QString voiceCommand)
{
    QString textFile = "/tmp/omiloCli.txt";
    QString wavFile = "/tmp/omilo.wav";
    QFile outputFile(textFile);
    outputFile.open(QIODevice::WriteOnly);
    QTextStream outStream(&outputFile);
    outStream << text;
    outputFile.close();
    QString command="flite " + voiceCommand + " -f " + textFile + " -o " + wavFile;
    int result = system(command.toLocal8Bit());
    exit(result);
}

void espeak(QString text, QString voiceCommand)
{
    QString textFile = "/tmp/omiloCli.txt";
    QString wavFile = "/tmp/omilo.wav";
    QString command;
    QFile outputFile(textFile);
    outputFile.open(QIODevice::WriteOnly);
    QTextStream outStream(&outputFile);
    outStream << text;
    outputFile.close();
    if ( voiceCommand == "")
    {
        command="espeak " + voiceCommand + " -f " + textFile + " -w " + wavFile;
    }
    else
    {
        command="espeak -v " + voiceCommand + " -f " + textFile + " -w " + wavFile;
    }

    int result = system(command.toLocal8Bit());
    exit(result);
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString inputText;
    QString voiceCommand;
    QString speed;
    QString tempo;

    for (int i = 1; i < argc; i++)
        inputText = inputText + QString::fromLocal8Bit(argv[i]) + " ";

    DownloadManager downloadManager;
    PostProcessor postProcessor;
    QString voice = "";
    QFile file("/tmp/omiloParameters.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString inText = in.readLine();
        QStringList inList = inText.split(" ");
        voice = inList[0];
        if (inList.size() > 2)
        {
            speed = inList[1];
            tempo = inList[2];
        }
    }
    file.close();

    if (voice == GreekMary)
        voiceCommand = "LOCALE=el&VOICE=emily-v2.0.1-hmm";
    else if (voice == GreekGoogleMary)
        voiceCommand = "LOCALE=el&VOICE=google-10";
    else if (voice == GreekHerculesMary)
        voiceCommand = "LOCALE=el&VOICE=alchemist-1992-hsmm-hsmm";
    else if (voice == ItalianMary)
        voiceCommand = "LOCALE=it&VOICE=istc-lucia-hsmm";
    else if (voice == GermanMary)
        voiceCommand = "LOCALE=de&VOICE=dfki-pavoque-neutral-hsmm";
    else if (voice == TurkishMary)
        voiceCommand = "LOCALE=tr&VOICE=dfki-ot-hsmm";
    else if (voice == FrenchMary)
        voiceCommand = "LOCALE=fr&VOICE=enst-dennys-hsmm";
    else if (voice == CmuRmsMary)
        voiceCommand = "LOCALE=en_US&VOICE=cmu-rms-hsmm";
    else if (voice == CmuSltMary)
        voiceCommand = "LOCALE=en_US&VOICE=cmu-slt-hsmm";
    else if (voice == ObadiahMary)
        voiceCommand = "LOCALE=en_US&VOICE=dfki-obadiah-hsmm";
    else if (voice == PoppyMary)
        voiceCommand = "LOCALE=en_US&VOICE=dfki-poppy-hsmm";
    else if (voice == PrudenceMary)
        voiceCommand = "LOCALE=en_US&VOICE=dfki-prudence-hsmm";
    else if (voice == SpikeMary)
        voiceCommand = "LOCALE=en_US&VOICE=dfki-spike-hsmm";
    else if (voice == CoriMary)
        voiceCommand = "LOCALE=en_US&VOICE=cori-2740-hsmm";
    else if (voice == KalFestival)
    {
        voiceCommand = "";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == AwbCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_awb_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == BdlCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_bdl_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == ClbCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_clb_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == JmkCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_jmk_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == KspCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_ksp_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == RmsCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_rms_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == SltCmuFestival)
    {
        voiceCommand = " -eval \"(voice_cmu_us_slt_arctic_clunits)\"";
        festivalSpeak(inputText, voiceCommand);
    }
    else if (voice == RmsFlite)
    {
        voiceCommand = "-voice rms";
        fliteSpeak(inputText, voiceCommand);
    }
    else if (voice == SltFlite)
    {
        voiceCommand = "-voice slt";
        fliteSpeak(inputText, voiceCommand);
    }
    else if (voice == AwbFlite)
    {
        voiceCommand = "-voice awb";
        fliteSpeak(inputText, voiceCommand);
    }
    else if (voice == Kal16Flite)
    {
        voiceCommand = "-voice kal16";
        fliteSpeak(inputText, voiceCommand);
    }
    //else
    //default value
    //    voiceCommand = "LOCALE=el&VOICE=emily-v2.0.1-hmm";
    if ( voice != "")
    {

        //QObject::connect(&downloadManager, SIGNAL(finished()), &app, SLOT(quit()));
        postProcessor.speed = speed;
        postProcessor.tempo = tempo;
        QObject::connect(&downloadManager, SIGNAL(finished()), &postProcessor, SLOT(postProcess()));
        QObject::connect(&postProcessor, SIGNAL(finished()), &app, SLOT(quit()));
        downloadManager.performMaryTTSSpeak(inputText, voiceCommand);
        app.exec();
    }
    else
    {
        QString systemLanguage = QLocale::languageToString(QLocale::system().language());
        if (systemLanguage == QLocale::languageToString(QLocale::Greek))
            voiceCommand = "el";
        else
            voiceCommand = "";
        espeak(inputText, voiceCommand);
    }
}
