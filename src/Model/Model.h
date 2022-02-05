#include <string>
#include <vector>
#include "../Field/Field.h"
#include "../Player/Player.h"
#include "../Zombie/Zombie.h"
#include "../Goblin/Goblin.h"
#include "../Orc/Orc.h"
#include "../MedKit/MedKit.h"
#include "../Sword/Sword.h"
#include "../Armor/Armor.h"
#include "../Dependencies/json/nlohmann/json.hpp"

#pragma once

class Model
{
    Field board;

    Player actor;

    Zombie *zombies;
    int zombies_count;

    Goblin *goblins;
    int goblins_count;

    Orc *orcs;
    int orcs_count;

    MedKit *med_kits;
    int med_kits_count;

    Sword *swords;
    int swords_count;

    Armor *armor;
    int armor_count;

    void destroy();

    void pick_item(int x, int y);

    bool pick_enemy(int x, int y);

public:
    Model();

    Model(const Model &other);

    Model(Model &&other);

    nlohmann::json get_json_copy();

    void set_json_copy(nlohmann::json js);

    Model &operator=(const Model &other);

    Model &operator=(Model &&other);

    int get_enemies_count();

    int get_enemies_killed_count();

    int get_items_count();

    int get_used_items_count();

    Field &get_field();

    void enemies_move();

    Player *get_player();

    std::string get_player_info();

    bool down();

    bool left();

    bool right();

    bool up();

    bool game_over(bool сondition_collisions, bool сondition_picks);

    friend bool operator==(const Model &model_1, const Model &model_2);

    friend bool operator!=(const Model &model_1, const Model &model_2);

    ~Model();

    friend class Logger;
};
