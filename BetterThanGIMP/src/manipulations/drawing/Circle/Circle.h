//
// Created by Hugues Baratgin on 17/06/2021.
//

#ifndef BETTERTHANGIMP_CIRCLE_H
#define BETTERTHANGIMP_CIRCLE_H


#include "../Drawing.h"

class Circle : public Drawing {
public:
    Circle(Workspace &);

    Mat applyManipulation() override;

private:
    cv::Point center;
};


#endif //BETTERTHANGIMP_CIRCLE_H
