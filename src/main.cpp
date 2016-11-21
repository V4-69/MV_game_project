#pragma once
#include <QApplication>
#include <QMainWindow>
#include <QSurfaceFormat>
#include "main_window.hpp"
#include "def_set_cus_set.hpp"


int main(int argc, char ** argv)
{
  QApplication app(argc, argv);
  MyMainWindow window;
  window.setWindowTitle(QString::fromUtf8("MainWindow"));
  window.decorate();
  return app.exec();
}


