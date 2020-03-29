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


#ifndef ChronoP_hpp
#define ChronoP_hpp

#include <chrono>
#include <ctime>
#include <iostream>

class ChronoP {
  std::chrono::time_point<std::chrono::system_clock> start, end;

 public:
  void Start() { start = std::chrono::system_clock::now(); }
  void Stop() { end = std::chrono::system_clock::now(); }
  void Restart() { start = std::chrono::system_clock::now(); }

  int64_t ellapsed_second() {
    return std::chrono::duration_cast<std::chrono::seconds>(end - start)
        .count();
  }

  int64_t ellapsed_m_second() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
        .count();
  }
  
  int64_t ellapsed_u_second() {
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start)
        .count();
  }

  int64_t compute_granularity() {
    std::chrono::time_point<std::chrono::system_clock> tmp;
    std::chrono::time_point<std::chrono::system_clock> st =
        std::chrono::system_clock::now();
    while ((tmp = std::chrono::system_clock::now()) == st)
      ;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(tmp - st)
        .count();
  }
};


#endif /* ChronoP_hpp */
