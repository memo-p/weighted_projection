#define CATCH_CONFIG_MAIN

#include <algorithm>
#include <armadillo>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

#include "catch.hpp"
#include "weighted/projection.hpp"

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
    r = arma::dot(w, x);
    REQUIRE(abs(r - a) < epsilon);

    proj::ProjWSplit(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w, x);
    REQUIRE(abs(r - a) < epsilon);

    proj::ProjWB(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w, x);
    REQUIRE(abs(r - a) < epsilon);

    proj::ProjWBF(y.memptr(), w.memptr(), x.memptr(), l, a);
    r = arma::dot(w, x);
    REQUIRE(abs(r - a) < epsilon);
  }
}

TEST_CASE("test projection in-place") {
  int l = 10000;
  double a = 1;
  double epsilon = 1e-7;
  double r;
  size_t rep = 100;
  for (size_t i = 0; i < rep; i++) {
    arma::vec w = arma::abs(arma::randn<arma::vec>(l));
    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjWSort(y.memptr(), w.memptr(), y.memptr(), l, a);
      r = arma::dot(w, y);
      REQUIRE(abs(r - a) < epsilon);
    }

    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjWSplit(y.memptr(), w.memptr(), y.memptr(), l, a);
      r = arma::dot(w, y);
      REQUIRE(abs(r - a) < epsilon);
    }

    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjWB(y.memptr(), w.memptr(), y.memptr(), l, a);
      r = arma::dot(w, y);
      REQUIRE(abs(r - a) < epsilon);
    }

    {
      arma::vec y = arma::abs(arma::randn<arma::vec>(l));
      proj::ProjWBF(y.memptr(), w.memptr(), y.memptr(), l, a);
      r = arma::dot(w, y);
      REQUIRE(abs(r - a) < epsilon);
    }
  }
}
