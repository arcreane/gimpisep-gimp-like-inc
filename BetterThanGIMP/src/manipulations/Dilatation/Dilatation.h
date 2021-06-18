//
// Created by yakiimo on 6/17/21.
//

#ifndef BETTERTHANGIMP_DILATATION_H
#define BETTERTHANGIMP_DILATATION_H


#include "../Manipulation.h"
#include "../../display/workspace/Workspace.h"

class Dilatation : public Manipulation {
public:
    Dilatation(Workspace &workspace);

    Mat applyManipulation();

private:
    int inputSize;
    int inputKernel;
};



#endif //BETTERTHANGIMP_DILATATION_H
