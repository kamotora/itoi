#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "demonstration/Lab1.h"
#include "filter/FilterUtil.h"
#include "demonstration/Lab2.h"
#include "demonstration/Lab3.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Lab3::demo();
    return 0;
}
