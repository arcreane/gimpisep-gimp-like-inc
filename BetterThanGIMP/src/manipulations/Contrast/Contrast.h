//￼
// Created by yakiimo on 6/17/21.
//

#ifndef BETTERTHANGIMP_CONTRAST_H
#define BETTERTHANGIMP_CONTRAST_H

#include "../Manipulation.h"
#include "../../display/workspace/Workspace.h"


class Contrast : public Manipulation {
public:
    Contrast(Workspace &workspace);
    Mat applyManipulation() override;

private:
    double contrastFactor;

};


#endif //BETTERTHANGIMP_CONTRAST_H
