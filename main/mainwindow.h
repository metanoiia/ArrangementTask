#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "inputDataManager/inputdatamanager.h"
#include "graphicsView/graphicsview.h"
#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include "graphicsItem/graphicsitem.h"


class MainWindow : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene * m_scene;
    GraphicsView * m_view;

    InputDataManager * m_inDataMngr;

    QHBoxLayout * m_buttonLayout;
    QVBoxLayout * m_mainLayout;

    QPushButton * m_readFileBtn;
    QPushButton * m_calculateBtn;
    QPushButton * m_resetBtn;
    QPushButton * m_exitBtn;

    int m_height;
    int m_width;

    void disableBtns();
    void enableBtns();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    InputDataManager * getInDataMngr();

public slots:

    void onReadBtnClicked();
    void onExitBtnClicked();
    void onResetBtnClicked();
};
#endif // MAINWINDOW_H
