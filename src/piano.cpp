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

#include <game.h>

#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <regex>

#define COUNTDOWN_WAIT 0.3*1000000

void Game::config_window(){
    window = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    keypad(window, true);
    nodelay(window, true);
    curs_set(0);
}

void Game::config_play_screen(){
    uint_fast16_t maxx, maxy;
    getmaxyx(window, maxy, maxx);
    rect_struct r;
    r.start_row=0, r.start_col=0;
    r.height=maxy, r.width=maxx;
    screen = new Play_Screen(r, window, &current_notes);
}

void Game::config_maps(){
    duration_map['w'] = 4;
    duration_map['h'] = 2;
    duration_map['q'] = 1;

    uint_fast16_t start_col = 1;
    uint_fast16_t step = 4;
    note_map["c"] = {start_col,'a'};        note_map["c#"] = {start_col+step*1,'w'};
    note_map["d"] = {start_col+step*2,'s'}; note_map["d#"] = {start_col+step*3,'e'};
    note_map["e"] = {start_col+step*4,'d'};
    note_map["f"] = {start_col+step*5,'f'}; note_map["f#"] = {start_col+step*6,'t'};
    note_map["g"] = {start_col+step*7,'g'}; note_map["g#"] = {start_col+step*8,'y'};
    note_map["a"] = {start_col+step*9,'h'}; note_map["a#"] = {start_col+step*10,'u'};
    note_map["b"] = {start_col+step*11,'j'};
}

void Game::print_file_format(uint_fast32_t line_index){
    printw("Wrong format at line %lu\n", line_index);
    printw("Correct format is note duration\n");
    printw("Notes are written from A to G and from octave 2 to 5\n");
    printw("sharp notation is written as '#' and flat as 'b'\n");
    printw("Rest notation is written as 'rest'\n");
    printw("Available durations: (w)hole - (h)alf - (q)uarter - (e)ighth'\n");
}

bool Game::parse_line(std::string line, uint_fast32_t line_index, uint_fast32_t&running_time){
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    std::istringstream iss_line(line);
    std::vector<std::string> words{std::istream_iterator<std::string>{iss_line},
                    std::istream_iterator<std::string>{}};

    std::regex note_regex("([a-g](#|b|)[2-5])|(rest)");
    std::regex duration_regex("(w)|(h)|(q)|(e)");
    if(words.size()<2 || !std::regex_match(words[0], note_regex) ||
        !std::regex_match(words[1], duration_regex)){
        print_file_format(line_index);
        return false;
    }

    uint_fast8_t duration = duration_map[words[1][0]];
    if(words[0]!="rest"){
        note_pair npair =  note_map[words[0].substr(0, words[0].length()-1)];
        remaining_notes.push(Note(-duration, npair.col, running_time, duration, npair.letter,
                                    words[0]));
    }
    running_time += duration;
    return true;
}

bool Game::get_notes_from_file(std::string file_path){
    std::ifstream song_file(file_path.c_str());
    // TODO: add check

    std::string line;
    uint_fast32_t running_time = 0;
    uint_fast32_t line_index = 1;
    while (std::getline(song_file, line))
        if(!parse_line(line, line_index++, running_time))
            return false;
    return true;
}

void Game::pause_game(){
    nodelay(window, false);
    while (getch()!='p');
    nodelay(window, true);
}

Game::Game(){
    config_window();
    config_play_screen();
    config_maps();
    current_time = 0;
    score = 0;
    time_step = 0.4*1000000;
}

Game::~Game(){
    delete screen;
}

void Game::welcome_screen(){
    printw("%c Press 'p' at anytime to pause/resume.\n", ACS_BULLET);
    printw("%c Press Esc at anytime to quit.\n", ACS_BULLET);
    printw("%c Press any key to start.\n", ACS_BULLET);
    nodelay(window, false);
    int ch = getch();
    nodelay(window, true);

    clear();
    refresh();
    uint_fast16_t maxx, maxy;
    getmaxyx(window, maxy, maxx);
    for(int i=3;i>=1;--i){
        mvaddch(maxy/2, maxx/2, std::to_string(i)[0]);
        refresh();
        usleep(COUNTDOWN_WAIT);
    }
    clear();
    refresh();
}

void Game::print_final_score(uint_fast32_t total_score){
    clear();
    refresh();
    fprintf(stdout, "Score = %lu/%lu \n", score,total_score);
    nodelay(window, false);
    getch();
    endwin();
}

void Game::run(std::string file_path){
    if(!get_notes_from_file(file_path)){
        print_final_score(0);
        return;
    }
    welcome_screen();
    int user_input;
    uint_fast32_t total_score = remaining_notes.size();
    while(!remaining_notes.empty()||!current_notes.empty()){
        user_input = wgetch(window);
        if(user_input != ERR){
            if(user_input == 'p') pause_game();
            else if(user_input == 27){
                print_final_score(total_score);
                return;
            }
            else{
                if(current_notes.front().play(user_input))
                    ++score;
                current_notes.pop_front();
            }
        }
        screen->update(std::to_string(score));
        if(remaining_notes.top().starts_now(current_time)){
            current_notes.push_back(remaining_notes.top());
            remaining_notes.pop();
        }
        ++current_time;
        usleep(time_step);
    }
    print_final_score(total_score);
}