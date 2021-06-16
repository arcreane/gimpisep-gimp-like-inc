//
// Created by yakiimo on 5/10/21.
//

#include <QPushButton>
#include <QLayout>
#include "ToolMenu.h"

ToolMenu::ToolMenu(){
    this->setStyleSheet("QWidget{background-color: blue;}");
    this->setLayout(new QVBoxLayout());
    QPushButton *circleButton = new QPushButton("Draw Circle");
    QPushButton *boxButton = new QPushButton("Draw Box");
    QPushButton *brushButton = new QPushButton("Draw with brush");
    this->layout()->addWidget(circleButton);
    this->layout()->addWidget(boxButton);
    this->layout()->addWidget(brushButton);
}