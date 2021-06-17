//
// Created by Hugues Baratgin on 12/06/2021.
//

#ifndef BETTERTHANGIMP_MONOCHROME_H
#define BETTERTHANGIMP_MONOCHROME_H


#include "../Manipulation.h"
#include "../../display/workspace/Workspace.h"

class Monochrome : public Manipulation {

public:
    Monochrome(Workspace &workspace);

    Mat applyManipulation();

private:
    ColorConversionCodes transform;
};


#endif //BETTERTHANGIMP_MONOCHROME_H
