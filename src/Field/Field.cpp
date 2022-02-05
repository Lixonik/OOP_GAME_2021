#include "Field.h"

void Field ::destroy()
{
    for (int i = 0; i < width; i++)
        delete[] arr_cell[i];

    delete[] arr_cell;
}

void Field ::walling()
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            arr_cell[i][j].set_wall();
}

void Field ::dfs(Cell **grid, int i, int j)
{
    if (i < 0 || i >= width || j < 0 || j >= height || !grid[i][j].is_passability())
        return;

    grid[i][j].set_wall();

    dfs(grid, i + 1, j);
    dfs(grid, i - 1, j);
    dfs(grid, i, j + 1);
    dfs(grid, i, j - 1);
}

void Field ::delete_deadblocks(int x_0, int y_0)
{
    Cell **grid = new Cell *[width];

    for (int i = 0; i < width; i++)
        grid[i] = new Cell[height];

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            grid[i][j] = arr_cell[i][j];

    dfs(grid, x_0, y_0);

    for (int i = 1; i < width - 1; i++)
        for (int j = 1; j < height - 1; j++)
            if (grid[i][j].is_passability())
                for (int x = x_0; x != i; x_0 < i ? x++ : x--)
                    for (int y = y_0; y != j; y_0 < j ? y++ : y--)
                        if (x == x_0 || y == j)
                            arr_cell[x][y].set_passability();

    for (int i = 0; i < width; i++)
        delete[] grid[i];

    delete[] grid;
}

void Field ::maze_generating()
{
    int x = randomcity.generate(0, (width - 1) / 2) * 2 + 1;
    int y = randomcity.generate(0, (height - 1) / 2) * 2 + 1;
    arr_cell[x][y].set_passability();
    arr_cell[x][y].set_maze_visit();

    std::vector<Cell> to_check;

    if (y - 2 >= 0)
        to_check.push_back(arr_cell[x][y - 2]);

    if (y + 2 < height)
        to_check.push_back(arr_cell[x][y + 2]);

    if (x - 2 >= 0)
        to_check.push_back(arr_cell[x - 2][y]);

    if (x + 2 < width)
        to_check.push_back(arr_cell[x + 2][y]);

    while (to_check.size() > 0)
    {
        int index = randomcity.generate(0, to_check.size() - 1);
        x = to_check[index].get_x();
        y = to_check[index].get_y();

        arr_cell[x][y].set_passability();
        arr_cell[x][y].set_maze_visit();

        to_check.erase(to_check.begin() + index);

        int direction = randomcity.generate(0, 3);

        switch (direction)
        {
        case 0:
            if (y - 2 >= 0 && arr_cell[x][y - 2].is_passability())
                arr_cell[x][y - 1].set_passability();
            break;
        case 1:
            if (y + 2 < height && arr_cell[x][y + 2].is_passability())
                arr_cell[x][y + 1].set_passability();
            break;
        case 2:
            if (x - 2 >= 0 && arr_cell[x - 2][y].is_passability())
                arr_cell[x - 1][y].set_passability();
            break;
        case 3:
            if (x + 2 < width && arr_cell[x + 2][y].is_passability())
                arr_cell[x + 1][y].set_passability();
            break;
        }

        if (y - 2 >= 0 && !arr_cell[x][y - 2].is_maze_visit() && !arr_cell[x][y - 2].is_passability())
            to_check.push_back(arr_cell[x][y - 2]);

        if (y + 2 < height && !arr_cell[x][y + 2].is_maze_visit() && !arr_cell[x][y + 2].is_passability())
            to_check.push_back(arr_cell[x][y + 2]);

        if (x - 2 >= 0 && !arr_cell[x - 2][y].is_maze_visit() && !arr_cell[x - 2][y].is_passability())
            to_check.push_back(arr_cell[x - 2][y]);

        if (x + 2 < width && !arr_cell[x + 2][y].is_maze_visit() && !arr_cell[x + 2][y].is_passability())
            to_check.push_back(arr_cell[x + 2][y]);
    }

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
                arr_cell[i][j].set_wall();

    std::vector<Cell> dead_ends;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            if (arr_cell[i][j].is_passability())
            {
                int neighbors = 0;

                if (j - 1 >= 0 && arr_cell[i][j - 1].is_passability())
                    neighbors++;

                if (j + 1 < height && arr_cell[i][j + 1].is_passability())
                    neighbors++;

                if (i - 1 >= 0 && arr_cell[i - 1][j].is_passability())
                    neighbors++;

                if (i + 1 < width && arr_cell[i + 1][j].is_passability())
                    neighbors++;

                if (neighbors <= 1)
                    dead_ends.push_back(arr_cell[i][j]);
            }
        }

    for (auto &cell : dead_ends)
        delete_deadblocks(cell.get_x(), cell.get_y());
}

