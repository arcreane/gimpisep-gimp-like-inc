//
// Created by yakiimo on 5/10/21.
//

#include <QStyleFactory>
#include <QStatusBar>
#include <QPushButton>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include "Window.h"

Window::Window() {
    layout = new QGridLayout(this);
    workspace = new Workspace();
    mainMenu = new MenuBar(workspace);
    optionsMenu = new OptionsMenu();
    toolMenu = new ToolMenu();

    connect(mainMenu, &MenuBar::updateWindowImage, this, &Window::loadImage);
    connect(workspace, &Workspace::updateWindowImage, this, &Window::loadImage);
    connect(mainMenu, &MenuBar::applyFilterImage, this, &Window::loadImage);
    /*
    QStatusBar *statusBar = new QStatusBar(nullptr);
    QPushButton *test = new QPushButton("Hello World!", statusBar);
    this->setStatusBar(statusBar);
    */

    this->setLayout(layout);
    layout->setMenuBar(mainMenu);
    layout->addWidget(toolMenu, 0, 0);
    layout->addWidget(workspace, 0, 1, 0, 3);
    layout->addWidget(optionsMenu, 0, 4);

    this->setMinimumSize(1280, 720);
    this->show();
}

void Window::loadImage(QString path) {
    if (path.size() > 0) {
        std::string filePath = path.toUtf8().constData();
        std::cout << filePath << std::endl;
        cv::Mat temp = cv::imread(filePath);
        if (!temp.data) {
            std::cout << "Error loading image" << std::endl;
            QMessageBox error;
            error.setText("An error has occured");
            error.exec();
        } else {
            temp.copyTo(this->image);
            workspace->updateImage(this->image);
        }
    }
}

void Window::loadImage(cv::Mat image) {
    if (!image.data) {
        std::cout << "Error loading image" << std::endl;
        QMessageBox error;
        error.setText("An error has occured");
        error.exec();
    } else {
        workspace->updateImage(this->image);
    }
}


