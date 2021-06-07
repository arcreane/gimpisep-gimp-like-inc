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

signals:
    void updateWindowImage(QString string);
    void applyFilterImage(cv::Mat image);

public slots :
    void closeApplication();
    void openFile();
    void monochrome();
};


#endif //BETTERTHANGIMP_MENUBAR_H
