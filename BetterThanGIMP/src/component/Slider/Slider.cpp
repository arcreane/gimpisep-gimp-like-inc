//
// Created by Hugues Baratgin on 15/06/2021.
//

#include <QVBoxLayout>
#include <QLabel>
#include "Slider.h"

Slider::Slider(QString name, Qt::Orientation orientation, int min, int max, int defaultValue, int defaultOffset) {
    QLabel *sliderTitle = new QLabel(name);

    this->slider = new QSlider(orientation);
    this->slider->setRange(min, max);
    this->slider->setValue(defaultValue + defaultOffset);

    this->currentValue = new QLabel(QString::number(defaultValue));

    this->setLayout(new QVBoxLayout());

    if (orientation == Qt::Vertical) {
        this->layout()->addWidget(sliderTitle);
        this->layout()->setAlignment(sliderTitle, Qt::AlignHCenter);
        this->layout()->addWidget(this->slider);
        this->layout()->setAlignment(this->slider, Qt::AlignHCenter);
        this->layout()->addWidget(this->currentValue);
        this->layout()->setAlignment(this->currentValue, Qt::AlignHCenter);
    } else {
        QWidget *sliderInfo = new QWidget();
        sliderInfo->setLayout(new QHBoxLayout);

        sliderInfo->layout()->addWidget(sliderTitle);
        this->layout()->setAlignment(sliderTitle, Qt::AlignHCenter);
        sliderInfo->layout()->addWidget(this->currentValue);
        this->layout()->setAlignment(this->currentValue, Qt::AlignHCenter);

        this->layout()->addWidget(sliderInfo);

        this->layout()->addWidget(this->slider);
        this->layout()->setAlignment(this->slider, Qt::AlignHCenter);
    }

}

QSlider *Slider::getSlider() {
    return this->slider;
}

void Slider::setCurrentValue(int newValue) {
    this->currentValue->setText(QString::number(newValue));
}