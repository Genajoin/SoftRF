/*
 * LK8EX1Helper.h
 * Copyright (C) 2019 Evgeny Istomin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LK8EX1HELPER_H
#define LK8EX1HELPER_H

#include "SoftRF.h"
#define LK8EX1_BUFFER_SIZE    128
enum
{
	LK8EX1_OFF,
	LK8EX1_UART,
	LK8EX1_UDP,
	LK8EX1_TCP,
	LK8EX1_BLUETOOTH
};

void LK8EX1_Export(void);

#endif /* LK8EX1HELPER_H */