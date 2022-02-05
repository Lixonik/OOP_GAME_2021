#include "Button.h"
#include "../Model/Model.h"

#pragma once

class DownButton : public Button
{
    Model *model;

public:
    DownButton(Model *model) : model(model) {}

    int execute(int command)
    {
        int victory = 2;

        if (command == Down)
            victory = model->down();

        return victory;
    }
};