//
// Created by yakiimo on 5/10/21.
//

#include <iostream>
#include <QFileDialog>
#include <opencv2/opencv.hpp>

#include "MenuBar.h"
#include "../../manipulations/Monochrome/Monochrome.h"
#include "../../manipulations/CannyEdge/CannyEdge.h"
#include "../../manipulations/Panorama/Panorama.h"
#include "../../manipulations/Brightness/Brightness.h"
#include "../../manipulations/Blur/Blur.h"
#include "../../manipulations/Erosion/Erosion.h"
#include "../../manipulations/Dilatation/Dilatation.h"

MenuBar::MenuBar(Workspace &workspace) : workspace(workspace) {

    QMenu *fileMenu = this->addMenu(("&File"));

    QAction *openAction = fileMenu->addAction("Open...");
    connect(openAction, &QAction::triggered, this, &MenuBar::openFile);
    openAction->setShortcut(QKeySequence("Ctrl+O"));

    QAction *saveAction = fileMenu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, [this]() { this->emit saveOnDisk(); });
    saveAction->setShortcut(QKeySequence("Ctrl+S"));

    QAction *exportAction = fileMenu->addAction("Export as...");
    connect(exportAction, &QAction::triggered, this, &MenuBar::exportImage);
    exportAction->setShortcut(QKeySequence("Ctrl+E"));

    QAction *exitAction = fileMenu->addAction("Exit");
    connect(exitAction, &QAction::triggered, this, &MenuBar::closeApplication);
    exitAction->setShortcut(QKeySequence("Ctrl+Q"));

    QMenu *editMenu = this->addMenu(("&Edit"));
    QAction *undoAction = editMenu->addAction("Undo");
    QAction *redoAction = editMenu->addAction("Redo");
    QAction *resizeAction = editMenu->addAction("Resize");


    QMenu *filterMenu = this->addMenu(("&Transformation"));
    QAction *dilatationAction = filterMenu->addAction("Dilatation");
    connect(dilatationAction, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new Dilatation(this->workspace));
    });

    QAction *monochromeAction = filterMenu->addAction("Monochrome");
    connect(monochromeAction, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new Monochrome(this->workspace));
    });

    QAction *panoramaAction = filterMenu->addAction("Panorama");
    connect(panoramaAction, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new Panorama(this->workspace));
    });

    QAction *contrastAction = filterMenu->addAction("Contrast");
    //connect(contrastAction, SLOT(triggered()), this, SLOT(applyTransformation(image_to_bright)));

    QAction *expositionAction = filterMenu->addAction("Exposition");
    
    QAction *erosionAction = filterMenu->addAction("Erosion");
    connect(erosionAction, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new Erosion(this->workspace));
    });

    QAction *brightnessAction = filterMenu->addAction("Brightness");
    connect(brightnessAction, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new Brightness(this->workspace));
    });

    QAction *gaussianBlurAction = filterMenu->addAction("Gaussian Blur");
    connect(gaussianBlurAction, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new Blur(this->workspace));
    });

    QAction *cannyEdge = filterMenu->addAction("Canny Edge");
    connect(cannyEdge, &QAction::triggered, this, [this]() {
        this->emit newManipulationSelected(new CannyEdge(this->workspace));
    });
}

void MenuBar::closeApplication() {
    exit(0);
}

void MenuBar::openFile() {
    QString path;
    path = QFileDialog::getOpenFileName(nullptr, "Open file", "/",
                                        "Image Files (*png *jpg *bmp *jpeg *jfif)");

    emit onOpenEmitFilePath(path);
}

void MenuBar::exportImage(){
    QString path;
    QString selectedFilter;
    path = QFileDialog::getSaveFileName(nullptr, "Export as", "/",
                                        "PNG (*.png);; "
                                        "JPEG (*.jpg, *.jpeg);;"
                                        "BMP (*.bmp);;"
                                        "JFIF (*.jfif);;"
                                        "All files (*.*);;",
                                        &selectedFilter);
    emit onSaveEmitFilePath(path);
}
