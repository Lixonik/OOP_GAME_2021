#include <fstream>
#include "Button.h"
#include "../Model/Model.h"
#include "../View/View.h"

#pragma once

class SaveButton : public Button
{
    Model *model;

    void save()
    {
        std::string savename;
        std::cin >> savename;
        savename += ".json";

        std::ofstream out("./saves/" + savename);
        if (out.is_open())
        {
            out << model->get_json_copy();
            out.close();
        }
    }
public:
    SaveButton(Model *model) : model(model) {}

    int execute(int command)
    {
        View *view = View::get_instance();
        int victory = 2;

        if (command == Save)
        {
            view->imagine("Enter the name of the save: ");
            save();
        }

        return victory;
    }
};