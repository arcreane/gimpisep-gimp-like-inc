//
// Created by Hugues Baratgin on 12/06/2021.
//

#ifndef BETTERTHANGIMP_MANIPULATION_H
#define BETTERTHANGIMP_MANIPULATION_H


#include <opencv2/core/mat.hpp>
#include <iostream>
#include <QWidget>
#include "../display/workspace/Workspace.h"

using namespace cv;

class Manipulation : public QWidget {
Q_OBJECT
public:
    Manipulation(Workspace &);

    virtual Mat applyManipulation() = 0;

    virtual void onResize();

    QWidget *getOptions();

    std::string getName();

    Mat getImageModified();

    void setImageSavedInMemory(Mat);

    void updateImageDisplayOnWorkspace();

protected:
    QWidget *options;
    std::string name;
    Mat imageSavedInMemory;
    Mat imageModified;
    Workspace &workspace;

    void updateImageDisplay();
};


#endif //BETTERTHANGIMP_MANIPULATION_H
