#include "inputdatamanager.h"
#include <QDebug>
#include <QFileDialog>

InputDataManager::InputDataManager()
{
    m_file = new QFile;
}

bool InputDataManager::openInputFile()
{
    QString filePath = QFileDialog::getOpenFileName( nullptr, tr( "Open input data file" ),
                                  "", tr( "TXT files (*.txt)" ));
    if( !filePath.isNull() )
    {
        m_file->setFileName( filePath );
        m_file->open( QIODevice::ReadOnly );

        if( !m_file->isOpen() )
        {
            qCritical() << "Can't open input file";
            return false;
        }
    }
    return true;
}

bool InputDataManager::checkFileFormatting()
{
    bool allCorrect = true;

    if( !m_file->isOpen() )
    {
        qCritical() << "Input file is not opened!";
        return false;
    }

    QTextStream in( m_file );

    unsigned int lineNum = 0;

    while( !in.atEnd() )
    {
        QString line = in.readLine();
        lineNum++;

        if( line == KeyWords::TARG )
        {
            allCorrect &= readTarg( in, lineNum );
        }
        else if( line == KeyWords::PADS )
        {
            allCorrect &= readPads( in, lineNum );
        }
        else if( line == KeyWords::TUBE )
        {
            allCorrect &= readTube( in, lineNum );
        }
        else if( line == KeyWords::LIMI )
        {
            allCorrect &= readLimi( in, lineNum );
        }
        else
        {
            qCritical() << lineNum  << "Undefined parameter: " << line;
            allCorrect = false;
        }
    }

    checkTargetsCoords();

    return allCorrect;
}

/*reads input data file and checks its formatting,
  if everything is ok fills the list of targs (now not implemented)
*/
bool InputDataManager::readTarg( QTextStream & in, unsigned int & num )
{
   unsigned int localNum = 0; // used for lines in block TARG counting
   bool allCorrect = true;
   bool tarCorrect = true;

   QString line;

   while( !in.atEnd() )
   {
       tarCorrect = true;

       line = in.readLine();

       num++;
       localNum++;

       if( line == KeyWords::END )
       {
           if( localNum == 1 )
           {
               qCritical() << QString::number( num ) <<" [TARG]->empty TARG list";
               return false;
           }
           return allCorrect;
       }

       QStringList targParams = line.split( " ",  QString::SkipEmptyParts );


       if(  targParams.size() != KeyWords::TARG_PARAM_CNT )
       {
           qCritical() << num <<" [TARG]->TARG parameters count must be equal 4 according to input format: at line " << line;
           allCorrect = false;
           tarCorrect = false;
       }
       else
       {
           float x = targParams.at( 0 ).toFloat();
           float y = targParams.at( 1 ).toFloat();
           float radius = targParams.at( 2 ).toFloat();
           unsigned int price = targParams.at( 3 ).toFloat();

           if( radius <= 0.0 ) //if R <= 0
           {
               qCritical() << num << " [TARG]->invalid maximum radius at: " << line;
               allCorrect = false;
               tarCorrect = false;
           }
           if( price <= 0 ) // if one meter of drilling price <= 0
           {
               qCritical() << num << " [TARG]->invalid cost at: " << line;
               allCorrect = false;
               tarCorrect = false;
           }

           if( tarCorrect )
           {
               m_targets.append( new Target( x, y, radius, price, num ) );
           }
       }

   }

   return allCorrect;
}

/*reads input data file and checks its formatting,
  if everything is ok initializes pads obj (now not implemented)
*/
bool InputDataManager::readPads( QTextStream & in, unsigned int & num )
{
    bool allCorrect = true;
    unsigned int localNum = 0; // used for lines in block PADS counting

    QString line;

    while( !in.atEnd() )
    {
        line = in.readLine();

        num++;
        localNum++;

        if( localNum > 2 )
        {
             qCritical() << num << " [PADS]->only one pads parameter line is allowed: " << line;
             allCorrect = false;
        }

        if( line == KeyWords::END )
        {
            if( localNum < 2 )
            {
                 qCritical() << num << " [PADS]->there is no pads parameter line: " << line;
                 allCorrect = false;
            }

            return allCorrect;
        }

        QStringList padsParams = line.split( " ",  QString::SkipEmptyParts );

        if ( padsParams.size() != 2 )
        {
            qCritical() << num << " [PADS]->pads line must have two parameters: " << line;
            allCorrect = false;
        }

        if( padsParams.at( 0 ).toFloat() <= 0 )
        {
            qCritical() << num << " [PADS]->invalid maximum target count at: " << line;
            allCorrect =  false;
        }
        if( padsParams.at( 1 ).toFloat() <= 0 )
        {
            qCritical() << num << " [PADS]->invalid cost at: " << line;
            allCorrect =  false;
        }

        //(not implemented)
        //*if allCorrect still contains 'true' then init PADS object*
        //*else just continue checking others lines*
    }

    return allCorrect;
}

