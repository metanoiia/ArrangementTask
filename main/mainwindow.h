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
#include <QCheckBox>
#include <QTextEdit>
#include "logger/logger.h"
#include "graphicsItem/graphicsitem.h"

using GrTargetsVector = QVector < GraphicsItem <Target> * >;

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    enum Levels : uint8_t
    {
        ALERT,
        NOTIFY,
        INFO,
    };

    QGraphicsScene * m_scene;
    GraphicsView * m_view;

    InputDataManager * m_inDataMngr;

    QHBoxLayout * m_buttonLayout;
    QGridLayout * m_mainLayout;

    QPushButton * m_readFileBtn;
    QPushButton * m_calculateBtn;
    QPushButton * m_resetBtn;
    QPushButton * m_exitBtn;

    QCheckBox   * m_showRs;
    QTextEdit   * m_textEdit;

    GrTargetsVector m_GrTargets;

    int m_height;
    int m_width;

    void disableBtns();
    void enableBtns();
    void resetAll();
    void clearAndDisable();
    void appendMessage( QString msg, Levels level );

public:
    MainWindow( QWidget *parent = nullptr );
    ~MainWindow();

    InputDataManager * getInDataMngr();

public slots:
    void onReadBtnClicked();
    void onExitBtnClicked();
    void onResetBtnClicked();
    void onShowRsClicked( bool checked );
    void gotNewMsg( const QString & msg );
};
#endif // MAINWINDOW_H
