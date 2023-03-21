#ifndef TAYLOR_ACTION_HPP

#define TAYLOR_ACTION_HPP

static double compute(data_client client, double x) {
  data d = client.get_data().get();

  size_t size = d.size();

  double sum = 0;

  std::cout << d[size - 1] << std::endl;

  for (size_t i = 0; i < size; i++) {
    double e = d[i];

    sum += std::pow(-1.0, e + 1) * std::pow(x, e) / (e);
  }

  return sum;
}

HPX_PLAIN_ACTION(compute, compute_action)

#endif