bool InputDataManager::readTube( QTextStream & in, unsigned int & num )
{
    bool allCorrect = true;
    unsigned int localNum = 0; // used for lines in block TUBE counting

    QString line;

    while( !in.atEnd() )
    {
        line = in.readLine();

        num++;
        localNum++;

        if( localNum > 2 )
        {
             qCritical() << num << " [TUBE]->only one tube parameter line is allowed: " << line;
             allCorrect = false;
        }

        if( line == KeyWords::END )
        {
            if( localNum < 2 )
            {
                 qCritical() << num << " [TUBE]->there is no tube parameter line: " << line;
                 allCorrect = false;
            }

            return allCorrect;
        }

        QStringList tubeParams = line.split( " ",  QString::SkipEmptyParts );

        if( tubeParams.size() != 1 )
        {
            qCritical() << num << " [TUBE]->must have 1 input parameter: " << line;
            allCorrect =  false;
        }

        if( tubeParams.at( 0 ).toFloat() <= 0 )
        {
            qCritical() << num << " [TUBE]->invalid cost at: " << line;
            allCorrect =  false;
        }

        //(not implemented)
        //*if allCorrect still contains 'true' then init TUBE object*
        //*else just continue checking others lines*
    }

    return allCorrect;
}

bool InputDataManager::readLimi( QTextStream & in, unsigned int & num )
{
    bool allCorrect = true;
    unsigned int localNum = 0; // used for lines in block TARG counting


    QString line = in.readLine();

    num++;
    localNum++;

    QStringList limiParams = line.split( " ", QString::SkipEmptyParts );

    if( limiParams.size() != 3 )
    {
        qCritical() << num << " [LIMI]->invalid parameters number: " << line;
        return  false;
    }

    unsigned int numX    = limiParams.at( 0 ).toInt();
    unsigned int numY    = limiParams.at( 1 ).toInt();
    unsigned int maxCost = limiParams.at( 2 ).toInt();

    float x, y = 0.0;
    unsigned int cost = 0;

    if( numX <= 0 )
    {
        qCritical() << num << " [LIMI]->X limits mist be greater than 0: " << line;
        return  false;
    }
    if( numY <= 0 )
    {
        qCritical() << num << " [LIMI]->Y limits mist be greater than 0: " << line;
        return  false;
    }
    if( maxCost <= 0 )
    {
        qCritical() << num << " [LIMI]->cost limits mist be greater than 0: " << line;
        return  false;
    }

    float dX = 0.0,        dY = 0.0;
    float x0 = 0.0,        y0 = 0.0;
    float xMax = 0.0,      yMax = 0.0;
    float xPrevious = 0.0, yPrevious = 0.0;

    unsigned int indX = 0, indY = 0;

    while( !in.atEnd() )
    {
        line = in.readLine();

        num++;
        localNum++;

        if( line == KeyWords::END )
        {
            unsigned int expNum = numX * numY;

            if( localNum - 2 != expNum )
            {
                qCritical() << endl << "Wrong [LIMI] points count received: expected "
                            << expNum << ", got " << localNum - 2
                            << ". Difference: " << qAbs(  expNum - localNum - 2 );

                allCorrect = false;
            }


            m_xMaxCoord = xMax;
            m_yMaxCoord = yMax;

            m_x0Coord = x0;
            m_y0Coord = y0;

            return allCorrect;
        }

        limiParams = line.split( " ",  QString::SkipEmptyParts );

        if( limiParams.size() != 3 )
        {
            qCritical() << num << " [LIMI]->invalid parameters number: " << line;
            allCorrect = false;
        }

        x = limiParams.at( 0 ).toFloat();
        y = limiParams.at( 1 ).toFloat();
        cost = limiParams.at( 2 ).toInt();

        if( cost <= 0 )
        {
            qCritical() << num << " [LIMI]->cost value must be greater than 0 : " << line;
            allCorrect = false;
        }

        if ( indX == 0 && indY == 0 ) // first pair of coordinates are taked as initial
        {
            x0 = x;
            y0 = y;
            xPrevious = x;
            yPrevious = y;

            indY++;
        }
        else
        {
            if( ( y == yPrevious ) && ( x == xPrevious ) ) //duplicate
            {
                qCritical() << num << " [LIMI]->got duplicated coordinates of previous cell: " << line;
                allCorrect = false;
            }

            else if( ( y == yPrevious ) && ( x != xPrevious ) ) // got something very strange
            {
                if( indY < numY )
                {
                    qCritical() << num << " [LIMI]->invalid X and Y: " << line;
                }
                else //got new column with invalid Y data or gor old column new row with invalid X Y data?
                {
                    qCritical() << num << " [LIMI]->missed point(s): "<< line;
                }
                allCorrect = false;
            }

            else if( ( y != yPrevious ) && ( x != xPrevious ) ) //new column new row?
            {
                if( x > xPrevious )
                {
                    if( indY < numY - 1) //cathed missed points from previous column
                    {
                        for( indY; indY < numY; indY++ )
                        {
                            qCritical() << num << " [LIMI]->missed one point. Expected : "<< x
                                        << " " << ( indY * dY + y0 ) << " " <<"int cost. Got: " << line;
                        }
                        allCorrect = false;
                    }

                    if( y != y0 )
                    {
                        qCritical() << num << " [LIMI]->missed one point. Expected : "<< x
                                    << " " << y0 << " " <<"int cost. Got: "<< line;
                        allCorrect = false;
                    }
                    indY = 0;
                    indX++;

                    if( dX == 0.0 )
                    {
                        dX = x - xPrevious;
                        xMax = x0 + dX * numX;
                        xPrevious = x;
                        yPrevious = y;

                    }
                    else
                    {
                        if( x - xPrevious != dX )
                        {
                            qCritical() << num << " [LIMI]->X coordinate recedes unevenly: " << line;
                            allCorrect = false;
                        }
                        else
                        {
                            xPrevious = x;
                            yPrevious = y;

                        }
                    }
                }
                else //incorrect x data
                {
                    qCritical() << num << " [LIMI]->X coordinate must be sorted in ascending order: " << line;
                    allCorrect = false;
                }

                if( indX >= numX )
                {
                    qCritical() << num << " [LIMI]->X coordinate out of range, number of raw greater than provided: " << line;
                    allCorrect = false;
                }
            }

            else if( ( y != yPrevious ) && ( x == xPrevious ) ) // old column new row?
            {
                if( y > yPrevious )
                {
                    if( dY == 0.0 )
                    {
                        dY = y - yPrevious;
                        yMax = y0 + dY * numY;
                        xPrevious = x;
                        yPrevious = y;
                    }
                    else
                    {
                        if( y - yPrevious != dY )
                        {
                            qCritical() << num << " [LIMI]->Y coordinate recedes unevenly: " << line;
                            allCorrect = false;
                        }
                        else
                        {
                            xPrevious = x;
                            yPrevious = y;
                        }
                    }
                }
                else
                {
                    qCritical() << num << " [LIMI]->Y coordinate must be sorted in ascending order: " << line;
                    allCorrect = false;
                }

                if( indY >= numY )
                {
                    qCritical() << num << " [LIMI]->Y coordinate out of range, number of raw greater than provided: " << line;
                    allCorrect = false;
                }

            }
            indY++;
        }

    }
    return allCorrect;
}

void InputDataManager::checkTargetsCoords()
{
    if( m_targets.empty() )
        return;

    for( Target * t : m_targets )
    {
        float tX = t->getX();
        float tY = t->getY();

        if( !( ( tX >= m_x0Coord ) && ( tX <= m_xMaxCoord )
         && ( tY >= m_y0Coord ) && ( tY <= m_yMaxCoord ) ) )
        {
            qCritical() << t->getlineNum() << " [LIMI] out of bounds. Limits: "
                        << "[" << m_x0Coord << ", " << m_y0Coord << "].  "
                        << "[" << m_xMaxCoord << ", " << m_yMaxCoord << "]"
                        << "Got: "
                        << "[" << tX << ", " << tY << "] ";
        }

        m_targets.removeOne( t );
    }
}

InputDataManager::~InputDataManager()
{
    delete m_file;
}



