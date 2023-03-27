#include "flatland.h"
#include <stdio.h>

// Maximum distance an asteroid can move and still be considered the same asteroid
#define SAME_ASTEROID_TOLERANCE 20

void flatland_protect(void* cluster, void* scanner)
{
    int n_scanners = get_num_scanners(scanner);
    float* scanner_pos = get_scanner_positions(scanner);

    float last_pos[2] = { -1, -1 }; //a y value of -1 is impossible - so it's a safe default value

    // Cluster not clear and no impact
    while ( !asteroid_cluster_clear(cluster) 
         && !asteroid_cluster_impact(cluster))
    {
        
        float* dist = scan(scanner, cluster);

        float lowest_asteroid[2] = { -1, -1 };

        for(int i = 0; i < n_scanners - 1; i++)
        {
            for(int j = i + 1; j < n_scanners; j++)
            {
                float pos[2];

                if (triangulate(scanner_pos[i], dist[i], scanner_pos[j], dist[j], pos)) 
                {
                    if (lowest_asteroid[1] == -1 || pos[1] < lowest_asteroid[1])
                    {
                        lowest_asteroid[0] = pos[0];
                        lowest_asteroid[1] = pos[1];
                    }
                }
            }
        }

        if(lowest_asteroid[1] == -1)
        {
            DEBUG_PRINT("NO INTERSECTION\n");
            last_pos[0] = -1;
            last_pos[1] = -1;
        }
        else
        {
            DEBUG_PRINT("LOWEST AST: [%f, %f]\n", lowest_asteroid[0], lowest_asteroid[1]);

            if(last_pos[1] == -1)
            {
                last_pos[0] = lowest_asteroid[0];
                last_pos[1] = lowest_asteroid[1];
            }
            else
            {
                if(flatland_dist(
                    last_pos[0], last_pos[1], lowest_asteroid[0], lowest_asteroid[1]
                ) <= SAME_ASTEROID_TOLERANCE)
                {
                    float dx = lowest_asteroid[0] - last_pos[0];
                    float dy = lowest_asteroid[1] - last_pos[1];

                    asteroid_cluster_intercept(cluster, lowest_asteroid[0] + dx, lowest_asteroid[1] + dy);

                    last_pos[0] = -1;
                    last_pos[1] = -1;
                }
                else
                {
                    last_pos[0] = lowest_asteroid[0];
                    last_pos[1] = lowest_asteroid[1];
                }
            }
        }
    }

    return;
}

int triangulate(float s1_pos, float s1_dist, float s2_pos, float s2_dist, float* pos) {
    float centerdx = s1_pos - s2_pos;

    float R = flatland_abs(centerdx);

    if (!(flatland_abs(s1_dist - s2_dist) <= R && R <= s1_dist + s2_dist)) { // no intersection
        return 0;
    }

    float R2 = R * R;
    float R4 = R2 * R2;
    float r2r2 = ((s1_dist * s1_dist) - (s2_dist * s2_dist));
    float a = r2r2 / (2 * R2);

    float c = flatland_sqrt(
        (2 * ((s1_dist * s1_dist) + (s2_dist * s2_dist)) / R2) 
        - ((r2r2 * r2r2) / R4)
        - 1
    );

    float fx = (s1_pos + s2_pos) / 2 + a * (s2_pos - s1_pos);
    float ix = fx;

    float gy = c * (s1_pos - s2_pos) / 2;
    float iy1 = gy;
    float iy2 = -gy;

    pos[0] = ix;

    if (iy1 > iy2)
        pos[1] = iy1;
    else
        pos[1] = iy2;

    return 1;
}