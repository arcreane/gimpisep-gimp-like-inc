//
// Created by yakiimo on 5/10/21.
//

#include <opencv2/imgproc.hpp>
#include "Workspace.h"

Workspace::Workspace(){
    this->setStyleSheet("QLabel{background-color: red; color: blue;}");
    this->setText("Hello World!");
}

void Workspace::updateImage(cv::Mat image){
    cv::Mat tmp;
    cv::cvtColor(image, tmp, cv::COLOR_BGR2RGB);
    QImage qImage = QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888)
            .scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    this->setPixmap(QPixmap::fromImage(qImage));

    //this->setScaledContents(true);
    //this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}