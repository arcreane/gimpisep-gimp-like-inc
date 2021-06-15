//
// Created by Hugues Baratgin on 15/06/2021.
//

#include <QVBoxLayout>
#include <QLabel>
#include "Slider.h"

Slider::Slider(QString name, int min, int max, int defaultValue, int defaultOffset) {
    QLabel *sliderTitle = new QLabel(name);

    this->slider = new QSlider(Qt::Vertical);
    this->slider->setRange(min, max);
    this->slider->setValue(defaultValue + defaultOffset);

    this->currentValue = new QLabel("Value: " + QString::number(defaultValue));

    this->setLayout(new QVBoxLayout());

    this->layout()->addWidget(sliderTitle);
    this->layout()->setAlignment(sliderTitle, Qt::AlignHCenter);
    this->layout()->addWidget(this->slider);
    this->layout()->setAlignment(this->slider, Qt::AlignHCenter);
    this->layout()->addWidget(this->currentValue);
    this->layout()->setAlignment(this->currentValue, Qt::AlignHCenter);
}

QSlider *Slider::getSlider() {
    return this->slider;
}

void Slider::setCurrentValue(int newValue) {
    this->currentValue->setText("Value: " + QString::number(newValue));
}