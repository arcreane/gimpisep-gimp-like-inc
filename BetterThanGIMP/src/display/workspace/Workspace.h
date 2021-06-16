//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_WORKSPACE_H
#define BETTERTHANGIMP_WORKSPACE_H


#include <opencv2/core/mat.hpp>
#include <QLabel>
#include <QDropEvent>
#include <QDragEnterEvent>

class Workspace : public QLabel {
Q_OBJECT
private:
    cv::Mat &currentImage;
public:
    Workspace(cv::Mat & imageInMemory);

    void updateImageDisplay();

    void updateImageDisplay(cv::Mat imageToDisplay);

    void dropEvent(QDropEvent *ev) override;

    void dragEnterEvent(QDragEnterEvent *ev) override;

public:
signals:
    void onDropEmitFilePath(QString path);


};


#endif //BETTERTHANGIMP_WORKSPACE_H
