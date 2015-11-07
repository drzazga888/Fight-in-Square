#include <QApplication>

#include "Server.h"
#include <string.h>
#include <iostream>

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Server server;
  server.show();
  app.exec();
  return 0;
}
