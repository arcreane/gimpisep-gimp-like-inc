//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_WINDOW_H
#define BETTERTHANGIMP_WINDOW_H


#include <opencv2/opencv.hpp>
#include <QGridLayout>
#include <QMenuBar>
#include <QMainWindow>

#include "drawingMenu/DrawingMenu.h"
#include "optionsMenu/OptionsMenu.h"
#include "menuBar/MenuBar.h"
#include "workspace/Workspace.h"
#include "../manipulations/Manipulation.h"

class Window : public QWidget {
Q_OBJECT
private:
    QHBoxLayout *layout;
    MenuBar *mainMenu;
    DrawingMenu *drawingMenu;
    Workspace *workspace;
    OptionsMenu *manipulationOptionsMenu;
    cv::Mat image;
    Manipulation *currentManipulation;

    void resizeEvent(QResizeEvent *e) override;

private slots :

    void loadImageFromString(QString path);

    void setCurrentManipulation(Manipulation *manipulationToUse);

    void saveOnDisk();

    void exportImage(QString path);

    void undo();

public:
    Window();
};

#endif //BETTERTHANGIMP_WINDOW_H
