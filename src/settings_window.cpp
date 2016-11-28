#pragma once
#include "settings_window.hpp"

#include <fstream>
//#include "C:\Users\Max\Desktop\template-window_demo\template-window_demo\3party\pugixml\src\pugixml.hpp"
typedef void (QWidget::*QWidgetVoidSlot)();

SettingsWindow::SettingsWindow()
{
  centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);
  checkIsObstacles = new QCheckBox("Препятсвия");
  checkMovableAliens = new QCheckBox("Инопланетяне движутся");
  checkSound = new QCheckBox("Звук");
  QGridLayout * layout = new QGridLayout(centralWidget);

  comboBoxDifficulty = new QComboBox(this);
  comboBoxDifficulty->addItem("Легко", 1);
  comboBoxDifficulty->addItem("Средне", 2);
  comboBoxDifficulty->addItem("Сложно", 3);
  comboBoxDifficulty->setCurrentIndex(1);
  connect(comboBoxDifficulty, SIGNAL(activated(int)), this, SLOT(setDifficulty(int)));

  QPushButton *cancel =new QPushButton("Отмена");
  QPushButton *def = new QPushButton("Вернуть состояние");
  QPushButton *save =new QPushButton("Сохранить состояние");
  connect(save,SIGNAL(clicked()),this,SLOT(WriteJson()));
  connect(def,SIGNAL(clicked()),this,SLOT(ReadJson()));

  QWidget *bottom_widget = new QWidget(this);
  QHBoxLayout *bottom = new QHBoxLayout(bottom_widget);
  bottom->addWidget(cancel);
  bottom->addWidget(def);
  bottom->addWidget(save);

  layout->addWidget(comboBoxDifficulty,0,0);
  layout->addWidget(checkIsObstacles,0,1);
  layout->addWidget(checkMovableAliens,1,1);
  layout->addWidget(checkSound,2,1);
  layout->addWidget(bottom_widget,3,0);


  setFocusPolicy(Qt::StrongFocus);
  show();
  ReadJson();
}

SettingsWindow::setDifficulty(int m_difficulty)
{
  //здесь будет код
}

void SettingsWindow::WriteJson()
{
  Json::Value settings;

  auto & root = settings["settings"];
  root["difficulty"] = comboBoxDifficulty->currentIndex();
  root["is_obstacles"] = checkIsObstacles->isChecked();
  root["movable_aliens"] = checkMovableAliens->isChecked();
  root["sound"] = checkSound->isChecked();

  std::ofstream settingsFile;
  settingsFile.open("settings.json");
  if (settingsFile.is_open())
  {
    Json::StyledWriter styledWriter;
    settingsFile << styledWriter.write(settings);
    settingsFile.close();
  }
}
void SettingsWindow::ReadJson()
{
  Json::Value settings;
  std::ifstream file("settings.json");
  if (file.is_open())
  {
    file >> settings;
    file.close();
  }
  comboBoxDifficulty->setCurrentIndex(settings["settings"]["difficulty"].asInt());
  if (settings["settings"]["is_obstacles"].asBool())
      checkIsObstacles->setCheckState(Qt::Checked);
  else
      checkIsObstacles->setCheckState(Qt::Unchecked);
  if (settings["settings"]["movable_aliens"].asBool())
      checkMovableAliens->setCheckState(Qt::Checked);
  else
      checkMovableAliens->setCheckState(Qt::Unchecked);
  if (settings["settings"]["sound"].asBool())
      checkSound->setCheckState(Qt::Checked);
  else
      checkSound->setCheckState(Qt::Unchecked);
}

