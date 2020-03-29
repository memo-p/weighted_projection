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
 *
 * From the code of Laurent Condat: https://lcondat.github.io
 */

#pragma once

#include <float.h>
#include <math.h>

#include "DTB.hpp"

namespace proj {

inline void ProjC(const datatype* y, datatype* x, const int length,
                  const double a) {
  datatype* aux = new datatype[length];
  datatype* aux0 = aux;
  int auxlength = 1;
  int auxlengthold = -1;
  datatype tau = (*aux = *y) - a;
  int i = 1;
  int iter = 1;
  for (; i < length; i++)
    if (y[i] > tau) {
      if ((tau += ((aux[auxlength] = y[i]) - tau) /
                  (auxlength - auxlengthold)) <= y[i] - a) {
        tau = y[i] - a;
        auxlengthold = auxlength - 1;
      }
      auxlength++;
    }
  if (auxlengthold >= 0) {
    iter++;
    auxlength -= ++auxlengthold;
    aux += auxlengthold;
    while (--auxlengthold >= 0)
      if (aux0[auxlengthold] > tau)
        tau += ((*(--aux) = aux0[auxlengthold]) - tau) / (++auxlength);
  }
  do {
    iter++;
    auxlengthold = auxlength - 1;
    for (i = auxlength = 0; i <= auxlengthold; i++)
      if (aux[i] > tau)
        aux[auxlength++] = aux[i];
      else
        tau += (tau - aux[i]) / (auxlengthold - i + auxlength);
  } while (auxlength <= auxlengthold);

  for (i = 0; i < length; i++) x[i] = (y[i] > tau ? y[i] - tau : 0.0);
  delete[] aux0;
}

}  // namespace proj