void Field ::construct_entrance_exit()
{
    int x_min = 2, x_max = width - 2;

try_again:

    int x_entrance = randomcity.generate(x_min, x_max);
    x_exit = randomcity.generate(x_min, x_max);

    int y_min = 2, y_max = height - 2;

    int y_entrance = randomcity.generate(y_min, y_max);
    y_exit = randomcity.generate(y_min, y_max);

    if (x_max != 1 || y_max != 1)
        if (!(arr_cell[x_entrance][y_entrance].is_passability()) || !(arr_cell[x_exit][y_exit].is_passability()) || ((x_entrance == x_exit) && (y_entrance == y_exit)) || ((x_entrance - 1 == x_exit) && (y_entrance == y_exit)) || ((x_entrance + 1 == x_exit) && (y_entrance == y_exit)) || ((y_entrance - 1 == y_exit) && (x_entrance == x_exit)) || ((y_entrance + 1 == y_exit) && (x_entrance == x_exit)) || ((x_entrance + 1 == x_exit) && (y_entrance - 1 == y_exit)) || ((x_entrance + 1 == x_exit) && (y_entrance + 1 == y_exit)) || ((x_entrance - 1 == x_exit) && (y_entrance + 1 == y_exit)) || ((x_entrance - 1 == x_exit) && (y_entrance - 1 == y_exit)))
            goto try_again;

    arr_cell[x_entrance][y_entrance].set_entrance();
    arr_cell[x_exit][y_exit].set_exit();
}

void Field ::enemies_spawning()
{
    int enemies_counter = std::div((width - 2) * (height - 2), 32).quot;
    zombies_count = std::div(enemies_counter, 3).quot + std::div(enemies_counter, 3).rem;
    goblins_count = std::div(enemies_counter, 3).quot;
    orcs_count = std::div(enemies_counter, 3).quot;

    while (enemies_counter)
    {
        int u = randomcity.generate(1, width - 2), v = randomcity.generate(1, height - 2);

        if (arr_cell[u][v].is_passability() && !arr_cell[u][v].is_player() && !arr_cell[u][v].is_item() && !arr_cell[u][v].is_enemy() && !arr_cell[u][v].is_entrance() && !arr_cell[u][v].is_exit())
        {
            arr_cell[u][v].set_enemy();
            arr_cell[u][v].set_passability(false);
            enemies_counter--;
        }
    }
}

void Field ::items_spawning()
{
    int items_counter = std::div((width - 2) * (height - 2), 64).quot;
    med_kits_count = std::div(items_counter, 3).quot + std::div(items_counter, 3).rem;
    swords_count = std::div(items_counter, 3).quot;
    armor_count = std::div(items_counter, 3).quot;

    while (items_counter)
    {
        int u = randomcity.generate(1, width - 2), v = randomcity.generate(1, height - 2);

        if (arr_cell[u][v].is_passability() && !arr_cell[u][v].is_player() && !arr_cell[u][v].is_item() && !arr_cell[u][v].is_enemy() && !arr_cell[u][v].is_entrance() && !arr_cell[u][v].is_exit())
        {
            arr_cell[u][v].set_item();
            items_counter--;
        }
    }
}

void Field ::player_spawning()
{
    for (int i = 1; i < width - 1; i++)
        for (int j = 1; j < height - 1; j++)
            if (arr_cell[i][j].is_entrance())
            {
                if (arr_cell[i][j + 1].is_passability() && !arr_cell[i][j + 1].is_item())
                {
                    arr_cell[i][j + 1].set_player();

                    return;
                }

                if (arr_cell[i][j - 1].is_passability() && !arr_cell[i][j - 1].is_item())
                {
                    arr_cell[i][j - 1].set_player();

                    return;
                }

                if (arr_cell[i - 1][j].is_passability() && !arr_cell[i - 1][j].is_item())
                {
                    arr_cell[i - 1][j].set_player();

                    return;
                }

                if (arr_cell[i + 1][j].is_passability() && !arr_cell[i + 1][j].is_item())
                {
                    arr_cell[i + 1][j].set_player();

                    return;
                }
            }
}

Field ::Field()
{
    width = randomcity.generate(15, 25);
    height = randomcity.generate(15, 25);

    arr_cell = new Cell *[width];
    for (int i = 0; i < width; i++)
        arr_cell[i] = new Cell[height];

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            arr_cell[i][j].set_cell(i, j);

    walling();

    maze_generating();

    construct_entrance_exit();

    enemies_spawning();

    items_spawning();

    player_spawning();
}

