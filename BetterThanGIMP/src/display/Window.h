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
#include "../manipulations/Manipulation.h"
#include <opencv2/opencv.hpp>

class Window : public QWidget {
Q_OBJECT
private:
    QGridLayout *layout;
    MenuBar *mainMenu;
    ToolMenu *toolMenu;
    Workspace *workspace;
    OptionsMenu *manipulationOptionsMenu;
    cv::Mat image;
    Manipulation* currentManipulation;

private slots :
    void loadImageFromString(QString);
    void setCurrentManipulation(Manipulation*);
    void saveOnDisk();

public:
    Window();
};

#endif //BETTERTHANGIMP_WINDOW_H
