#ifndef GPX_READ_H
#define GPX_READ_H

#define MAX_POINTS 10000
#define MAX_FILE_NAME 256

int read_file(const char *filename, double *lats, double *lons, double *eles, char *route_name);

#endif