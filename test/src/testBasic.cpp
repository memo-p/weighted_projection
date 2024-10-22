#define CATCH_CONFIG_MAIN

#include <algorithm>
#include <armadillo>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

#include "basic/projection.hpp"
#include "catch.hpp"

TEST_CASE("test projection 1") {
  std::vector<int> dims = {100, 1000, 100000};
  std::vector<int> as = {1,  8, 16, 32};
  double epsilon = 1e-7;
  double r;
  size_t rep = 10;
  for (auto &&l : dims) {
    for (auto &&a : as) {
      for (size_t i = 0; i < rep; i++) {
        arma::vec y = arma::abs(arma::randn<arma::vec>(l));
        arma::vec x = arma::zeros<arma::vec>(l);

        proj::ProjC(y.memptr(), x.memptr(), l, a);
        r = arma::sum(x);
        REQUIRE(abs(r - a) < epsilon);

        proj::ProjB(y.memptr(), x.memptr(), l, a);
        r = arma::sum(x);
        REQUIRE(abs(r - a) < epsilon);

        proj::ProjBF(y.memptr(), x.memptr(), l, a);
        r = arma::sum(x);
        REQUIRE(abs(r - a) < epsilon);
      }
    }
  }
}

TEST_CASE("test projection in-place") {
  int l = 10000;
  double a = 1;
  double epsilon = 1e-7;
  double r;
  size_t rep = 100;
  for (size_t i = 0; i < rep; i++) {
    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjC(y.memptr(), y.memptr(), l, a);
      r = arma::sum(y);
      REQUIRE(abs(r - a) < epsilon);
    }
    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjB(y.memptr(), y.memptr(), l, a);
      r = arma::sum(y);
      REQUIRE(abs(r - a) < epsilon);
    }
    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjBF(y.memptr(), y.memptr(), l, a);
      r = arma::sum(y);
      REQUIRE(abs(r - a) < epsilon);
    }
  }
}
