#ifndef ITOI_OCTAVE_H
#define ITOI_OCTAVE_H


#include "OctaveElement.h"
#include "vector"

class Octave {
private:
    vector<OctaveElement> elements;
public:
    vector<OctaveElement> getElements() const;
    void addElement(OctaveElement element);
    OctaveElement& getLast();
};


#endif //ITOI_OCTAVE_H
