#ifndef ITOI_FILTERUTIL_H
#define ITOI_FILTERUTIL_H

#include <ostream>
#include "DoubleImage.h"
#include <iomanip>
#include "iostream"
using namespace std;

class FilterUtil {

    static void print(ostream &out, DoubleImage &matrix);
};


#endif //ITOI_FILTERUTIL_H
