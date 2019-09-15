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

#include <play_screen.h>

#include <stdlib.h>

Play_Screen::Play_Screen(rect_struct r, WINDOW* w, std::deque<Note>* n){
    shape = r;
    window = w;
    notes = n;
}

void Play_Screen::refresh_screen(std::string score){
    attron(A_BOLD);
    box(window, 0, 0);
    mvwhline(window, shape.start_row+2 , shape.start_col+1,  ACS_HLINE, shape.width-2);
    for(int i=0;i<12;++i){
        mvaddch(shape.start_row+1, (4*i), ACS_VLINE);
        mvaddch(shape.start_row+1, (4*i)+1, ' ');
        mvaddch(shape.start_row+1, (4*i)+2, letters[i]);
        mvaddch(shape.start_row+1, (2*i)+3, ' ');
        mvaddch(shape.start_row+1, (4*i)+4, ACS_VLINE);
    }
    printw("  Score = %s", score.c_str());
    attroff(A_BOLD);
    refresh();
}

bool Play_Screen::update(std::string score){
    werase(window);
    for(std::deque<Note>::iterator note = (*notes).begin(); note!=(*notes).end(); ++note)
        if(!note->update(shape.start_row+2, shape.start_row+shape.height))
            notes->pop_front();
    refresh_screen(score);
    return true;
}