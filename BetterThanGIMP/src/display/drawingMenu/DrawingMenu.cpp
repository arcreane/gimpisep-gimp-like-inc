//
// Created by yakiimo on 5/10/21.
//

#include <QPushButton>
#include <QVBoxLayout>

#include "DrawingMenu.h"
#include "../../manipulations/drawing/Brush/Brush.h"
#include "../../manipulations/drawing/Circle/Circle.h"
#include "../../manipulations/drawing/Box/Box.h"

DrawingMenu::DrawingMenu(Workspace &workspace) {
    this->setLayout(new QVBoxLayout());

    QPushButton *circleButton = new QPushButton("Draw Circle");
    connect(circleButton, &QPushButton::pressed, this, [this, &workspace]() {
        this->emit newManipulationSelected(new Circle(workspace));
    });

    QPushButton *boxButton = new QPushButton("Draw Box");
    connect(boxButton, &QPushButton::pressed, this, [this, &workspace]() {
        this->emit newManipulationSelected(new Box(workspace));
    });

    QPushButton *brushButton = new QPushButton("Draw with brush");
    connect(brushButton, &QPushButton::pressed, this, [this, &workspace]() {
        this->emit newManipulationSelected(new Brush(workspace));
    });

    this->layout()->addWidget(circleButton);
    this->layout()->addWidget(boxButton);
    this->layout()->addWidget(brushButton);

    this->setStyleSheet("QWidget{padding: 20px; border: 2px solid grey;}"
                        "QWidget:hover{background-color: lightGrey}");
}