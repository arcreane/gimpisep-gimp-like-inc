//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_OPTIONSMENU_H
#define BETTERTHANGIMP_OPTIONSMENU_H


#include <QWidget>
#include <QGridLayout>

class OptionsMenu : public QWidget {
public:
    OptionsMenu();

    void setOptions(QWidget *, QString);

    void removeOptions();


private:
    QVBoxLayout *layout;
    QWidget *currentOptions;
    QLabel *title;
};


#endif //BETTERTHANGIMP_OPTIONSMENU_H
