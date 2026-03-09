#include "gpx_read.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int read_file(const char *filename, double *lats, double *lons, double *eles, char *route_name) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku: %s\n", filename);
        return -1;
    }

    char line[1024];
    int ilepoints = 0;
    route_name[0] = '\0';

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "<name>")) {
            sscanf(line, " <name>%255[^<]</name>", route_name);
        } else if (strstr(line, "<trkpt")) {
            double lat, lon, ele = 0.0;
            if (sscanf(line, " <trkpt lat=\"%lf\" lon=\"%lf\">", &lat, &lon) == 2) {
                while (fgets(line, sizeof(line), file) && !strstr(line, "</trkpt>")) {
                    if (strstr(line, "<ele>")) sscanf(line, " <ele>%lf</ele>", &ele);
                }
                if (ilepoints < MAX_POINTS) {
                    lats[ilepoints] = lat;
                    lons[ilepoints] = lon;
                    eles[ilepoints] = ele;
                    ilepoints++;
                }
            }
        }
    }

    fclose(file);
    return ilepoints;
}
