#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include "common/Filter.h"
#include "test/Lab2.h"
#include "test/Lab3.h"
#include "test/Lab4.h"
#include "test/Lab5.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Lab2::test();
    Lab3::test();
    Lab4::test();
    Lab5::test();
    return 0;
}
