#include "Controller.h"

Controller *Controller::instance = nullptr;

Controller ::Controller(Model *model) : model(model) 
{   
    DownButton* down_button = new DownButton(model);
    LeftButton* left_button = new LeftButton(model);
    RightButton* right_button = new RightButton(model);
    UpButton* up_button = new UpButton(model);
    SaveButton* save_button = new SaveButton(model);
    LoadButton* load_button = new LoadButton(model);

    buttons.push_back(down_button);
    buttons.push_back(left_button);
    buttons.push_back(right_button);
    buttons.push_back(up_button);
    buttons.push_back(save_button);
    buttons.push_back(load_button);
}

Controller *Controller ::get_instance(Model *model)
{
    if (instance == nullptr)
        instance = new Controller(model);

    return instance;
}

void Controller:: load_save()
{
    for (Button *button : buttons)
        button->execute(Load);
}

bool Controller ::readout()
{
    int command = toupper(getch());
    bool victory; 
    int victory_tmp;

    for (Button *button : buttons)
    {
        victory_tmp = button->execute(command);
        if (victory_tmp != 2)
            victory = victory_tmp;
    }
            
    return victory;
}

Controller ::~Controller()
{
    if (instance)
        delete instance;

    for (Button *button : buttons)
        delete button;
}