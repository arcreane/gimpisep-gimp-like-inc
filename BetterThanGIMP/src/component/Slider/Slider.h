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
    Slider(QString name, Qt::Orientation orientation, int min, int max, int defaultValue, int offset = 0);

    QSlider *getSlider();

    void setCurrentValue(double newValue);
};


#endif //BETTERTHANGIMP_SLIDER_H
