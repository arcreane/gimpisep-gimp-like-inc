//
// Created by yakiimo on 5/10/21.
//

#include <opencv2/imgproc.hpp>
#include <QMimeData>
#include <iostream>
#include "Workspace.h"

Workspace::Workspace(){
    this->setStyleSheet("QLabel{background-color: red; color: blue;}");
    this->setText("Hello World!");
    this->setAcceptDrops(true);
}

void Workspace::updateImage(cv::Mat image){
    cv::Mat tmp;
    cv::cvtColor(image, tmp, cv::COLOR_BGR2RGB);
    QImage qImage = QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.step, QImage::Format_RGB888)
            .scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    this->setPixmap(QPixmap::fromImage(qImage));
    this->workspaceImage = tmp;
    // Crée une image temporaire à partir du QPixmap affiché, récupérer data, taille etc.
    // Lui appliquer la transformation

    //this->setScaledContents(true);
    //this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void Workspace::dropEvent(QDropEvent* event){
    const QMimeData* mimeData = event->mimeData();
    std::cout << "Drop event detected" << std::endl;
    if(mimeData->hasUrls()){
        std::cout << "Success" << std::endl;
        emit updateWindowImage(mimeData->urls().at(0).toLocalFile());
    }
}

void Workspace::dragEnterEvent(QDragEnterEvent *event) {
    std::cout << "Drag enter event" << std::endl;
    event->accept();
};