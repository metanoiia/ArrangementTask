#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow( QWidget *parent ):
    QWidget( parent ),
    m_height( 700 ),
    m_width( 1200 )
{
    m_inDataMngr = new InputDataManager;

    m_view = new GraphicsView( this );
    m_scene = new QGraphicsScene( this );

    setGeometry(0, 0, m_width, m_height);

    m_view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_view->setScene( m_scene );

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

    disableBtns();

    connect( m_readFileBtn, &QPushButton::clicked, this, &MainWindow::onReadBtnClicked );
    connect( m_exitBtn, &QPushButton::clicked, this, &MainWindow::onExitBtnClicked );
    connect( m_resetBtn, &QPushButton::clicked, this, &MainWindow::onResetBtnClicked );
}

void MainWindow::disableBtns()
{
    m_calculateBtn->setEnabled( false );
    m_resetBtn->setEnabled( false );
}

void MainWindow::enableBtns()
{
    m_calculateBtn->setEnabled( true );
    m_resetBtn->setEnabled( true );
}

void MainWindow::onReadBtnClicked()
{
    m_scene->clear();

    m_inDataMngr->openInputFile();
    if( !m_inDataMngr->checkFileFormatting() )
    {
        m_calculateBtn->setEnabled( false );

        m_inDataMngr->resetData();

        QMessageBox::critical( this, tr( "Input error" ),
                               tr( "Errors found in input file.\n"
                                   "Please check log file"),
                               QMessageBox::Ok,
                               QMessageBox::Ok );

    }
    else
    {
        for( Cell * cell : m_inDataMngr->getGrid() )
        {
            m_scene->addItem( new CellItem( *cell ) );
        }

        m_scene->setSceneRect( m_inDataMngr->getX0Grid(),
                               m_inDataMngr->getY0Grid(),
                               m_inDataMngr->getXMaxGrid(),
                               m_inDataMngr->getYMaxGrid() );

        qDebug() << "sceneRect" << m_scene->sceneRect();

        m_view->fitInView( m_scene->sceneRect(), Qt::KeepAspectRatio );
    }

    m_inDataMngr->closeInputFile();

    enableBtns();
}

void MainWindow::onResetBtnClicked()
{
    QMessageBox msgBox;

    msgBox.setText( "All displayed information will be deleted" );
    msgBox.setInformativeText( "Are you sure you want to clear scene?" );
    msgBox.setStandardButtons( QMessageBox::Yes | QMessageBox::No );
    msgBox.setDefaultButton( QMessageBox::No );
    msgBox.setIcon( QMessageBox::Warning );
    msgBox.setStyleSheet("QLabel{min-width: 500px;}");

    if( msgBox.exec() == QMessageBox::Yes )
    {
        m_scene->clear();
        disableBtns();
    }
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
