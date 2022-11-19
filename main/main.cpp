#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include "mainwindow.h"
#include <QDebug>

QScopedPointer < QFile > logFile;

void messageHandler( QtMsgType type, const QMessageLogContext & context, const QString & msg )
{
    Q_UNUSED(context);

    QTextStream out( logFile.data() );

    out << msg << ": ";

    switch ( type )
    {
    case QtInfoMsg:     out << "INFO "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRITICAL "; break;
    case QtFatalMsg:    out << "FATAL "; break;
    }

    out << endl;
    out.flush();
}

int main(int argc, char *argv[])
{
    logFile.reset( new QFile( QDir::currentPath() + "/logFile.log" ) );

    logFile.data()->open( QFile::WriteOnly | QFile::Text );

    qInstallMessageHandler( messageHandler );

    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
