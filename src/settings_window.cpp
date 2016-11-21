#pragma once
#include "settings_window.hpp"
#include <QMainWindow>
#include <QTimer>
#include <QGridLayout>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QMessageBox>
#include "gl_widget.hpp"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QComboBox>
typedef void (QWidget::*QWidgetVoidSlot)();

SettingsWindow::SettingsWindow()
{
  QWidget * centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  QCheckBox *check1 = new QCheckBox("Пули-Шмули");
  QCheckBox *check2 = new QCheckBox("Питер");
  QCheckBox *check3 = new QCheckBox("VR");
  QGridLayout * layout = new QGridLayout(centralWidget);

  QComboBox * comboBox = new QComboBox(this);
  comboBox->addItem("Легко", 1);
  comboBox->addItem("Средне", 2);
  comboBox->addItem("Сложно", 3);
  comboBox->setCurrentIndex(1);
  connect(comboBox, SIGNAL(activated(int)), this, SLOT(set_difficulty(int)));

  QPushButton *cancel =new QPushButton("Отмена");
  QPushButton *def = new QPushButton("Вернуть стандартные");
  QPushButton *save =new QPushButton("Сохранить");

  QWidget *bottom_widget = new QWidget(this);
  QHBoxLayout *bottom = new QHBoxLayout(bottom_widget);
  bottom->addWidget(cancel);
  bottom->addWidget(def);
  bottom->addWidget(save);

  layout->addWidget(comboBox,0,0);
  layout->addWidget(check1,0,1);
  layout->addWidget(check2,1,1);
  layout->addWidget(check3,2,1);
  layout->addWidget(bottom_widget,3,0);


  setFocusPolicy(Qt::StrongFocus);
  show();
}

SettingsWindow::set_difficulty(int data1)
{
  QMessageBox msgBox;
  msgBox.setWindowTitle("Hello");
  if(data1 == 0)
  msgBox.setText("0");
  if(data1 == 1)
  msgBox.setText("1");
  if(data1 == 2)
  msgBox.setText("2");
  msgBox.resize(500,500);
  msgBox.exec();
}
