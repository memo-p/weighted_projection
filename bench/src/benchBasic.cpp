#include <armadillo>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "ChronoP.hpp"

#include "basic/projection.hpp"
#include "utils.hpp"

int main(int, char **) {
  std::vector<int> dims = {1000,    100000,  300000,  500000,  800000,
                           1000000, 3000000, 5000000, 7000000, 10000000};
  std::vector<int> as = {1, 2, 4, 8, 16};
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> times_c;
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> times_b;
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> times_bf;
  size_t rep = 10;
  ChronoP projc;
  ChronoP projb;
  ChronoP projbf;
  for (auto &&d : dims) {
    for (auto &&a : as) {
      for (size_t i = 0; i < rep; i++) {
        arma::vec y = arma::abs(arma::randn<arma::vec>(d));
        arma::vec x = arma::zeros<arma::vec>(d);

        projc.Start();
        proj::ProjC(y.memptr(), x.memptr(), d, a);
        projc.Stop();

        projbf.Start();
        proj::ProjBF(y.memptr(), x.memptr(), d, a);
        projbf.Stop();

        projb.Start();
        proj::ProjB(y.memptr(), x.memptr(), d, a);
        projb.Stop();

        times_c[d][a].push_back(projc.ellapsed_u_second());
        times_b[d][a].push_back(projb.ellapsed_u_second());
        times_bf[d][a].push_back(projbf.ellapsed_u_second());
      }
    }
  }
  for (auto &&entry1 : times_c) {
    int d = entry1.first;
    for (auto &&entry2 : times_c[d]) {
      int a = entry2.first;
      auto pc = MeanAndStdev(times_c[d][a]);
      auto pb = MeanAndStdev(times_b[d][a]);
      auto pbf = MeanAndStdev(times_bf[d][a]);
      std::cout << d << ";";
      std::cout << a << ";";
      std::cout << pc.first << ";";
      std::cout << pb.first << ";";
      std::cout << pbf.first << ";";
      std::cout << pc.second << ";";
      std::cout << pb.second << ";";
      std::cout << pbf.second << ";";
      std::cout << std::endl;
    }
  }

  return 0;
}
