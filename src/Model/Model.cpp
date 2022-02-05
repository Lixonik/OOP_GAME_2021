#include "Model.h"

void Model::destroy()
{
    if (zombies)
        delete[] zombies;

    if (goblins)
        delete[] goblins;

    if (orcs)
        delete[] orcs;

    if (med_kits)
        delete[] med_kits;

    if (swords)
        delete[] swords;

    if (armor)
        delete[] armor;
}

Model ::Model()
{
    actor.generate(&board);

    zombies_count = board.get_zombies_count();
    goblins_count = board.get_goblins_count();
    orcs_count = board.get_orcs_count();
    med_kits_count = board.get_med_kits_count();
    swords_count = board.get_swords_count();
    armor_count = board.get_armor_count();

    zombies = new Zombie[zombies_count];
    for (int i = 0; i < zombies_count; i++)
        zombies[i].generate(&board);

    goblins = new Goblin[goblins_count];
    for (int i = 0; i < goblins_count; i++)
        goblins[i].generate(&board);

    orcs = new Orc[orcs_count];
    for (int i = 0; i < orcs_count; i++)
        orcs[i].generate(&board);

    med_kits = new MedKit[med_kits_count];
    for (int i = 0; i < med_kits_count; i++)
        med_kits[i].generate(&board);

    swords = new Sword[swords_count];
    for (int i = 0; i < swords_count; i++)
        swords[i].generate(&board);

    armor = new Armor[armor_count];
    for (int i = 0; i < armor_count; i++)
        armor[i].generate(&board);
}

Model ::Model(const Model &other) : zombies_count(other.zombies_count), goblins_count(other.goblins_count), orcs_count(other.orcs_count), med_kits_count(other.med_kits_count), swords_count(other.swords_count), armor_count(other.armor_count), board(other.board), actor(other.actor)
{
    zombies = new Zombie[zombies_count];
    for (int i = 0; i < zombies_count; i++)
        zombies[i] = other.zombies[i];

    goblins = new Goblin[goblins_count];
    for (int i = 0; i < goblins_count; i++)
        goblins[i] = other.goblins[i];

    orcs = new Orc[orcs_count];
    for (int i = 0; i < orcs_count; i++)
        orcs[i] = other.orcs[i];

    med_kits = new MedKit[med_kits_count];
    for (int i = 0; i < med_kits_count; i++)
        med_kits[i] = other.med_kits[i];

    swords = new Sword[swords_count];
    for (int i = 0; i < swords_count; i++)
        swords[i] = other.swords[i];

    armor = new Armor[armor_count];
    for (int i = 0; i < armor_count; i++)
        armor[i] = other.armor[i];
}

nlohmann::json Model::get_json_copy()
{
    std::vector<std::string> map;
    map.resize(board.get_height());

    for (int j = board.get_height() - 1; j > -1; j--)
    {
        for (int i = 0; i < board.get_width(); i++)
            if (!board.get_cell(i, j)->is_passability() && !board.get_cell(i, j)->is_enemy())
                map[j] += "X";
            else
            {
                if (board.get_cell(i, j)->is_player())
                    map[j] += "P";

                if (board.get_cell(i, j)->is_enemy())
                {
                    if (board.get_cell(i, j)->is_zombie())
                        map[j] += "Z";

                    if (board.get_cell(i, j)->is_goblin())
                        map[j] += "G";

                    if (board.get_cell(i, j)->is_orc())
                        map[j] += "O";
                }

                if (board.get_cell(i, j)->is_item())
                {
                    if (board.get_cell(i, j)->is_med_kit())
                        map[j] += "M";

                    if (board.get_cell(i, j)->is_sword())
                        map[j] += "S";

                    if (board.get_cell(i, j)->is_armor())
                        map[j] += "A";
                }

                if (board.get_cell(i, j)->is_entrance() && !board.get_cell(i, j)->is_player())
                    map[j] += "~";

                if (board.get_cell(i, j)->is_exit() && !board.get_cell(i, j)->is_player())
                    map[j] += "#";

                if (!(board.get_cell(i, j)->is_player() || board.get_cell(i, j)->is_enemy() || board.get_cell(i, j)->is_item() || board.get_cell(i, j)->is_entrance() || board.get_cell(i, j)->is_exit()))
                    map[j] += " ";
            }
    }

    nlohmann::json js;
    js["map"] = map;
    js["width"] = board.get_width();
    js["height"] = board.get_height();
    js["hp"] = actor.get_hp();
    js["damage"] = actor.get_damage();
    js["defense"] = actor.get_defense();
    js["collisions"] = actor.get_collisions();

    return js;
}

