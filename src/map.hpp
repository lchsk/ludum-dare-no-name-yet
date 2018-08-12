#ifndef MAP_H
#define MAP_H

#include <cassert>
#include <iostream>

#include "player.hpp"
#include "resources.hpp"
#include "tile.hpp"
#include "tile_config.hpp"
#include "unit.hpp"

namespace ld {
using MapDefinition = std::array<std::array<unsigned, 13>, 10>;

const MapDefinition map_1 = {{
    {4, 4, 4, 0, 0, 0, 0, 4, 4, 4, 4, 4, 4},
    {0, 4, 4, 0, 0, 0, 4, 4, 4, 3, 4, 4, 4},
    {0, 1, 0, 0, 0, 1, 0, 3, 2, 2, 2, 3, 4},
    {0, 1, 1, 1, 0, 1, 0, 2, 3, 3, 2, 2, 4},
    {0, 1, 1, 1, 1, 1, 3, 3, 2, 3, 2, 2, 2},
    {0, 1, 1, 0, 0, 0, 3, 2, 2, 2, 3, 3, 3},
    {0, 0, 0, 0, 1, 0, 2, 3, 2, 2, 2, 3, 4},
    {0, 0, 1, 0, 1, 1, 2, 3, 2, 3, 2, 3, 4},
    {5, 0, 1, 0, 0, 0, 4, 4, 3, 3, 2, 3, 4},
    {4, 4, 0, 1, 0, 4, 4, 4, 3, 2, 2, 4, 4},

}};

namespace map_coords {
inline int px2tile_col(int x) {
    return static_cast<double>(x) / ld::config::get_screen_width() *
           ld::config::COLS;
}

inline int px2tile_row(int y) {
    return static_cast<double>(y) / ld::config::get_screen_height() *
           ld::config::ROWS;
}

inline int coords_to_tile_id(int tile_row, int tile_col) {
    return tile_row * ld::config::COLS + tile_col;
}

inline bool neighbor_tiles(const ld::Tile &selected_tile,
                           const ld::Tile *unit_tile) {
    const int row_diff = std::abs(selected_tile.row_ - unit_tile->row_);
    const int col_diff = std::abs(selected_tile.col_ - unit_tile->col_);

    return ((row_diff == 1 and col_diff == 0) or
            (row_diff == 0 and col_diff == 1));
}
};

class Map {
  public:
    Map(const ld::MapDefinition &map_definition,
        const std::shared_ptr<ld::Resources> &resources);

    void render(sf::RenderWindow &window) const;

    bool is_valid_move(const ld::Tile &selected_tile,
                       const ld::Tile *unit_tile) const;
    void add_new_unit(std::shared_ptr<ld::Player> &player,
                      ld::UnitType unit_type);

    void handle_left_mouse_click(const sf::Vector2i &pos);

  private:
    std::vector<ld::Tile> tiles;
    std::vector<std::shared_ptr<ld::Unit>> units;

    // MOVE OUT OF MAP
    sf::Sprite crosshair;

    std::shared_ptr<ld::Player> player_1_;
    std::shared_ptr<ld::Player> player_2_;

    std::shared_ptr<ld::Resources> resources;
};
}

#endif /* MAP_H */
