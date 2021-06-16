//
// Created by yakiimo on 5/10/21.
//

#include <opencv2/imgproc.hpp>
#include <QMimeData>
#include <iostream>
#include "Workspace.h"

using namespace cv;

Workspace::Workspace(Mat &currentImage) : currentImage(currentImage) {
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