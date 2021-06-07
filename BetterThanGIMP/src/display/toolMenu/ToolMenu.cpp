//
// Created by yakiimo on 5/10/21.
//

#include <QPushButton>
#include <QLayout>
#include "ToolMenu.h"

ToolMenu::ToolMenu(){
    this->setStyleSheet("QWidget{background-color: blue;}");
    QPushButton *circleButton = new QPushButton("Draw Circle", this);
    circleButton->move(80,0);
    QPushButton *boxButton = new QPushButton("Draw Box", this);
}