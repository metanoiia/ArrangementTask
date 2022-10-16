#ifndef INPUTDATAMANAGER_H
#define INPUTDATAMANAGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>
#include "target/target.h"

class InputDataManager : public QObject
{
    Q_OBJECT
private:
    QFile * m_file;

    float m_xMaxCoord;
    float m_yMaxCoord;

    float m_x0Coord;
    float m_y0Coord;

    QList < Target *> m_targets;

public:
    InputDataManager();
    ~InputDataManager();

    bool openInputFile();
    bool closeInputFile();
    bool checkFileFormatting();

    bool readTarg( QTextStream & in, unsigned int & num );
    bool readPads( QTextStream & in, unsigned int & num );
    bool readTube( QTextStream & in, unsigned int & num );
    bool readLimi( QTextStream & in, unsigned int & num );

    void checkTargetsCoords();
};

namespace KeyWords
{
    const QString TARG = "TARG";
    const QString PADS = "PADS";
    const QString TUBE = "TUBE";
    const QString LIMI = "LIMI";
    const QString PTL = "PTL";
    const QString END = "/";

    const int TARG_PARAM_CNT = 4;
    const int PADS_PARAM_CNT = 2;
    const int TUBE_PARAM_CNT = 1;
    const int LIMI_PARAM_CNT = 3;
}

#endif // INPUTDATAMANAGER_H
