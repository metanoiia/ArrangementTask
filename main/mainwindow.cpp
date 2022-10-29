#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_inDataMngr = new InputDataManager;
    m_inDataMngr->openInputFile();
    m_inDataMngr->checkFileFormatting();
    m_inDataMngr->closeInputFile();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_inDataMngr;
}

InputDataManager * MainWindow::getInDataMngr()
{
    return m_inDataMngr;
}
