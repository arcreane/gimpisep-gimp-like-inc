//
// Created by yakiimo on 5/10/21.
//

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
    connect(this->mainMenu, &MenuBar::onSaveEmitFilePath, this, &Window::exportImage);
    connect(this->mainMenu, &MenuBar::newManipulationSelected, this, &Window::setCurrentManipulation);
    connect(this->mainMenu, &MenuBar::saveOnDisk, this, &Window::saveOnDisk);

    this->manipulationOptionsMenu = new OptionsMenu();

    this->drawingMenu = new DrawingMenu(*this->workspace);
    connect(this->drawingMenu, &DrawingMenu::newManipulationSelected, this, &Window::setCurrentManipulation);

    this->setLayout(layout);
    layout->setMenuBar(mainMenu);

    layout->addWidget(drawingMenu, 10);
    layout->addWidget(workspace, 60);
    layout->addWidget(manipulationOptionsMenu, 30);

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
            std::cout << "Error: The image can't be loaded" << std::endl;
            QMessageBox error;
            error.setText("An error has occurred on the image loading!");
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
        std::cout << "Set current manipulation on: " << manipulation->getName() << std::endl;
        this->manipulationOptionsMenu->setOptions(manipulation->getOptions(),
                                                  QString::fromUtf8(manipulation->getName().c_str()));

        this->currentManipulation = manipulation;
        this->currentManipulation->setImageSavedInMemory(this->image);
    } else {
        std::cout << "Error: The image in memory is empty, can't set the manipulation!" << std::endl;
        QMessageBox error;
        error.setText("Can't perform requested manipulation on an empty image!");
        error.exec();

        delete manipulation;
    }
}

void Window::saveOnDisk() {
    if (this->image.empty()) {
        std::cout << "Error: No image to save" << std::endl;
        QMessageBox error;
        error.setText("There is no image to be saved!");
        error.exec();
    }
    if (!this->image.empty()) {
        if (currentManipulation != nullptr) {
            this->image = currentManipulation->applyManipulation();
        }
        imwrite("output.png", this->image);
    }
}


void Window::exportImage(QString path) {

    if (this->image.empty()) {
        std::cout << "Error: No image to save" << std::endl;
        QMessageBox error;
        error.setText("There is no image to be saved!");
        error.exec();
    }
    if (!this->image.empty()) {
        if (currentManipulation != nullptr) {
            this->image = currentManipulation->applyManipulation();
        }
        std::string filePath = path.toUtf8().constData();

        if (filePath == "") {
            std::cout << "Error: No path" << std::endl;
            QMessageBox error;
            error.setText("You must specify a path to store the image!");
            error.exec();
        } else if (filePath.find('.') == -1) {
            std::cout << "Error: No extension" << std::endl;
            QMessageBox error;
            error.setText("You must specify an extension for the image!");
            error.exec();
        } else {
            imwrite(filePath, this->image);
        }
    }
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