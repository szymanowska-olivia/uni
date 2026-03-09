#include "route.h"
#include "distance.h"

#include <stdlib.h>

double route_length(double *lats, double *lons, double *eles, int ilepoints) {
    double suma_dis = 0.0;
    for (int i = 1; i < ilepoints; i++) suma_dis += pitagoras3D(lats[i - 1], lons[i - 1], eles[i - 1], lats[i], lons[i], eles[i]);
    return suma_dis;
}

int compare(const void *a, const void *b) {
    double diff = *(double*)a - *(double*)b;
    return (diff > 0) - (diff < 0);
}