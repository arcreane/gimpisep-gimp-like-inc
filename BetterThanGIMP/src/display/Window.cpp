//
// Created by yakiimo on 5/10/21.
//

#include <QStyleFactory>
#include <QPushButton>
#include <iostream>
#include <QMessageBox>
#include "Window.h"

Window::Window() {
    this->currentManipulation = nullptr;
    this->layout = new QHBoxLayout();

    this->workspace = new Workspace(this->image);
    connect(this->workspace, &Workspace::onDropEmitFilePath, this, &Window::loadImageFromString);

    this->mainMenu = new MenuBar(*this->workspace);
    connect(this->mainMenu, &MenuBar::onOpenEmitFilePath, this, &Window::loadImageFromString);
    connect(this->mainMenu, &MenuBar::newManipulationSelected, this, &Window::setCurrentManipulation);
    connect(this->mainMenu, &MenuBar::saveOnDisk, this, &Window::saveOnDisk);

    this->manipulationOptionsMenu = new OptionsMenu();

    this->toolMenu = new ToolMenu(*this->workspace);
    connect(this->toolMenu, &ToolMenu::newManipulationSelected, this, &Window::setCurrentManipulation);

    this->setLayout(layout);
    layout->setMenuBar(mainMenu);

    layout->addWidget(toolMenu, 1);
    layout->addWidget(workspace, 7);
    layout->addWidget(manipulationOptionsMenu, 2);

    this->setMinimumSize(1280, 720);

    this->setStyleSheet(
            "QWidget{background-color:#C0C0C0;}");
    this->show();

}

void Window::loadImageFromString(QString path) {
    if (path.size() > 0) {
        std::string filePath = path.toUtf8().constData();
        cv::Mat temp = cv::imread(filePath);
        if (temp.empty()) {
            std::cout << "Error loading image" << std::endl;
            QMessageBox error;
            error.setText("An error has occured");
            error.exec();
        } else {
            if (currentManipulation) {
                delete this->currentManipulation;
                this->currentManipulation = nullptr;
                this->manipulationOptionsMenu->removeOptions();
            }
            temp.copyTo(this->image);
            workspace->updateImageDisplay();
        }
    }
}

void Window::setCurrentManipulation(Manipulation *manipulation) {

    if (currentManipulation && !currentManipulation->getImageModified().empty()) {
        this->image = currentManipulation->getImageModified();
        delete this->currentManipulation;
        workspace->updateImageDisplay();
    }

    if (!this->image.empty() || manipulation->getName() == "Panorama") {
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

void Window::resizeEvent(QResizeEvent *e) {
    if (currentManipulation) {
        currentManipulation->onResize();
    }
    if (!this->image.empty()) {
        if (currentManipulation) {
            currentManipulation->updateImageDisplayOnWorkspace();
        } else {
            workspace->updateImageDisplay();
        }
    }
}