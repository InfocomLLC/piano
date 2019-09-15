/*
Copyright (C) Infocom LLC

SPDX-License-Identifier: AGPL-3.0-or-later

This file is part of Piano.

Piano is free software: you can redistribute it and/or modify it under
the terms of the GNU Affero General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

Piano is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public
License for more details.

You should have received a copy of the GNU Affero General Public
License along with Piano. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <deque>
#include <queue>
#include <map>
#include <utility>
#include <ncurses.h>

#include <play_screen.h>

class Game{
    std::priority_queue<Note> remaining_notes;
    std::deque<Note> current_notes;
    WINDOW* window = NULL;
    Play_Screen* screen = NULL;
    uint_fast32_t current_time, time_step, score;

    struct note_pair{
        uint_fast16_t col;
        char letter;
    };
    std::map<std::string, note_pair> note_map;
    std::map<char, uint_fast8_t> duration_map;

    void config_window();
    void config_play_screen();
    void config_maps();
    void print_file_format(uint_fast32_t line_index);
    bool parse_line(std::string line, uint_fast32_t line_index, uint_fast32_t&running_time);
    bool get_notes_from_file(std::string file_path);
    void pause_game();
    void print_final_score(uint_fast32_t total_score);
    void welcome_screen();

public:

    Game();
    ~Game();
    void run(std::string file_path);
};