Field::Field(std::vector<std::string> map, int width, int height) : width(width), height(height)
{
    if (width < 15 || height < 15 || map.size() != height)
        throw "The save file is not correct";

    for (int j = 0; j < height; j++)
        if (map[j].length() != width)
            throw "The save file is not correct";

    int x_player = 0, y_player = 0;
    int player_counter = 0, entrance_counter = 0, exit_counter = 0;

    arr_cell = new Cell *[width];
    for (int i = 0; i < width; i++)
        arr_cell[i] = new Cell[height];

    for (int j = 0; j < height; j++)
        for (int i = 0; i < width; i++)
        {
            switch (map[j][i])
            {
            case 'X':
                arr_cell[i][j].set_passability(false);
                break;
            case 'P':
                arr_cell[i][j].set_player();
                x_player = i, y_player = j;
                player_counter++;
                break;
            case 'Z':
                arr_cell[i][j].set_enemy();
                arr_cell[i][j].set_passability(false);
                arr_cell[i][j].set_zombie();
                zombies_count++;
                break;
            case 'G':
                arr_cell[i][j].set_enemy();
                arr_cell[i][j].set_passability(false);
                arr_cell[i][j].set_goblin();
                goblins_count++;
                break;
            case 'O':
                arr_cell[i][j].set_enemy();
                arr_cell[i][j].set_passability(false);
                arr_cell[i][j].set_orc();
                orcs_count++;
                break;
            case 'M':
                arr_cell[i][j].set_item();
                arr_cell[i][j].set_med_kit();
                med_kits_count++;
                break;
            case 'S':
                arr_cell[i][j].set_item();
                arr_cell[i][j].set_sword();
                swords_count++;
                break;
            case 'A':
                arr_cell[i][j].set_item();
                arr_cell[i][j].set_armor();
                armor_count++;
                break;
            case '~':
                arr_cell[i][j].set_entrance();
                entrance_counter++;
                break;
            case '#':
                arr_cell[i][j].set_exit();
                x_exit = i;
                y_exit = j;
                exit_counter++;
                break;
            case ' ':
                break;
            default:
                throw "The save file is not correct";
            }
        }
    if (!entrance_counter)
    {
        arr_cell[x_player][y_player].set_entrance();
        entrance_counter++;
    }
    if (!exit_counter)
    {
        arr_cell[x_player][y_player].set_exit();
        x_exit = x_player;
        y_exit = y_player;
        exit_counter++;
    }

    int enemies_counter = std::div((width - 2) * (height - 2), 32).quot;
    int zombies_counter = std::div(enemies_counter, 3).quot + std::div(enemies_counter, 3).rem;
    int goblins_counter = std::div(enemies_counter, 3).quot;
    int orcs_counter = std::div(enemies_counter, 3).quot;

    int items_counter = std::div((width - 2) * (height - 2), 64).quot;
    int med_kits_counter = std::div(items_counter, 3).quot + std::div(items_counter, 3).rem;
    int swords_counter = std::div(items_counter, 3).quot;
    int armor_counter = std::div(items_counter, 3).quot;

    if (zombies_count > zombies_counter || goblins_count > goblins_counter || orcs_count > orcs_counter)
        throw "The save file is not correct";

    if (med_kits_count > med_kits_counter || swords_count > swords_counter || armor_count > armor_counter)
        throw "The save file is not correct";

    if (player_counter != 1 || entrance_counter != 1 || exit_counter != 1)
        throw "The save file is not correct";
}

Field ::Field(const Field &other) : width(other.width), height(other.height)
{
    zombies_count = other.zombies_count;
    goblins_count = other.goblins_count;
    orcs_count = other.orcs_count;
    med_kits_count = other.med_kits_count;
    swords_count = other.swords_count;
    armor_count = other.armor_count;
    x_exit = other.x_exit;
    y_exit = other.y_exit;

    arr_cell = new Cell *[width];

    for (int i = 0; i < width; i++)
        arr_cell[i] = new Cell[height];

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            arr_cell[i][j] = other.arr_cell[i][j];
}

Field &Field::operator=(const Field &other)
{
    if (this != &other)
    {
        destroy();

        width = other.width;
        height = other.height;

        zombies_count = other.zombies_count;
        goblins_count = other.goblins_count;
        orcs_count = other.orcs_count;
        med_kits_count = other.med_kits_count;
        swords_count = other.swords_count;
        armor_count = other.armor_count;
        x_exit = other.x_exit;
        y_exit = other.y_exit;

        arr_cell = new Cell *[width];

        for (int i = 0; i < width; i++)
            arr_cell[i] = new Cell[height];

        for (int i = 0; i < width; i++)
            for (int j = 0; j < height; j++)
                arr_cell[i][j] = other.arr_cell[i][j];
    }

    return *this;
}

