//
// Created by yakiimo on 5/10/21.
//

#include <QStyleFactory>
#include <QStatusBar>
#include <QPushButton>
#include <iostream>
#include <QFileDialog>
#include "Window.h"

Window::Window() {
    //layout = new QGridLayout(this);
    workspace = new Workspace();
    mainMenu = new MenuBar(workspace);


    /*
    QStatusBar *statusBar = new QStatusBar(nullptr);
    QPushButton *test = new QPushButton("Hello World!", statusBar);
    this->setStatusBar(statusBar);
    */

    this->setCentralWidget(workspace);
    this->setMenuBar(mainMenu);
    this->setMinimumSize(1280, 720);
    this->show();
}

