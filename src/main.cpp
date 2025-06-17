#include "dual.hpp"
#include "rosenbrock.hpp"
#include "toml.hpp"
#include <array>
#include <iostream>
#include <random>

typedef struct {
  int a;
  int b;
} rosenbrock_params;

typedef struct {
  double alpha;
  int epochs;
  int multi_trial_count;
} search_params;

typedef struct minimum_ctx_ {
  std::array<double, 2> x_vec;
  double f;
  int trial;

  void echo() {
    std::cout << "Minimal value:" << std::endl;
    std::cout << "\tf(x, y) = " << f << " occurred at:" << std::endl;
    std::cout << "\tx = " << x_vec[0] << std::endl;
    std::cout << "\ty = " << x_vec[1] << std::endl;
    std::cout << "\ttrial = " << trial << std::endl;
  }
} minimum_ctx;

void usage() {
  std::cout << "ad - a simple cli-based tool to search for the minumum of the Rosenbrock function using AD." << std::endl;
  std::cout << "The tool requires a path to the config.toml file as a single command-line argument." << std::endl;
  std::cout << "Invoke the tool as follows:" << std::endl << std::endl;
  std::cout << "./ad <path-to-config>" << std::endl;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    usage();
    return 1;
  }
    
  search_params sp;
  rosenbrock_params rp;
  toml::table tbl;

  try {
    tbl = toml::parse_file(argv[1]);

    sp.alpha = tbl["search"]["alpha"].value<double>().value_or(1e-3);
    sp.epochs = tbl["search"]["alpha"].value<int>().value_or(100);
    sp.multi_trial_count =
        tbl["search"]["multi_trial_count"].value<int>().value_or(1);

    sp.alpha = tbl["search"]["alpha"].value<double>().value_or(1e-3);
    sp.epochs = tbl["search"]["alpha"].value<int>().value_or(100);
    sp.multi_trial_count =
        tbl["search"]["multi_trial_count"].value<int>().value_or(1);

    rp.a = tbl["rosenbrock"]["a"].value<double>().value_or(1.0);
    rp.b = tbl["rosenbrock"]["b"].value<double>().value_or(100.0);

  } catch (const toml::parse_error &err) {
    std::cerr << "Parsing failed:\n" << err << "\n";
    return 1;
  }

  minimum_ctx min;
  std::random_device rand_dev;
  std::mt19937 gen(rand_dev());
  std::uniform_real_distribution<double> distr(-5.0, 5.0);

  for (int trial = 0; trial < sp.multi_trial_count; trial++) {

    std::array<dual, 2> x{dual(distr(gen), 0.0), dual(distr(gen), 0.0)};
    std::array<double, 2> grad{0.0, 0.0};
    rosenbrock<dual> r(rp.a, rp.b);

    dual f(0.0, 0.0);

    for (int k = 0; k < sp.epochs; k++) {
      for (int i = 0; i < x.size(); i++) {
        x[i].der = 1.0;
        f = r(x);
        grad[i] = f.der;
        x[i].der = 0.0;
      }

      for (int i = 0; i < x.size(); i++) {
        x[i].val -= sp.alpha * grad[i];
      }
    }

    if (trial == 0 || f.val < min.f) {
      min.x_vec[0] = x[0].val;
      min.x_vec[1] = x[1].val;
      min.f = f.val;
      min.trial = trial + 1;
    }
  }
  min.echo();
}