Field ::Field(Field &&other)
{
    std::swap(width, other.width);
    std::swap(height, other.height);
    std::swap(zombies_count, other.zombies_count);
    std::swap(goblins_count, other.goblins_count);
    std::swap(orcs_count, other.orcs_count);
    std::swap(med_kits_count, other.med_kits_count);
    std::swap(swords_count, other.swords_count);
    std::swap(armor_count, other.armor_count);
    std::swap(arr_cell, other.arr_cell);
    std::swap(x_exit, other.x_exit);
    std::swap(y_exit, other.y_exit);

    other.arr_cell = NULL;
}

Field &Field::operator=(Field &&other)
{
    if (this != &other)
    {
        std::swap(width, other.width);
        std::swap(height, other.height);
        std::swap(zombies_count, other.zombies_count);
        std::swap(goblins_count, other.goblins_count);
        std::swap(orcs_count, other.orcs_count);
        std::swap(med_kits_count, other.med_kits_count);
        std::swap(swords_count, other.swords_count);
        std::swap(armor_count, other.armor_count);
        std::swap(arr_cell, other.arr_cell);
        std::swap(x_exit, other.x_exit);
        std::swap(y_exit, other.y_exit);
    }

    return *this;
}

int Field ::get_width()
{
    return width;
}

int Field ::get_height()
{
    return height;
}

Cell *Field ::get_cell(int x, int y)
{
    return &arr_cell[x][y];
}

int Field ::get_x_exit()
{
    return x_exit;
}

int Field ::get_y_exit()
{
    return y_exit;
}

int Field ::get_zombies_count()
{
    return zombies_count;
}

void Field ::zombies_count_decrement()
{
    zombies_count--;
}

int Field ::get_goblins_count()
{
    return goblins_count;
}

void Field ::goblins_count_decrement()
{
    goblins_count--;
}

int Field ::get_orcs_count()
{
    return orcs_count;
}

void Field ::orcs_count_decrement()
{
    orcs_count--;
}

int Field ::get_med_kits_count()
{
    return med_kits_count;
}

void Field ::med_kits_count_decrement()
{
    med_kits_count--;
}

int Field ::get_swords_count()
{
    return swords_count;
}

void Field ::swords_count_decrement()
{
    swords_count--;
}

int Field ::get_armor_count()
{
    return armor_count;
}

void Field ::armor_count_decrement()
{
    armor_count--;
}

Field ::~Field()
{
    if (arr_cell)
        destroy();
}

std::ostream &operator<<(std::ostream &out, const Field &object)
{
    out << "FIELD INFO" << std::endl;
    out << "width = " << object.width << std::endl;
    out << "height = " << object.height << std::endl;

    for (int i = 0; i < object.width; i++)
        for (int j = 0; j < object.height; j++)
        {
            if (object.arr_cell[i][j].is_entrance())
                out << "entrance (" << i << ',' << j << ')' << std::endl;

            if (object.arr_cell[i][j].is_exit())
                out << "exit (" << i << ',' << j << ')' << std::endl;
        }
    std::cout << "666" << std::endl;

    for (int j = object.height - 1; j > -1; j--)
    {
        for (int i = 0; i < object.width; i++)
            if (!object.arr_cell[i][j].is_passability() && !object.arr_cell[i][j].is_enemy())
                out << "X";
            else
            {
                if (object.arr_cell[i][j].is_player())
                    out << "P";

                if (object.arr_cell[i][j].is_enemy())
                {
                    if (object.arr_cell[i][j].is_zombie())
                        out << "Z";

                    if (object.arr_cell[i][j].is_goblin())
                        out << "G";

                    if (object.arr_cell[i][j].is_orc())
                        out << "O";
                }

                if (object.arr_cell[i][j].is_item())
                {
                    if (object.arr_cell[i][j].is_med_kit())
                        out << "M";

                    if (object.arr_cell[i][j].is_sword())
                        out << "S";

                    if (object.arr_cell[i][j].is_armor())
                        out << "A";
                }

                if (object.arr_cell[i][j].is_entrance() && !object.arr_cell[i][j].is_player())
                    out << "~";

                if (object.arr_cell[i][j].is_exit() && !object.arr_cell[i][j].is_player())
                    out << "#";

                if (!(object.arr_cell[i][j].is_player() || object.arr_cell[i][j].is_enemy() || object.arr_cell[i][j].is_item() || object.arr_cell[i][j].is_entrance() || object.arr_cell[i][j].is_exit()))
                    out << " ";
            }

        out << std::endl;
    }

    return out;
}

bool operator==(const Field &field_1, const Field &field_2)
{
    if (field_1.width != field_2.width || field_1.height != field_2.height)
        return false;

    for (int i = 0; i < field_1.width; i++)
        for (int j = 0; j < field_1.height; j++)
            if (field_1.arr_cell[i][j] != field_2.arr_cell[i][j])
                return false;

    return true;
}

bool operator!=(const Field &field_1, const Field &field_2)
{
    return !(field_1 == field_2);
}
