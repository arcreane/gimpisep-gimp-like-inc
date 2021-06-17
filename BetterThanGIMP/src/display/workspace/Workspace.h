//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_WORKSPACE_H
#define BETTERTHANGIMP_WORKSPACE_H


#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <QLabel>
#include <QDropEvent>
#include <QDragEnterEvent>

class Workspace : public QLabel {
Q_OBJECT
private:
    const cv::Mat &currentImage;

    cv::Point convertCoordinatesOnDisplayToCoordinatesOnImage(double xOnDisplayRaw, double yOnDisplayRaw);

public:
    Workspace(const cv::Mat &imageInMemory);

    void updateImageDisplay();

    void updateImageDisplay(cv::Mat imageToDisplay);

    void dropEvent(QDropEvent *ev) override;

    void dragEnterEvent(QDragEnterEvent *ev) override;

    void mousePressEvent(QMouseEvent *ev) override;
    
    void mouseReleaseEvent(QMouseEvent *ev) override;

    void mouseMoveEvent(QMouseEvent *ev) override;

public:
signals:

    void onDropEmitFilePath(QString path);

    void mouseMoved(cv::Point coordinates);

    void mousePressed(cv::Point clicCoordinates);

    void mouseReleased();
};


#endif //BETTERTHANGIMP_WORKSPACE_H
