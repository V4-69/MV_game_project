#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "gl_widget.hpp"
#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QMessageBox>
#include "gl_widget.hpp"
#include <QApplication>

typedef void (QWidget::*QWidgetVoidSlot)();

class GameWindow: public QMainWindow
{
  Q_OBJECT

  public:
    GameWindow();

private:
  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QOpenGLWidget * m_glWidget = nullptr;
};
