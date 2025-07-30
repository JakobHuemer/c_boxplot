
#include "boxplot.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Dummy stub of compute_box_plot to illustrate testing.
// Replace with your real function implementation.
box_plot_t *compute_box_plot(const float *data, int len);

// Utility: float comparison with tolerance
bool float_equal(float a, float b, float tol) { return fabs(a - b) <= tol; }

// Test function returns 1 if failed, 0 if passed
int test_box_plot(const float *data, int len, float exp_q1, float exp_q2,
                  float exp_q3, float exp_min, float exp_max,
                  const float *exp_outliers, unsigned int exp_outliers_len) {
  box_plot_t *bp = compute_box_plot(data, len);
  float tol = 0.0001f;
  bool pass = true;

  if (!float_equal(bp->q1, exp_q1, tol)) {
    printf("FAIL q1: got %f expected %f\n", bp->q1, exp_q1);
    pass = false;
  }
  if (!float_equal(bp->q2, exp_q2, tol)) {
    printf("FAIL q2: got %f expected %f\n", bp->q2, exp_q2);
    pass = false;
  }
  if (!float_equal(bp->q3, exp_q3, tol)) {
    printf("FAIL q3: got %f expected %f\n", bp->q3, exp_q3);
    pass = false;
  }
  if (!float_equal(bp->min, exp_min, tol)) {
    printf("FAIL min: got %f expected %f\n", bp->min, exp_min);
    pass = false;
  }
  if (!float_equal(bp->max, exp_max, tol)) {
    printf("FAIL max: got %f expected %f\n", bp->max, exp_max);
    pass = false;
  }
  if (bp->outlier_length != exp_outliers_len) {
    printf("FAIL outlier length: got %u expected %u\n", bp->outlier_length,
           exp_outliers_len);
    pass = false;
  }
  for (unsigned int i = 0; i < exp_outliers_len; i++) {
    if (!float_equal(bp->outliers[i], exp_outliers[i], tol)) {
      printf("FAIL outlier[%u]: got %f expected %f\n", i, bp->outliers[i],
             exp_outliers[i]);
      pass = false;
    }
  }
  if (pass) {
    printf("PASS\n");
  }
  free(bp->outliers);
  free(bp);

  return pass ? 0 : 1;
}

int main() {
  int failed = 0;

  float data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  float expected_outliers1[] = {};
  failed |= test_box_plot(data1, 9, 3.0f, 5.0f, 7.0f, 1.0f, 9.0f,
                          expected_outliers1, 0);

  float data2[] = {1, 2, 3, 4, 5, 6, 7, 8, 50};
  float expected_outliers2[] = {50};
  failed |= test_box_plot(data2, 9, 3.0f, 5.0f, 7.0f, 1.0f, 13.0f,
                          expected_outliers2, 1);

  float data3[] = {-20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 30};
  float expected_outliers3[] = {-20, 30};
  failed |= test_box_plot(data3, 11, 3.0f, 5.0f, 7.0f, -3.0f, 13.0f,
                          expected_outliers3, 2);

  return failed ? 1 : 0;
}
