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
#include <ncurses.h>

#include <note.h>

class Play_Screen{
    rect_struct shape;
    std::deque<Note>* notes;
    WINDOW* window;
    const char letters[12] = {
        'a', 'w', 's', 'e', 'd', 'f',
        't', 'g', 'y', 'h', 'u', 'j'
    };

    void refresh_screen(std::string score);

public:
    Play_Screen(rect_struct r, WINDOW* w, std::deque<Note>* n);
    bool update(std::string score);
};