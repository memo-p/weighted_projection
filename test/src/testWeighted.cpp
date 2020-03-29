#define CATCH_CONFIG_MAIN

#include <algorithm>
#include <armadillo>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include "weighted/projection.hpp"
#include "catch.hpp"

TEST_CASE("test projection 1") {
  int l = 100000;
  double a = 1;
  double epsilon = 1e-7;
  double r;
  size_t rep = 100;
  for (size_t i = 0; i < rep; i++) {
    arma::vec y = arma::abs(arma::randn<arma::vec>(l));
    arma::vec x = arma::zeros<arma::vec>(l);
    arma::vec w = arma::abs(arma::randn<arma::vec>(l));

    proj::ProjWSort(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w,x);
    REQUIRE(abs(r - a) < epsilon);

    proj::ProjWSplit(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w,x);
    REQUIRE(abs(r - a) < epsilon);

    proj::ProjWB(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w,x);
    REQUIRE(abs(r - a) < epsilon);

    proj::ProjWBF(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w,x);
    REQUIRE(abs(r - a) < epsilon);

  }
}
