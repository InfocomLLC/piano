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

#include <string>

#include <rect_struct.h>

class Note{
    int_fast16_t row;
    uint_fast32_t col, time, int_duration;
    std::string str_duration;
    char letter;
    std::string MIDI_file_name;

public:
    Note(uint_fast16_t r, uint_fast16_t c, uint_fast32_t t, uint_fast32_t i_d, char l, std::string mfn);
    bool update(uint_fast16_t miny, uint_fast16_t maxy);
    bool starts_now(uint_fast32_t current_time) const {return time==current_time;}
    bool play(char key_pressed) const;
    bool operator<(const Note&n)const{return time>n.time;}
};