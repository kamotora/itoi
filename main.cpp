#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "demonstration/Lab1.h"
#include "filter/FilterUtil.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Lab1::work();
    return 0;
}
