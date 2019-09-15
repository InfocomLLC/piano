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

#include <note.h>

#include <ncurses.h>
#include <stdlib.h>
#include <cstdlib>

Note::Note(uint_fast16_t r, uint_fast16_t c, uint_fast32_t t, uint_fast32_t i_d, char l,
            std::string mfn){
    row = r;
    col = c;
    time = t;
    int_duration = i_d;
    str_duration = std::to_string(i_d);
    letter = l;
    MIDI_file_name = "../resources/"+mfn+".mid";
}

bool Note::update(uint_fast16_t miny, uint_fast16_t maxy){
    if((row+int_duration+1)==maxy)
        return false;

    mvaddch(row+int_duration, col, ACS_LLCORNER);
    mvaddch(row+int_duration, col+1, ACS_HLINE);
    mvaddch(row+int_duration, col+2, ACS_LRCORNER);

    mvvline(row, col,  ACS_VLINE, int_duration);
    mvvline(row, col+2, ACS_VLINE, int_duration);

    ++row;
    return true;
}

bool Note::play(char key_pressed) const{
    if(key_pressed != letter)
        return false;
    else{
        std::string bash_file = "../bash/play_MIDI ";
        std::string supress = " &>/dev/null";
        std::system((bash_file+MIDI_file_name+" "+str_duration+supress).c_str());
        clear(); refresh();
    }
    return true;
}