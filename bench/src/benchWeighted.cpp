#include <armadillo>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "ChronoP.hpp"

#include "utils.hpp"
#include "weighted/projection.hpp"

int main(int, char **) {
  // std::vector<int> dims = {1000,    100000,  300000,  500000,  800000,
  //                          1000000, 3000000, 5000000, 7000000, 10000000};
  std::vector<int> dims = {1000, 100000, 500000, 1000000, 5000000, 10000000};
  // std::vector<int> as = {1, 2, 4, 8, 16, 32};
  std::vector<int> as = {1, 2, 4, 16};
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> times_sort;
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>>
      times_split;
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> times_b;
  std::unordered_map<int, std::unordered_map<int, std::vector<int>>> times_bf;
  size_t rep = 10;
  ChronoP proj_sort;
  ChronoP proj_split;
  ChronoP projb;
  ChronoP projbf;
  for (auto &&d : dims) {
    for (auto &&a : as) {
      for (size_t i = 0; i < rep; i++) {
        arma::vec y = arma::abs(arma::randn<arma::vec>(d));
        arma::vec x = arma::zeros<arma::vec>(d);
        arma::vec w = arma::abs(arma::randn<arma::vec>(d));

        proj_sort.Start();
        // proj::ProjWSort(y.memptr(), w.memptr(), x.memptr(), d, a);
        proj_sort.Stop();

        proj_split.Start();
        proj::ProjWSplit(y.memptr(), w.memptr(), x.memptr(), d, a);
        proj_split.Stop();

        projbf.Start();
        proj::ProjWBF(y.memptr(), w.memptr(), x.memptr(), d, a);
        projbf.Stop();

        projb.Start();
        // proj::ProjWB(y.memptr(), w.memptr(), x.memptr(), d, a);
        projb.Stop();

        times_b[d][a].push_back(projb.ellapsed_u_second());
        times_bf[d][a].push_back(projbf.ellapsed_u_second());
        times_split[d][a].push_back(proj_split.ellapsed_u_second());
        times_sort[d][a].push_back(proj_sort.ellapsed_u_second());
      }
    }
  }
  for (auto &&entry1 : times_bf) {
    int d = entry1.first;
    for (auto &&entry2 : times_bf[d]) {
      int a = entry2.first;
      auto pso = MeanAndStdev(times_sort[d][a]);
      auto psp = MeanAndStdev(times_split[d][a]);
      auto pb = MeanAndStdev(times_b[d][a]);
      auto pbf = MeanAndStdev(times_bf[d][a]);
      std::cout << d << ";";
      std::cout << a << ";";
      std::cout << pso.first << ";";
      std::cout << psp.first << ";";
      std::cout << pbf.first << ";";
      std::cout << pb.first << ";";
      std::cout << pso.second << ";";
      std::cout << psp.second << ";";
      std::cout << pbf.second << ";";
      std::cout << pb.second << ";";
      std::cout << std::endl;
    }
  }

  return 0;
}
