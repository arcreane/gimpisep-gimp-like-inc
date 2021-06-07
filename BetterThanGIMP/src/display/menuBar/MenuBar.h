//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_MENUBAR_H
#define BETTERTHANGIMP_MENUBAR_H


#include <QMenuBar>
#include "../workspace/Workspace.h"

class MenuBar : public QMenuBar {
    Q_OBJECT

private:
    Workspace *workspace;
public:
    MenuBar(Workspace *workspace);
public:signals:
    void updateWindowImage(QString string);

public slots :
    void closeApplication();
    void openFile();
    cv::Mat monochrome(cv::Mat image);
};


#endif //BETTERTHANGIMP_MENUBAR_H
