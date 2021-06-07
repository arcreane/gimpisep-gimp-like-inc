//
// Created by yakiimo on 5/10/21.
//

#include <QSlider>
#include <iostream>
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(){
    this->setStyleSheet("QWidget{background-color: green;}");
    QSlider *slider = new QSlider(Qt::Horizontal,this);
    slider->setRange(0,100);
    slider->setValue(50);
    connect(slider, &QSlider::valueChanged, this, &OptionsMenu::setValue);
}

void OptionsMenu::setValue(int i){
    std::cout << i << std::endl;
}