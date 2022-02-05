#include <conio.h>
#include "../Model/Model.h"
#include "../View/View.h"
#include "../Controller/Controller.h"
#include "../Rules/Rule_1.h"
#include "../Rules/Rule_2.h"
#include "../Rules/Rule_3.h"
#include "../Logger/Logger.h"
#include "../ConsoleLoggingListener/ConsoleLoggingListener.h"
#include "../FileLoggingListener/FileLoggingListener.h"

#pragma once

template <class R1, class R2, class R3>
class Presenter
{
    Model *model;
    View *view;
    R1 *rule_1;
    R2 *rule_2;
    R3 *rule_3;

    void player_info()
    {
        view->imagine("\n");
        view->imagine(model->get_player_info());
        view->imagine("\n");
    }

    void console_logs_report()
    {
        view->imagine("Output the logs to the console? (y/n): ");
    }

    void file_logs_report()
    {
        view->clear();
        view->imagine("Output the logs to a file? (y/n): ");
    }

    void file_logs_filename_report()
    {
        view->imagine("Enter the name of the log file: ");
    }

    void save_load_report()
    {
        view->clear();
        view->imagine("Do you want to download the save? (y/n): ");
    }

    void manual_report()
    {
        view->clear();
        view->imagine("control buttons:");
        view->imagine("\n");
        view->imagine("w -- up");
        view->imagine("\n");
        view->imagine("s -- down");
        view->imagine("\n");
        view->imagine("a -- left");
        view->imagine("\n");
        view->imagine("d -- right");
        view->imagine("\n");
        view->pause();
        view->clear();
    }

    void lose_report()
    {
        view->imagine("you lose\n");
        view->pause();
    }

    void victory_report()
    {
        view->imagine("you win!\n");
        view->pause();
    }

    void update_model(nlohmann::json js)
    {
        Model mod(js);
        std::swap(*model, mod);
    }

public:
    Presenter(View *view) : model(new Model), view(view), rule_1(new R1), rule_2(new R2), rule_3(new R3) {}
    
