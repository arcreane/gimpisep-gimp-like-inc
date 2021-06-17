//
// Created by Hugues Baratgin on 12/06/2021.
//

#ifndef BETTERTHANGIMP_CANNYEDGE_H
#define BETTERTHANGIMP_CANNYEDGE_H


#include "../Manipulation.h"

class CannyEdge : public Manipulation {
public:
    CannyEdge(Workspace &workspace);

    Mat applyManipulation();

private:
    int threshold1;
    int threshold2;
    int kernelSize;

    Mat cannyEdge(Mat &image, int threshold1, int threshold2, int blurKernelSize);
};


#endif //BETTERTHANGIMP_CANNYEDGE_H
