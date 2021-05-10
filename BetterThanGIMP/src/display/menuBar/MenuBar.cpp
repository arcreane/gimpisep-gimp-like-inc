//
// Created by yakiimo on 5/10/21.
//

#include <iostream>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "MenuBar.h"

MenuBar::MenuBar(Workspace *workspace){
    this->workspace = workspace;

    QMenu *fileMenu = this->addMenu(("&File"));

    QAction *openAction = fileMenu->addAction("Open...");
    connect(openAction, &QAction::triggered, this, &MenuBar::openFile);
    openAction->setShortcut(QKeySequence("Ctrl+O"));

    QAction *saveAction = fileMenu->addAction("Save");
    QAction *exportAction = fileMenu->addAction("Export...");

    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &MenuBar::closeApplication);
    exitAction->setShortcut(QKeySequence("Ctrl+E"));

    QMenu *editMenu = this->addMenu(("&Edit"));
    QAction *undoAction = editMenu->addAction("Undo");
    QAction *redoAction = editMenu->addAction("Redo");
    QAction *resizeAction = editMenu->addAction("Resize");
    QMenu *filterMenu = this->addMenu(("&Filter"));
    QAction *dilatationAction = filterMenu->addAction("Dilatation");
    QAction *monochromeAction = filterMenu->addAction("Monochrome");
    QAction *contrastAction = filterMenu->addAction("Contrast");
    QAction *expositionAction = filterMenu->addAction("Exposition");
    QAction *erosionAction = filterMenu->addAction("Erosion");
    QAction *brightnessAction = filterMenu->addAction("Brightness");
    QAction *blurAction = filterMenu->addAction("Blur");
    QAction *gaussianBlurAction = filterMenu->addAction("Gaussian Blur");
}

void MenuBar::closeApplication(){
    exit(0);
}

void MenuBar::openFile(){
    QString path;
    path = QFileDialog::getOpenFileName(workspace, "Open file", "/", "Image Files (*.png *gif * jpg *bmp *jpeg * jfif)");
    std::string filePath = path.toUtf8().constData();
    std::cout << filePath << std::endl;
    cv::Mat image = cv::imread(filePath);
    if (!image.data){
        std::cout << "Error loading image" << std::endl;
        exit(-1);
    }
    workspace->updateImage(image);

}