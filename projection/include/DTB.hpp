/*
 * Copyright (C) 2020 Guillaume Perez
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

namespace proj {

#ifndef USE_32_BITS_

typedef double datatype;
#define DATASIZE 8

#else

typedef float datatype;
#define DATASIZE 4

#endif

union DtB {
  datatype val;
  unsigned char byte[sizeof(datatype)];
};
typedef union DtB Dtb;

#define KahanSum(s, v, c, t, y) \
  y = v - c;                    \
  t = s + y;                    \
  c = (t - s) - y;              \
  s = t;
#define KahanSumDel(s, v, c, t, y) \
  y = v + c;                       \
  t = s - y;                       \
  c = (t - s) + y;                 \
  s = t;

}  // namespace proj
