//
// Created by yakiimo on 6/17/21.
//

#ifndef BETTERTHANGIMP_EROSION_H
#define BETTERTHANGIMP_EROSION_H


#include "../Manipulation.h"
#include "../../display/workspace/Workspace.h"

class Erosion : public Manipulation {
public:
    Erosion(Workspace &workspace);

    Mat applyManipulation();

private:
    int inputSize;
    int inputKernel;
};


#endif //BETTERTHANGIMP_EROSION_H
