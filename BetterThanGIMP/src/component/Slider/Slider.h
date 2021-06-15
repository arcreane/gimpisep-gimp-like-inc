//
// Created by Hugues Baratgin on 15/06/2021.
//

#ifndef BETTERTHANGIMP_SLIDER_H
#define BETTERTHANGIMP_SLIDER_H


#include <QSlider>
#include <QLabel>

class Slider : public QWidget {
Q_OBJECT
private:
    QSlider *slider;
    QLabel *currentValue;

public:
    Slider(QString, int, int, int,int = 0);

    QSlider *getSlider();

    void setCurrentValue(int);
};


#endif //BETTERTHANGIMP_SLIDER_H
