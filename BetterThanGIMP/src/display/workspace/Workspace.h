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
    Workspace(cv::Mat &);

    void updateImageDisplay();

    void updateImageDisplay(cv::Mat);

    void dropEvent(QDropEvent *) override;

    void dragEnterEvent(QDragEnterEvent *) override;

public:
signals:
    void onDropEmitFilePath(QString);


};


#endif //BETTERTHANGIMP_WORKSPACE_H