void Model::set_json_copy(nlohmann::json js)
{
    bool correct = true;

    try
    {
        if (js.count("map") == 0 || js.count("width") == 0 || js.count("height") == 0 || js.count("hp") == 0 || js.count("damage") == 0 || js.count("defense") == 0 || js.count("collisions") == 0)
            throw "The save file is not correct";
        else
        {
            Field field(js["map"].get<std::vector<std::string>>(), js["width"].get<int>(), js["height"].get<int>());
            Player player(js["hp"].get<int>(), js["damage"].get<int>(), js["defense"].get<int>(), js["collisions"].get<int>());
        }
    }
    catch (const char *message)
    {
        std::cerr << message << std::endl;
        correct = false;
        system("pause");
    }

    if (correct)
    {
        destroy();

        board = Field(js["map"].get<std::vector<std::string>>(), js["width"].get<int>(), js["height"].get<int>());
        actor = Player(js["hp"].get<int>(), js["damage"].get<int>(), js["defense"].get<int>(), js["collisions"].get<int>());
        actor.generate(&board);

        zombies_count = board.get_zombies_count();
        goblins_count = board.get_goblins_count();
        orcs_count = board.get_orcs_count();
        med_kits_count = board.get_med_kits_count();
        swords_count = board.get_swords_count();
        armor_count = board.get_armor_count();

        zombies = new Zombie[zombies_count];
        for (int i = 0; i < zombies_count; i++)
            zombies[i].generate(&board);

        goblins = new Goblin[goblins_count];
        for (int i = 0; i < goblins_count; i++)
            goblins[i].generate(&board);

        orcs = new Orc[orcs_count];
        for (int i = 0; i < orcs_count; i++)
            orcs[i].generate(&board);

        med_kits = new MedKit[med_kits_count];
        for (int i = 0; i < med_kits_count; i++)
            med_kits[i].generate(&board);

        swords = new Sword[swords_count];
        for (int i = 0; i < swords_count; i++)
            swords[i].generate(&board);

        armor = new Armor[armor_count];
        for (int i = 0; i < armor_count; i++)
            armor[i].generate(&board);
    }
}

Model &Model::operator=(const Model &other)
{
    if (this != &other)
    {
        destroy();

        board = other.board;

        actor = other.actor;

        zombies_count = other.zombies_count;
        goblins_count = other.goblins_count;
        orcs_count = other.orcs_count;
        med_kits_count = other.med_kits_count;
        swords_count = other.swords_count;
        armor_count = other.armor_count;

        zombies = new Zombie[zombies_count];
        for (int i = 0; i < zombies_count; i++)
            zombies[i] = other.zombies[i];

        goblins = new Goblin[goblins_count];
        for (int i = 0; i < goblins_count; i++)
            goblins[i] = other.goblins[i];

        orcs = new Orc[orcs_count];
        for (int i = 0; i < orcs_count; i++)
            orcs[i] = other.orcs[i];

        med_kits = new MedKit[med_kits_count];
        for (int i = 0; i < med_kits_count; i++)
            med_kits[i] = other.med_kits[i];

        swords = new Sword[swords_count];
        for (int i = 0; i < swords_count; i++)
            swords[i] = other.swords[i];

        armor = new Armor[armor_count];
        for (int i = 0; i < armor_count; i++)
            armor[i] = other.armor[i];
    }

    return *this;
}

Model ::Model(Model &&other)
{
    std::swap(board, other.board);
    std::swap(actor, other.actor);
    actor.generate(&board);

    std::swap(zombies_count, other.zombies_count);
    std::swap(goblins_count, other.goblins_count);
    std::swap(orcs_count, other.orcs_count);
    std::swap(med_kits_count, other.med_kits_count);
    std::swap(swords_count, other.swords_count);
    std::swap(armor_count, other.armor_count);

    std::swap(zombies, other.zombies);
    std::swap(goblins, other.goblins);
    std::swap(orcs, other.orcs);
    std::swap(med_kits, other.med_kits);
    std::swap(swords, other.swords);
    std::swap(armor, other.armor);
}

Model &Model::operator=(Model &&other)
{
    if (this != &other)
    {
        std::swap(board, other.board);
        std::swap(actor, other.actor);
        actor.generate(&board);

        std::swap(zombies_count, other.zombies_count);
        std::swap(goblins_count, other.goblins_count);
        std::swap(orcs_count, other.orcs_count);
        std::swap(med_kits_count, other.med_kits_count);
        std::swap(swords_count, other.swords_count);
        std::swap(armor_count, other.armor_count);

        std::swap(zombies, other.zombies);
        std::swap(goblins, other.goblins);
        std::swap(orcs, other.orcs);
        std::swap(med_kits, other.med_kits);
        std::swap(swords, other.swords);
        std::swap(armor, other.armor);
    }

    return *this;
}

int Model::get_enemies_count()
{
    return zombies_count + goblins_count + orcs_count;
}

int Model::get_enemies_killed_count()
{
    int enemies_life_count = 0;

    for (int i = 0; i < zombies_count; i++)
        if (zombies[i].is_life())
            enemies_life_count++;

    for (int i = 0; i < goblins_count; i++)
        if (goblins[i].is_life())
            enemies_life_count++;

    for (int i = 0; i < orcs_count; i++)
        if (orcs[i].is_life())
            enemies_life_count++;

    return get_enemies_count() - enemies_life_count;
}

