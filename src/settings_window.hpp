#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "gl_widget.hpp"
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QWidget>
#include <json/json.h>
#include <json/writer.h>
#include <fstream>
#include <iostream>
#include <QHBoxLayout>
typedef void (QWidget::*QWidgetVoidSlot)();

class SettingsWindow: public QMainWindow
{
  Q_OBJECT


public:
  SettingsWindow();
private:
  QComboBox * comboBoxDifficulty;
  QWidget * centralWidget;
  QCheckBox * checkIsObstacles;
  QCheckBox * checkMovableAliens;
  QCheckBox * checkSound;
Q_SIGNALS:
public slots:
  void WriteJson();
  void ReadJson();
  int setDifficulty(int m_difficulty);

};
