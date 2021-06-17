//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_DRAWINGMENU_H
#define BETTERTHANGIMP_DRAWINGMENU_H


#include <QWidget>

#include "../workspace/Workspace.h"
#include "../../manipulations/Manipulation.h"

class DrawingMenu : public QWidget {
Q_OBJECT
public:
    DrawingMenu(Workspace &);

public:
signals:

    void newManipulationSelected(Manipulation *);
};

#endif //BETTERTHANGIMP_DRAWINGMENU_H
