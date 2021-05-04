#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "demonstration/Lab1.h"
#include "filter/FilterUtil.h"
#include "demonstration/Lab2.h"
#include "demonstration/Lab3.h"
#include "demonstration/Lab4.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    Lab2::demo();
//    Lab3::demo();
    Lab4::demo();
    return 0;
}