int Model::get_items_count()
{
    return med_kits_count + swords_count + armor_count;
}

int Model::get_used_items_count()
{
    int used_items = 0;

    for (int i = 0; i < med_kits_count; i++)
        if (med_kits[i].is_used())
            used_items++;

    for (int i = 0; i < swords_count; i++)
        if (swords[i].is_used())
            used_items++;

    for (int i = 0; i < armor_count; i++)
        if (armor[i].is_used())
            used_items++;

    return used_items;
}

Field &Model::get_field()
{
    return board;
}

void Model::enemies_move()
{
    for (int i = 0; i < zombies_count; i++)
        zombies[i].move();

    for (int i = 0; i < goblins_count; i++)
        goblins[i].move();

    for (int i = 0; i < orcs_count; i++)
        orcs[i].move();
}

Player *Model::get_player()
{
    return &actor;
}

std::string Model ::get_player_info()
{
    return "PLAYER INFO\nhp: " + std::to_string(actor.get_hp()) + " / 200" + "\ndefense: " + std::to_string(actor.get_defense()) + "\ndamage: " + std::to_string(actor.get_damage()) + "\n";
}

void Model::pick_item(int x, int y)
{
    for (int i = 0; i < med_kits_count; i++)
        if (med_kits[i].get_x() == x && med_kits[i].get_y() == y)
            actor.item_interaction(med_kits[i]);

    for (int i = 0; i < swords_count; i++)
        if (swords[i].get_x() == x && swords[i].get_y() == y)
            actor.item_interaction(swords[i]);

    for (int i = 0; i < armor_count; i++)
        if (armor[i].get_x() == x && armor[i].get_y() == y)
            actor.item_interaction(armor[i]);
}

bool Model ::pick_enemy(int x, int y)
{
    for (int i = 0; i < zombies_count; i++)
        if (zombies[i].get_x() == x && zombies[i].get_y() == y)
            return actor.battle(zombies[i]);

    for (int i = 0; i < goblins_count; i++)
        if (goblins[i].get_x() == x && goblins[i].get_y() == y)
            return actor.battle(goblins[i]);

    for (int i = 0; i < orcs_count; i++)
        if (orcs[i].get_x() == x && orcs[i].get_y() == y)
            return actor.battle(orcs[i]);

    return true;
}

bool Model ::down()
{
    bool victory = true;

    victory = pick_enemy(actor.get_x(), actor.get_y() - 1);
    pick_item(actor.get_x(), actor.get_y() - 1);
    actor.move_back_y();

    return victory;
}

bool Model ::left()
{
    bool victory = true;

    victory = pick_enemy(actor.get_x() - 1, actor.get_y());
    pick_item(actor.get_x() - 1, actor.get_y());
    actor.move_back_x();

    return victory;
}

bool Model ::right()
{
    bool victory = true;

    victory = pick_enemy(actor.get_x() + 1, actor.get_y());
    pick_item(actor.get_x() + 1, actor.get_y());
    actor.move_up_x();

    return victory;
}

bool Model ::up()
{
    bool victory = true;

    victory = pick_enemy(actor.get_x(), actor.get_y() + 1);
    pick_item(actor.get_x(), actor.get_y() + 1);
    actor.move_up_y();

    return victory;
}

bool Model::game_over(bool сondition_collisions, bool сondition_picks)
{
    return !сondition_collisions || (actor.get_hp() <= 0 || (actor.get_x() == board.get_x_exit() && actor.get_y() == board.get_y_exit() && сondition_picks));
}

bool operator==(const Model &model_1, const Model &model_2)
{
    if (model_1.board != model_2.board)
        return false;

    if (model_1.actor != model_2.actor)
        return false;

    if (model_1.zombies_count != model_2.zombies_count || model_1.goblins_count != model_2.goblins_count || model_1.orcs_count != model_2.orcs_count)
        return false;

    for (int i = 0; i < model_1.zombies_count; i++)
        if (model_1.zombies[i] != model_2.zombies[i])
            return false;

    for (int i = 0; i < model_1.goblins_count; i++)
        if (model_1.goblins[i] != model_2.goblins[i])
            return false;

    for (int i = 0; i < model_1.orcs_count; i++)
        if (model_1.orcs[i] != model_2.orcs[i])
            return false;

    if (model_1.med_kits_count != model_2.med_kits_count || model_1.swords_count != model_2.swords_count || model_1.armor_count != model_2.armor_count)
        return false;

    for (int i = 0; i < model_1.med_kits_count; i++)
        if (model_1.med_kits[i] != model_2.med_kits[i])
            return false;

    for (int i = 0; i < model_1.swords_count; i++)
        if (model_1.swords[i] != model_2.swords[i])
            return false;

    for (int i = 0; i < model_1.armor_count; i++)
        if (model_1.armor[i] != model_2.armor[i])
            return false;

    return true;
}

bool operator!=(Model &model_1, Model &model_2)
{
    return !(model_1 == model_2);
}

Model ::~Model()
{
    destroy();
}
