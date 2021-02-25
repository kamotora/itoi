#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "demonstration/Lab1.h"
#include "filter/FilterUtil.h"
#include "demonstration/Lab2.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Lab2().work();
    return 0;
}
