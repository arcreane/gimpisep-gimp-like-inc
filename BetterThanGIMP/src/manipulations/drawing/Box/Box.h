//
// Created by yakiimo on 6/17/21.
//

#ifndef BETTERTHANGIMP_BOX_H
#define BETTERTHANGIMP_BOX_H

#include "../Drawing.h"

class Box : public Drawing {
public:
    Box(Workspace &);

    Mat applyManipulation() override;

private:
    cv::Point startCorner;
};


#endif //BETTERTHANGIMP_BOX_H
