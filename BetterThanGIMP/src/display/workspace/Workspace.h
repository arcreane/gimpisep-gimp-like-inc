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
public:
    Workspace();
    void updateImage(cv::Mat);
    void dropEvent(QDropEvent* event) override;
    void dragEnterEvent(QDragEnterEvent* event) override;
public:signals:
    void updateWindowImage(QString string);
};


#endif //BETTERTHANGIMP_WORKSPACE_H
