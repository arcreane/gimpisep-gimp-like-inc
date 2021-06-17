//
// Created by yakiimo on 6/17/21.
//

#ifndef BETTERTHANGIMP_BLUR_H
#define BETTERTHANGIMP_BLUR_H

#include "../Manipulation.h"

class Blur : public Manipulation {
public:
    Blur(Workspace &workspace);

    Mat applyManipulation();

private:
    int blurKernelSize;

    Mat blur(Mat& image, int blurKernelSize);


};


#endif //BETTERTHANGIMP_BLUR_H
