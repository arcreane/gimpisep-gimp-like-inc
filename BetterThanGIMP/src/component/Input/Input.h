//
// Created by Hugues Baratgin on 17/06/2021.
//

#ifndef BETTERTHANGIMP_INPUT_H
#define BETTERTHANGIMP_INPUT_H


#include <QLineEdit>
#include <QLabel>

class Input : public QWidget {
Q_OBJECT
public:

    Input(const QString title);

    QLineEdit *getInput();

private:
    QLabel *title;
    QLineEdit *input;
};


#endif //BETTERTHANGIMP_INPUT_H
