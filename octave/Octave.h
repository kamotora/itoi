#ifndef ITOI_OCTAVE_H
#define ITOI_OCTAVE_H


#include "Element.h"
#include "vector"

class Octave {
private:
    vector<shared_ptr<Element>> elements;
public:
    [[nodiscard]]
    vector<shared_ptr<Element>> get_elements() const;

    void add_element(const shared_ptr<Element> &element);

    shared_ptr<Element> getLast();
};


#endif //ITOI_OCTAVE_H
