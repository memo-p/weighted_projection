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

#include <armadillo>

#include "basic/bucket.hpp"
#include "basic/bucket_filter.hpp"
#include "basic/condat.hpp"

namespace proj {

inline void project(datatype* y, datatype* x, int dimension, const double a) {
  ProjBF(y, x, dimension, a);
}

inline void project(arma::vec& y, arma::vec& x, const double a) {
  arma::vec yabs = arma::abs(y);
  arma::vec signY = arma::sign(y);
  project(yabs.memptr(), x.memptr(), yabs.n_elem, a);
  x %= signY;
}

} // namespace proj