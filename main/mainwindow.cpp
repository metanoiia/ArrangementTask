#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSizePolicy>
#include <QThread>


MainWindow::MainWindow( QWidget *parent ):
    QWidget( parent ),
    m_height( 700 ),
    m_width( 1200 )
{
    m_inDataMngr = new InputDataManager;

    m_view = new GraphicsView( this );
    m_scene = new QGraphicsScene( this );

    setGeometry( 0, 0, m_width, m_height );

    m_view->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_view->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    m_view->setScene( m_scene );
    m_view->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    m_readFileBtn = new QPushButton( "Read from file" );
    m_resetBtn = new QPushButton("Reset");
    m_exitBtn = new QPushButton( "Exit" );
    m_calculateBtn = new QPushButton( "Calculate" );

    m_textEdit = new QTextEdit;
    m_textEdit->setReadOnly( true );
    m_textEdit->setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Expanding );
    m_textEdit->setFont( QFont( "Courier New", 10 ) );

    m_showRs = new QCheckBox( "Show radii" );

    m_mainLayout = new QGridLayout;
    m_buttonLayout = new QHBoxLayout;

    m_buttonLayout->addWidget( m_readFileBtn );
    m_buttonLayout->addWidget( m_calculateBtn );
    m_buttonLayout->addWidget( m_resetBtn );
    m_buttonLayout->addWidget( m_exitBtn );

    m_mainLayout->addWidget( m_view, 0, 0, 4, 6 );
    m_mainLayout->addWidget( m_showRs, 0, 6, 1, 2 );
    m_mainLayout->addWidget( m_textEdit, 1, 6, 3, 2 );
    m_mainLayout->addItem( m_buttonLayout, 4, 0, 1, 8 );

    setLayout( m_mainLayout );

    disableBtns();

    connect( m_readFileBtn, &QPushButton::clicked, this, &MainWindow::onReadBtnClicked );
    connect( m_exitBtn, &QPushButton::clicked, this, &MainWindow::onExitBtnClicked );
    connect( m_resetBtn, &QPushButton::clicked, this, &MainWindow::onResetBtnClicked );
    connect( m_showRs, &QCheckBox::clicked, this, &MainWindow::onShowRsClicked );
    connect( m_inDataMngr, &InputDataManager::newMsg, this, &MainWindow::gotNewMsg );
}

void MainWindow::disableBtns()
{
    m_showRs->setEnabled( false );
    m_calculateBtn->setEnabled( false );
    m_resetBtn->setEnabled( false );
}

void MainWindow::enableBtns()
{
    m_showRs->setEnabled( true );
    m_calculateBtn->setEnabled( true );
    m_resetBtn->setEnabled( true );
}

void MainWindow::gotNewMsg( const QString & msg ) { m_textEdit->append( msg + '\n' ); }

//do not call it to append big amount of text because insertHtml is slowest PoS
void MainWindow::appendMessage( QString msg, Levels level )
{
    QTextCursor cursor = m_textEdit->textCursor();
    static QString alertHtml = "<font color=\"DarkRed\">";
    static QString infoHtml = "<font color=\"ForestGreen\">";
    static QString notifyHtml = "<font color=\"SteelBlue\">";
    static QString endHtml = "</font><br>";

    switch( level )
    {
        case ALERT: msg = alertHtml + msg; break;
        case NOTIFY: msg = notifyHtml + msg; break;
        case INFO: msg = infoHtml + msg; break;
        default: msg = infoHtml + msg; break;
    }

    msg = msg + endHtml;
    m_textEdit->insertHtml( msg );
    cursor.movePosition( QTextCursor::End );
    m_textEdit->setTextCursor( cursor );
}

void MainWindow::onReadBtnClicked()
{
    m_inDataMngr->openInputFile();

    m_textEdit->clear();

    if( !m_inDataMngr->checkFileFormatting() )
    {
        m_calculateBtn->setEnabled( false );

        m_inDataMngr->resetData();

        clearAndDisable();

        QMessageBox::critical( this, tr( "Input error" ),
                               tr( "Errors found in input file.\n"
                                   "Please check log file"),
                               QMessageBox::Ok,
                               QMessageBox::Ok );

        appendMessage( "Errors found in input file!", ALERT );
    }
    else
    {
        m_scene->clear();

        disableBtns();
        m_GrTargets.clear();

        for( Cell * cell : m_inDataMngr->getGrid() )
            m_scene->addItem( new GraphicsItem < Cell >( *cell ) );

        m_scene->setSceneRect( m_inDataMngr->getX0Grid(),
                               m_inDataMngr->getY0Grid(),
                               m_inDataMngr->getXMaxGrid(),
                               m_inDataMngr->getYMaxGrid() );

        float cellW = m_inDataMngr->getGrid().at( 0 )->getWidth();
        float cellH = m_inDataMngr->getGrid().at( 0 )->getHeight();

        for( Target * target : m_inDataMngr->getTargets() )
        {
            GraphicsItem < Target > * gr_target = new GraphicsItem < Target >( *target, cellW, cellH );
            m_scene->addItem( gr_target );
            m_GrTargets.push_back( gr_target );
        }

        qDebug() << "sceneRect" << m_scene->sceneRect();

        m_view->fitInView( m_scene->sceneRect(), Qt::KeepAspectRatio );

        appendMessage( "File read successfully!", INFO );

        enableBtns();
    }

    m_inDataMngr->closeInputFile();
}

void MainWindow::resetAll()
{
    m_scene->clear();
    m_showRs->setChecked( false );
    m_textEdit->clear();
    disableBtns();
    m_GrTargets.clear();
}

void MainWindow::clearAndDisable()
{
    m_scene->clear();
    m_showRs->setChecked( false );
    disableBtns();
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
        resetAll();
}

void MainWindow::onExitBtnClicked()
{
    QCoreApplication::exit();
}

void MainWindow::onShowRsClicked( bool checked )
{
    for( GraphicsItem <Target> * item : m_GrTargets )
    {
        item->showR( checked );
        item->update();
    }
}

MainWindow::~MainWindow()
{
    delete m_inDataMngr;
}

InputDataManager * MainWindow::getInDataMngr()
{
    return m_inDataMngr;
}
