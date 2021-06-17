//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_TOOLMENU_H
#define BETTERTHANGIMP_TOOLMENU_H


#include <QWidget>
#include "../workspace/Workspace.h"
#include "../../manipulations/Manipulation.h"

class ToolMenu : public QWidget {
Q_OBJECT
public:
    ToolMenu(Workspace &);

public:
signals:

    void newManipulationSelected(Manipulation *);
};


#endif //BETTERTHANGIMP_TOOLMENU_H
