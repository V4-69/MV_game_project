#pragma once

#include <QPushButton>
#include <QMessageBox>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include "game_window.hpp"
#include "settings_window.hpp"
#include <QSurfaceFormat>


class MyMainWindow: public QMainWindow
{
  Q_OBJECT

public:
  MyMainWindow(){}
  ~MyMainWindow(){}

  void decorate()
  {
    QPushButton *button = new QPushButton(this);
    QPushButton *button2 = new QPushButton(this);

    button->setText("Играть1");
    button2->setText("Настроечки");

    QObject::connect(button, SIGNAL(clicked()),this, SLOT(GameWindowSlot()));
    QObject::connect(button2, SIGNAL(clicked()),this, SLOT(SettingsSlot()));

    button->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    button2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QHBoxLayout* layout = new QHBoxLayout(centralWidget);

    layout->addWidget(button);
    layout->addWidget(button2);

    setCentralWidget(centralWidget);
    setWindowTitle("Pushbutton Clicked Signal Test");
    show();
  }

public slots:
  int GameWindowSlot()
  {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);
    GameWindow  *gw = new GameWindow;
    gw->show();
  }
  void SettingsSlot()
  {
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(format);
    SettingsWindow *sw = new SettingsWindow;
    sw->show();
  }
};

