#include "mainwindow.h"
#include "ui_mainwindow.h"

const float SCALE_X = 0.75;
const float SCALE_Y = 0.75;

MainWindow::MainWindow( QWidget *parent ):
    QWidget( parent ),
    m_height( 700 ),
    m_width( 1200 )
{
    m_inDataMngr = new InputDataManager;

    m_view = new GraphicsView( this );
    m_scene = new QGraphicsScene( this );

    int sceneWidth = m_width * SCALE_X;
    int sceneHeight = m_height * SCALE_Y;

    m_view->setSceneRect( 0, 0, sceneWidth, sceneHeight );
    m_view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_view->setScene( m_scene );

    m_scene->addRect( m_view->sceneRect(),
                      QPen(Qt::black, 1, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin) ); //test

    m_scene->addEllipse( 300, 300, 30, 30 ); //test

    m_readFileBtn = new QPushButton( "Read from file" );
    m_resetBtn = new QPushButton("Reset");
    m_exitBtn = new QPushButton( "Exit" );
    m_calculateBtn = new QPushButton( "Calculate" );

    m_mainLayout = new QVBoxLayout;
    m_buttonLayout = new QHBoxLayout;

    m_buttonLayout->addWidget( m_readFileBtn );
    m_buttonLayout->addWidget( m_calculateBtn );
    m_buttonLayout->addWidget( m_resetBtn );
    m_buttonLayout->addWidget( m_exitBtn );

    m_mainLayout->addWidget( m_view );
    m_mainLayout->addItem( m_buttonLayout );

    setLayout( m_mainLayout );

    m_calculateBtn->setEnabled( false );

    connect( m_readFileBtn, &QPushButton::clicked, this, &MainWindow::onReadBtnClicked );
    connect( m_exitBtn, &QPushButton::clicked, this, &MainWindow::onExitBtnClicked );
}

void MainWindow::onReadBtnClicked()
{
    m_inDataMngr->openInputFile();
    if( !m_inDataMngr->checkFileFormatting() )
    {
        m_calculateBtn->setEnabled( false );

        QMessageBox::critical( this, tr( "Input error" ),
                               tr( "Errors found in input file.\n"
                                   "Please check log file"),
                               QMessageBox::Ok,
                               QMessageBox::Ok );
    }
    else
        m_calculateBtn->setEnabled( true );

    m_inDataMngr->closeInputFile();
}

void MainWindow::onExitBtnClicked()
{
    QCoreApplication::exit();
}

MainWindow::~MainWindow()
{
    delete m_inDataMngr;
}

InputDataManager * MainWindow::getInDataMngr()
{
    return m_inDataMngr;
}
