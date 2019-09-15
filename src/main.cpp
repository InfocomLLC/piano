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

#include <cstdio>
#include <cinttypes>
#include <stdint.h>

#include <game.h>

int main(int argc, char** argv){

    if(argc<2){
        fprintf(stderr,"usage %s full/path/to/file/to/play  \n", argv[0]);
        return(1);
    }

    Game game;
    game.run(argv[1]);

    return 0;
}