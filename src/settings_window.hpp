#ifndef SETTINGS_WINDOW_HPP
#define SETTINGS_WINDOW_HPP
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
#include <QCheckBox>
#include "gl_widget.hpp"
#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>
typedef void (QWidget::*QWidgetVoidSlot)();

class SettingsWindow: public QMainWindow
{
  Q_OBJECT

public:
  SettingsWindow();

public slots:
  int set_difficulty(int data1);


};


#endif // GAME_WINDOW_H
