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

class Window : public QMainWindow {
Q_OBJECT
private:
    QGridLayout *layout;
    MenuBar *mainMenu;
    ToolMenu *toolMenu;
    Workspace *workspace;
    OptionsMenu *optionsMenu;

public:
    Window();
};


#endif //BETTERTHANGIMP_WINDOW_H
