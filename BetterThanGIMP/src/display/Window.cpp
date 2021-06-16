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
    this->currentManipulation = nullptr;
    this->layout = new QGridLayout(this);

    this->workspace = new Workspace(this->image);
    connect(this->workspace, &Workspace::onDropEmitFilePath, this, &Window::loadImageFromString);

    this->mainMenu = new MenuBar(*this->workspace);
    connect(this->mainMenu, &MenuBar::onOpenEmitFilePath, this, &Window::loadImageFromString);
    connect(this->mainMenu, &MenuBar::newManipulationSelected, this, &Window::setCurrentManipulation);
    connect(this->mainMenu, &MenuBar::saveOnDisk, this, &Window::saveOnDisk);

    this->manipulationOptionsMenu = new OptionsMenu();
    this->toolMenu = new ToolMenu();

    this->setLayout(layout);
    layout->setMenuBar(mainMenu);
    layout->addWidget(toolMenu, 0, 0);
    layout->addWidget(workspace, 0, 1, 0, 3);
    layout->addWidget(manipulationOptionsMenu, 0, 4);

    this->setMinimumSize(1600, 720);
    this->show();
}

void Window::loadImageFromString(QString path) {
    if (path.size() > 0) {
        std::string filePath = path.toUtf8().constData();
        std::cout << filePath << std::endl;
        cv::Mat temp = cv::imread(filePath);
        if (temp.empty()) {
            std::cout << "Error loading image" << std::endl;
            QMessageBox error;
            error.setText("An error has occured");
            error.exec();
        } else {
           if(currentManipulation){
               delete this->currentManipulation;
               this->manipulationOptionsMenu->removeOptions();
           }
            temp.copyTo(this->image);
            workspace->updateImageDisplay();
        }
    }
}

void Window::setCurrentManipulation(Manipulation *manipulation) {
    if (currentManipulation) {
        this->image = currentManipulation->getImageModified();
        delete this->currentManipulation;
        workspace->updateImageDisplay();
    }

    if (!this->image.empty()) {
        std::cout << manipulation->getName() << std::endl;
        this->manipulationOptionsMenu->setOptions(manipulation->getOptions(),
                                                  QString::fromUtf8(manipulation->getName().c_str()));

        this->currentManipulation = manipulation;
        this->currentManipulation->setImageSavedInMemory(this->image);
    } else {
        std::cout << "Error loading image" << std::endl;
        QMessageBox error;
        error.setText("Can't perform requested manipulation on an empty image!");
        error.exec();
    }
}

void Window::saveOnDisk() {
    if (currentManipulation != nullptr) {
        this->image = currentManipulation->applyManipulation();
    }
    imwrite("saved.png", this->image);
    //TODO sauver l'image dans un dossier
}
