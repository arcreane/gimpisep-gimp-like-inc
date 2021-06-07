//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_WINDOW_H
#define BETTERTHANGIMP_WINDOW_H


#include <QGridLayout>
#include <QMenuBar>
#include <QMainWindow>
#include "toolMenu/ToolMenu.h"
#include "workspace/Workspace.h"
#include "optionsMenu/OptionsMenu.h"
#include "menuBar/MenuBar.h"
#include <opencv2/opencv.hpp>

class Window : public QWidget {
Q_OBJECT
private:
    QGridLayout *layout;
    MenuBar *mainMenu;
    ToolMenu *toolMenu;
    Workspace *workspace;
    OptionsMenu *optionsMenu;
    cv::Mat image;
    void loadImage(QString);
    void loadImage(cv::Mat);

public:
    Window();
};


#endif //BETTERTHANGIMP_WINDOW_H
