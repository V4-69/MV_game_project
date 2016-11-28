#include "game_window.hpp"
#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QMessageBox>
#include "gl_widget.hpp"
#include <QApplication>

typedef void (QWidget::*QWidgetVoidSlot)();

GameWindow::GameWindow()
{
  m_glWidget = new GLWidget(this, qRgb(255, 255, 255));
  m_timer = new QTimer(this);
  m_timer->setInterval(10);
  setCentralWidget(m_glWidget);
  connect(m_timer, &QTimer::timeout, m_glWidget, static_cast<QWidgetVoidSlot>(&QWidget::update));
  m_timer->start();
  setFocusPolicy(Qt::StrongFocus);
  show();
}
