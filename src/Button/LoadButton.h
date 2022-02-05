#include <fstream>
#include "Button.h"
#include "../Model/Model.h"
#include "../View/View.h"

#pragma once

class LoadButton : public Button
{
    Model *model;

    void load()
    {
        View *view = View::get_instance();
        std::string savename;
        std::cin >> savename;
        savename += ".json";

        std::ifstream in("./saves/" + savename);
        nlohmann::json js;

        if (in.is_open())
        {
            try
            {
                in >> js;
                model->set_json_copy(js);
            }
            catch (nlohmann::detail::parse_error)
            {
                view->err("The save file is not correct");
                view->pause();
            }

            in.close();
        }
    }

public:
    LoadButton(Model *model) : model(model) {}

    int execute(int command)
    {
        View *view = View::get_instance();
        int victory = 2;

        if (command == Load)
        {
            view->imagine("Enter the name of the save: ");
            load();
        }

        return victory;
    }
};