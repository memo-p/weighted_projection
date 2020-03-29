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
 */
#pragma once

#include <numeric>
#include <vector>
#include <math.h>

inline std::pair<double,double> MeanAndStdev(std::vector<int>& v) {
  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double mean = sum / v.size();

  double sqr_sum = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
  double stdev = std::sqrt(sqr_sum / v.size() - mean * mean);
  return {mean, stdev};
}