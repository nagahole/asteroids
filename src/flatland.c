#include "flatland.h"
#include <stdio.h>

// Maximum distance an asteroid can move and still be considered the same asteroid
// In other words, this is also the fastest moving asteroid flatland can detect
#define SAME_ASTEROID_TOLERANCE 99999

// If the predicted position of an asteroid is within this tolerance, will intercept
#define PREDICTION_TOLERANCE 2

void flatland_protect(void* cluster, void* scanner)
{
    int n_scanners = get_num_scanners(scanner);
    float* scanner_pos = get_scanner_positions(scanner);

    float last_pos[2][2] = { { -1, -1 }, { -1, -1 } }; 
    //a y value of -1 is impossible - so it's a safe default value

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
        
        if (lowest_asteroid[0] == -1)
        {
            //resets last two positions
            for(int i = 0; i < 2; i++)
            {
                for(int j = 0; j < 2; j++)
                {
                    last_pos[i][j] = -1;
                }
            }
            DEBUG_PRINT("x ");
        }
        else 
        {
            DEBUG_PRINT("Lowest Ast: [%f, %f]\n", lowest_asteroid[0], lowest_asteroid[1]);
            if (last_pos[0][0] == -1)
            {
                last_pos[0][0] = lowest_asteroid[0];
                last_pos[0][1] = lowest_asteroid[1];
            }
            else if (last_pos[1][0] == -1)
            {
                last_pos[1][0] = last_pos[0][0];
                last_pos[1][1] = last_pos[0][1];

                last_pos[0][0] = lowest_asteroid[0];
                last_pos[0][1] = lowest_asteroid[1];
            }
            else
            {
                float deltas[2][2] = {
                    { lowest_asteroid[0] - last_pos[0][0], lowest_asteroid[1] - last_pos[0][1] },
                    { last_pos[0][0] - last_pos[1][0], last_pos[0][1] - last_pos[1][1] }
                };

                float d_delta[2] = { deltas[0][0] - deltas[1][0], deltas[0][1] - deltas[1][1] };

                // predicted delta is most recent delta + change in delta
                float predicted_delta[2] = { 
                    deltas[0][0] + d_delta[0],
                    deltas[0][1] + d_delta[1]
                };

                float predicted_pos[2] = {
                    lowest_asteroid[0] + predicted_delta[0],
                    lowest_asteroid[1] + predicted_delta[1]
                };

                asteroid_cluster_intercept(cluster, predicted_pos[0], predicted_pos[1]);

                //resets last two positions
                for(int i = 0; i < 2; i++)
                {
                    for(int j = 0; j < 2; j++)
                    {
                        last_pos[i][j] = -1;
                    }
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