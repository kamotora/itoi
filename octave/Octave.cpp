//
// Created by kamotora on 25.02.2021.
//

#include "Octave.h"

vector<OctaveElement> Octave::getElements() const {
    return elements;
}

void Octave::addElement(OctaveElement element) {
    elements.push_back(element);
}

OctaveElement &Octave::getLast() {
    return elements.back();
}

