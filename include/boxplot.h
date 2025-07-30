#ifndef OUTLIERS_H
#define OUTLIERS_H

typedef struct box_plot {
  float q1;
  float q2;
  float min;
  float max;
  float q3;
  float *outliers;
  unsigned int outlier_length;
} box_plot_t;

box_plot_t *compute_box_plot(const float *data, int len);

#endif
