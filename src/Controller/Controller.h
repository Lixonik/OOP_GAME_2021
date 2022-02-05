#include <vector>
#include <conio.h>
#include "../Model/Model.h"
#include "../Button/Button.h"
#include "../Button/DownButton.h"
#include "../Button/LeftButton.h"
#include "../Button/RightButton.h"
#include "../Button/UpButton.h"
#include "../Button/SaveButton.h"
#include "../Button/LoadButton.h"

#pragma once

class Controller
{
    static Controller *instance;
    Model* model;
    std::vector <Button *> buttons;

    Controller(Model *model);
public:
    static Controller *get_instance(Model *model);

    Controller(Controller &other) = delete;

    void operator=(const Controller &) = delete;

    void load_save();

    bool readout();

    ~Controller();
};