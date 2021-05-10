//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_WORKSPACE_H
#define BETTERTHANGIMP_WORKSPACE_H


#include <opencv2/core/mat.hpp>
#include <QLabel>

class Workspace : public QLabel {
public:
    Workspace();
    void updateImage(cv::Mat);
};


#endif //BETTERTHANGIMP_WORKSPACE_H
