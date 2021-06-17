//
// Created by yakiimo on 5/10/21.
//

#include <opencv2/imgproc.hpp>
#include <QMimeData>

#include "Workspace.h"

using namespace cv;

Workspace::Workspace(const Mat &currentImage) : imageInMemory(currentImage) {
    this->setAlignment(Qt::AlignCenter);
    this->setText("You can drag and drop your image here !");
    this->setAcceptDrops(true);


    this->setStyleSheet(
            "QLabel{border-left: 2px solid black; border-right: 2px solid black;border-radius: 0; font-size: 20px; color: grey}");
}

void Workspace::updateImageDisplay() {
    if (!imageInMemory.empty()) {
        Mat tmp;
        cvtColor(imageInMemory, tmp, COLOR_BGR2RGB);
        QImage qImage = QImage((uchar *) tmp.data, tmp.size().width, tmp.size().height, tmp.step, QImage::Format_RGB888)
                .scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setPixmap(QPixmap::fromImage(qImage));
    }
}


void Workspace::updateImageDisplay(Mat image) {
    if (!image.empty()) {
        Mat tmp;
        cvtColor(image, tmp, COLOR_BGR2RGB);
        QImage qImage = QImage((uchar *) tmp.data, tmp.size().width, tmp.size().height, tmp.step, QImage::Format_RGB888)
                .scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        this->setPixmap(QPixmap::fromImage(qImage));
    }
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


void Workspace::mousePressEvent(QMouseEvent *ev) {
    if (this->pixmap()) {
        Point coordOnImage = convertCoordinatesOnDisplayToCoordinatesOnImage(ev->x(), ev->y());
        if (coordOnImage.x != -1 && coordOnImage.y != -1) {
            emit mousePressed(coordOnImage);
        }
    }
}

void Workspace::mouseReleaseEvent(QMouseEvent *) {
    if (this->pixmap()) {
        emit mouseReleased();
    }
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

    double onRealWidth = this->imageInMemory.size().width;
    double onRealHeight = this->imageInMemory.size().height;

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