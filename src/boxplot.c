#include "boxplot.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

float maxf(float i1, float i2) {
  if (i1 > i2)
    return i1;
  return i2;
}

float minf(float i1, float i2) {
  if (i1 < i2)
    return i1;
  return i2;
}
/**
 * data must be a sorted array from low to high
 */
box_plot_t *compute_box_plot(const float *data, int len) {

  if (len <= 4)
    return NULL;

  // calc fixed qs
  const unsigned int mean_idx = floor((float)len / 2);
  const unsigned int lmean_idx = ceil((float)mean_idx / 2);
  const unsigned int rmean_idx = mean_idx + floor((float)mean_idx / 2);

  const float q1 = data[lmean_idx];
  const float q2 = data[mean_idx];
  const float q3 = data[rmean_idx];

  const float iqr = q3 - q1;

  // printf("CALC IQR: q3 - q1 = iqr | %f - %f = %f\n", q3, q1, iqr);

  const float data_min = data[0];
  const float data_max = data[len - 1];

  const float min = maxf(data_min, q1 - 1.5 * iqr);
  const float max = minf(data_max, q3 + 1.5 * iqr);

  // get outliers
  unsigned int outliers_length = 0;
  unsigned int outliers_buffsize = 2;
  float *outliers = (float *)malloc(sizeof(outliers) * outliers_buffsize);

  for (int i = 0; i < len; i++) {
    if (data[i] < min) {
      // add lower bound outlier
      if (++outliers_length >= outliers_buffsize) {
        outliers_buffsize *= 2;
        outliers = (float *)realloc(outliers, outliers_buffsize);
        if (outliers == NULL) {
          return NULL;
        }
      }
      outliers[outliers_length - 1] = data[i];
    }
  }

  for (int i = len - 1; i >= 0; i--) {
    if (data[i] > max) {
      // add lower bound outlier
      if (++outliers_length >= outliers_buffsize) {
        outliers_buffsize *= 2;
        outliers = (float *)realloc(outliers, outliers_buffsize);
        if (outliers == NULL) {
          return NULL;
        }
      }
      outliers[outliers_length - 1] = data[i];
    }
  }

  outliers = (float *)realloc(outliers, outliers_length);

  box_plot_t *const result = malloc(sizeof(*result));

  *result = (box_plot_t){.q1 = q1,
                         .q2 = q2,
                         .q3 = q3,
                         .min = min,
                         .max = max,
                         .outliers = outliers,
                         .outlier_length = outliers_length};

  return result;
}
