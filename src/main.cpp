#include <QApplication>
#include <QDesktopWidget>

#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;

  QRect screenGeometry = a.desktop()->screenGeometry();
  int x = (screenGeometry.width() - w.width()) / 2;
  int y = (screenGeometry.height() - w.height()) / 2;
  w.move(x, y);

  w.show();
  return a.exec();
}
