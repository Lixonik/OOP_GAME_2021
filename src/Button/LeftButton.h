#include "Button.h"
#include "../Model/Model.h"

#pragma once

class LeftButton : public Button
{
    Model *model;

public:
    LeftButton(Model *model) : model(model) {}

    int execute(int command)
    {
        int victory = 2;

        if (command == Left)
            victory = model->left();

        return victory;
    }
};