//
// Created by yakiimo on 5/10/21.
//

#include <opencv2/imgproc.hpp>
#include <QMimeData>
#include <iostream>
#include "Workspace.h"

using namespace cv;

Workspace::Workspace(const Mat &currentImage) : currentImage(currentImage) {
    //TEMP
    this->setStyleSheet("QLabel{background-color: red; color: blue;}");
    this->setAlignment(Qt::AlignCenter);
    this->setText("You can drag and drop you image here !");
    this->setAcceptDrops(true);
}

void Workspace::updateImageDisplay() {
    Mat tmp;
    cvtColor(currentImage, tmp, COLOR_BGR2RGB);
    QImage qImage = QImage((uchar *) tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888)
            .scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(QPixmap::fromImage(qImage));
}


void Workspace::updateImageDisplay(Mat image) {
    Mat tmp;
    cvtColor(image, tmp, COLOR_BGR2RGB);
    QImage qImage = QImage((uchar *) tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888)
            .scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setPixmap(QPixmap::fromImage(qImage));
}

void Workspace::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();
    if (mimeData->hasUrls()) {
        emit onDropEmitFilePath(mimeData->urls().at(0).toLocalFile());
    }
}

void Workspace::dragEnterEvent(QDragEnterEvent *event) {
    event->accept();
}

void Workspace::mouseReleaseEvent(QMouseEvent *) {

    std::cout << "xReal   yReal " << std::endl;
}

void Workspace::mouseMoveEvent(QMouseEvent *ev) {
    if (this->pixmap()) {
        Point coordOnImage = convertCoordinatesOnDisplayToCoordinatesOnImage(ev->x(), ev->y());
        if (coordOnImage.x != -1 && coordOnImage.y != -1) {
            emit mouseMoved(coordOnImage);
        }
    }

}

Point Workspace::convertCoordinatesOnDisplayToCoordinatesOnImage(double xOnDisplayRaw, double yOnDisplayRaw) {
    double onDisplayWidth = this->pixmap()->rect().width();
    double onDisplayHeight = this->pixmap()->rect().height();

    double onRealWidth = this->currentImage.cols;
    double onRealHeight = this->currentImage.rows;

    double xOffset = (this->width() - onDisplayWidth) / 2;
    double yOffset = (this->height() - onDisplayHeight) / 2;

    double xRatio = onRealWidth / onDisplayWidth;
    double yRatio = onRealHeight / onDisplayHeight;

    double xOnDisplay = xOnDisplayRaw - xOffset;
    double yOnDisplay = yOnDisplayRaw - yOffset;

    int xOnRealImage = (int) xOnDisplay * xRatio;
    int yOnRealImage = (int) yOnDisplay * yRatio;

    if ((xOnRealImage >= 0 && xOnRealImage <= onRealWidth)
        && (yOnRealImage >= 0 && yOnRealImage <= onRealHeight)) {
        return Point(xOnRealImage, yOnRealImage);
    }
    return Point(-1, -1);
}