#include "Button.h"
#include "../Model/Model.h"

#pragma once

class RightButton : public Button
{
    Model *model;

public:
    RightButton(Model *model) : model(model) {}

    int execute(int command)
    {
        int victory = 2;

        if (command == Right)
            victory = model->right();

        return victory;
    }
};