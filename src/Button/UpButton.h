#include "Button.h"
#include "../Model/Model.h"

#pragma once

class UpButton : public Button
{
    Model *model;

public:
    UpButton(Model *model) : model(model) {}

    int execute(int command)
    {
        int victory = 2;

        if (command == Up)
            victory = model->up();

        return victory;
    }
};