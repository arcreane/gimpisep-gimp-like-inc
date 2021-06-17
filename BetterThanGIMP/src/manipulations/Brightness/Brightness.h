#ifndef BETTERTHANGIMP_CANNYEDGE_H
#define BETTERTHANGIMP_CANNYEDGE_H


#include "../Manipulation.h"

class Brightness : public Manipulation {
public:
    Brightness(Workspace &workspace);
    Mat applyManipulation();

private:
    int percentChange;

    Mat Brightness(Mat &image, int percentChange);
};


#endif //BETTERTHANGIMP_CANNYEDGE_H
