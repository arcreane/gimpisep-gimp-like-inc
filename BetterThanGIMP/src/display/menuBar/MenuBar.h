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
    MenuBar(Workspace &workspace);

public:
signals:

    void onOpenEmitFilePath(QString path);

    void onSaveEmitFilePath(QString path);

    void newManipulationSelected(Manipulation *manipulation);

    void saveOnDisk();

    void undoManipulation();


public slots :

    void closeApplication();

    void openFile();

    void exportImage();
};


#endif //BETTERTHANGIMP_MENUBAR_H
