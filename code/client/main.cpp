#include <QApplication>
#include "Client.h"

int main(int argc, char **argv) {
  QApplication app(argc, argv);
  Client c;
  c.show();
  app.exec();
  return 0;
}
