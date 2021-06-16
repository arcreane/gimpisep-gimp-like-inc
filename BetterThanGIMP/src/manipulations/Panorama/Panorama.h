//
// Created by yakiimo on 6/15/21.
//

#ifndef BETTERTHANGIMP_PANORAMA_H
#define BETTERTHANGIMP_PANORAMA_H

#include "../Manipulation.h"
#include "../../display/workspace/Workspace.h"
#include <QScrollArea>


class Panorama : public Manipulation {

public:
    Panorama(Workspace &);
    Mat applyManipulation();

private:
    Mat stitch(std::vector<Mat> images_to_stitch);
    bool crop_after_stitching(Mat& image, Mat& output);
    bool checkBlackRow(const Mat &gray_image, int y, const Rect &outputRect);
    bool checkBlackColumn(const Mat &gray_image, int x, const Rect &outputRect);
    void displayImagesThumbnails();

    bool mustBeCropped;
    QStringList paths;
    std::vector<Mat> images_to_stitch;
    QWidget *thumbnails;

};


#endif //BETTERTHANGIMP_PANORAMA_H