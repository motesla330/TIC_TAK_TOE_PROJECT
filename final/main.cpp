// Copyright 2025 <MahmoudIsmail>

#include <QApplication>
#include "final/login.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Login loginWindow;
  loginWindow.show();

  return app.exec();
}
