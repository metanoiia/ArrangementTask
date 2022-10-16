#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "inputDataManager/inputdatamanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow * ui;

    InputDataManager * m_inDataMngr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    InputDataManager * getInDataMngr();


};
#endif // MAINWINDOW_H
