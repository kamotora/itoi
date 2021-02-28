//
// Created by kamotora on 25.02.2021.
//

#include "Octave.h"

vector<shared_ptr<OctaveElement>> Octave::getElements() const {
    return elements;
}

void Octave::addElement(const shared_ptr<OctaveElement>& element) {
    elements.push_back(element);
}

shared_ptr<OctaveElement> Octave::getLast() {
    return elements.back();
}

