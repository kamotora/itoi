#ifndef ITOI_OCTAVE_H
#define ITOI_OCTAVE_H


#include "OctaveElement.h"
#include "vector"

class Octave {
private:
    vector<shared_ptr<OctaveElement>> elements;
public:
    [[nodiscard]] vector<shared_ptr<OctaveElement>> getElements() const;
    void addElement(const shared_ptr<OctaveElement>& element);
    shared_ptr<OctaveElement> getLast();
};


#endif //ITOI_OCTAVE_H
