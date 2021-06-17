//
// Created by Hugues Baratgin on 17/06/2021.
//

#include <QHBoxLayout>

#include "Input.h"

Input::Input(const QString title) {
    this->setLayout(new QHBoxLayout());
    this->title = new QLabel(title);
    this->input = new QLineEdit();

    this->layout()->addWidget(this->title);
    this->layout()->addWidget(this->input);
}

QLineEdit *Input::getInput() {
    return this->input;
}