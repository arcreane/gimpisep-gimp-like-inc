//
// Created by Hugues Baratgin on 16/06/2021.
//

#ifndef BETTERTHANGIMP_BRUSH_H
#define BETTERTHANGIMP_BRUSH_H


#include "../Manipulation.h"

class Brush : public Manipulation {
public:
    Brush(Workspace &);

    cv::Mat applyManipulation();

private:
    Point coordinates;
    int brushSize;
    int red;
    int green;
    int blue;

    Mat draw(Mat &, Point, int, Scalar);


};


#endif //BETTERTHANGIMP_BRUSH_H
