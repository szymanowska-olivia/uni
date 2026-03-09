#include "distance.h"
#include <math.h>

#define SECONDS_IN_DEGREE 3600.0
#define LAT_METERS_PER_SECOND 30.72
#define LON_METERS_PER_SECOND 19.22

double pitagoras3D(double lat1, double lon1, double ele1, double lat2, double lon2, double ele2) {
    double dLat = (lat2 - lat1) * SECONDS_IN_DEGREE * LAT_METERS_PER_SECOND;
    double dLon = (lon2 - lon1) * SECONDS_IN_DEGREE * LON_METERS_PER_SECOND;
    double dEle = ele2 - ele1;
    return sqrt(dLat * dLat + dLon * dLon + dEle * dEle);
}

double calc_distance(double lat1, double lon1, double ele1, double lat2, double lon2, double ele2) {
    return pitagoras3D(lat1, lon1, ele1, lat2, lon2, ele2);
}
