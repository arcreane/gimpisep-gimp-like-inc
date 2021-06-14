//
// Created by yakiimo on 5/10/21.
//

#ifndef BETTERTHANGIMP_MENUBAR_H
#define BETTERTHANGIMP_MENUBAR_H


#include <QMenuBar>
#include "../workspace/Workspace.h"
#include "../../manipulations/Manipulation.h"

class MenuBar : public QMenuBar {
Q_OBJECT

private:
    Workspace &workspace;

public:
    MenuBar(Workspace &);

public:
signals:

    void onOpenEmitFilePath(QString);
    void newManipulationSelected(Manipulation *);
    void saveOnDisk();

public slots :
    void closeApplication();
    void openFile();
};


#endif //BETTERTHANGIMP_MENUBAR_H