    void start()
    {
        Controller* controller = Controller::get_instance(model);
        Logger *logger = Logger::get_instance(model);

        ConsoleLoggingListener console_sub;
        FileLoggingListener file_sub;

        std::string answer;

        console_logs_report();

        getline(std::cin, answer);

        if (answer == "y" || answer == "Y")
            logger->subscribe(console_sub);

        file_logs_report();

        getline(std::cin, answer);

        if (answer == "y" || answer == "Y")
        {
            file_logs_filename_report();

            std::string filename;
            getline(std::cin, filename);

            file_sub.generate("./logs/" + filename + ".txt");
            logger->subscribe(file_sub);
        }

        save_load_report();

        getline(std::cin, answer);

        if (answer == "y" || answer == "Y")
            controller->load_save();
        
        manual_report();

        if (model->get_enemies_count() < rule_2->get_quantity())
            rule_2->set_quantity(model->get_enemies_count());

        if (model->get_items_count() < rule_2->get_quantity())
            rule_2->set_quantity(model->get_items_count());

        int command = 1;
        bool victory = true, good_end = true;

        do
        {
            for (int j = model->get_field().get_height() - 1; j > -1; j--)
            {
                for (int i = 0; i < model->get_field().get_width(); i++)
                    if (!model->get_field().get_cell(i, j)->is_passability() && !model->get_field().get_cell(i, j)->is_enemy())
                        view->imagine("X");
                    else
                    {
                        if (model->get_field().get_cell(i, j)->is_player())
                            view->imagine("P", Blue);

                        if (model->get_field().get_cell(i, j)->is_enemy())
                        {
                            if (model->get_field().get_cell(i, j)->is_zombie())
                                view->imagine("Z", Red);

                            if (model->get_field().get_cell(i, j)->is_goblin())
                                view->imagine("G", Red);

                            if (model->get_field().get_cell(i, j)->is_orc())
                                view->imagine("O", Red);
                        }

                        if (model->get_field().get_cell(i, j)->is_item())
                        {
                            if (model->get_field().get_cell(i, j)->is_med_kit())
                                view->imagine("M", LightGreen);

                            if (model->get_field().get_cell(i, j)->is_sword())
                                view->imagine("S", LightGreen);

                            if (model->get_field().get_cell(i, j)->is_armor())
                                view->imagine("A", LightGreen);
                        }

                        if (model->get_field().get_cell(i, j)->is_entrance() && !model->get_field().get_cell(i, j)->is_player())
                            view->imagine("~", Yellow);

                        if (model->get_field().get_cell(i, j)->is_exit() && !model->get_field().get_cell(i, j)->is_player())
                            view->imagine("#", Yellow);

                        if (!(model->get_field().get_cell(i, j)->is_player() || model->get_field().get_cell(i, j)->is_enemy() || model->get_field().get_cell(i, j)->is_item() || model->get_field().get_cell(i, j)->is_entrance() || model->get_field().get_cell(i, j)->is_exit()))
                            view->imagine(" ");
                    }

                view->imagine("\n");
            }

            player_info();

            logger->respond_to_changes(model);
            
            victory = controller->readout();

            // std::vector<std::string> map;
            // map.resize(model->get_field().get_height());

            // for (int j = model->get_field().get_height() - 1; j > -1; j--)
            // {
            //     for (int i = 0; i < model->get_field().get_width(); i++)
            //         if (!model->get_field().get_cell(i, j)->is_passability() && !model->get_field().get_cell(i, j)->is_enemy())
            //             map[j] += "X";
            //         else
            //         {
            //             if (model->get_field().get_cell(i, j)->is_player())
            //                 map[j] += "P";

            //             if (model->get_field().get_cell(i, j)->is_enemy())
            //             {
            //                 if (model->get_field().get_cell(i, j)->is_zombie())
            //                     map[j] += "Z";

            //                 if (model->get_field().get_cell(i, j)->is_goblin())
            //                     map[j] += "G";

            //                 if (model->get_field().get_cell(i, j)->is_orc())
            //                     map[j] += "O";
            //             }

            //             if (model->get_field().get_cell(i, j)->is_item())
            //             {
            //                 if (model->get_field().get_cell(i, j)->is_med_kit())
            //                     map[j] += "M";

            //                 if (model->get_field().get_cell(i, j)->is_sword())
            //                     map[j] += "S";

            //                 if (model->get_field().get_cell(i, j)->is_armor())
            //                     map[j] += "A";
            //             }

            //             if (model->get_field().get_cell(i, j)->is_entrance() && !model->get_field().get_cell(i, j)->is_player())
            //                 map[j] += "~";

            //             if (model->get_field().get_cell(i, j)->is_exit() && !model->get_field().get_cell(i, j)->is_player())
            //                 map[j] += "#";

            //             if (!(model->get_field().get_cell(i, j)->is_player() || model->get_field().get_cell(i, j)->is_enemy() || model->get_field().get_cell(i, j)->is_item() || model->get_field().get_cell(i, j)->is_entrance() || model->get_field().get_cell(i, j)->is_exit()))
            //                map[j] += " ";
            //         }
            // }


            // nlohmann::json js;
            // js["map"] = map;
            // js["width"] = model->get_field().get_width();
            // js["height"] = model->get_field().get_height();
            // js["hp"] = model->get_player()->get_hp();
            // js["damage"] = model->get_player()->get_damage();
            // js["defense"] = model->get_player()->get_defense();
            // js["collisions"] = model->get_player()->get_collisions();

            // std::ofstream out("output.json");
            // out << js;
            // nlohmann::json j_new;
            // std::ifstream in("output.json");
            // in >> j_new;
            // //std::cout << j << std::endl;
            // //update_model(j_new);

            // delete model;
            // model = new Model(j_new);
            
            // controller = Controller::get_instance(model);

            model->enemies_move();

            bool сondition_collisions = rule_1->check(model->get_player()->get_collisions());
            bool сondition_picks = rule_2->check(model->get_enemies_killed_count()) && rule_3->check(model->get_used_items_count());

            if (!сondition_collisions)
                victory = false;

            if (model->game_over(сondition_collisions, сondition_picks))
            {
                if (!victory)
                {
                    view->clear();
                    good_end = false;
                    lose_report();
                }

                command = 0;
            }

            view->clear();

        } while (command);

        if (good_end)
            victory_report();
    }
    ~Presenter()
    {
        if (model) delete model;

        delete rule_1;
        delete rule_2;
        delete rule_3;
    }
};
