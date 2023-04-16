#include "flatland.h"
#include <stdio.h>

void flatland_protect(void* cluster, void* scanner)
{
    int n_scanners = get_num_scanners(scanner);
    float* scanner_pos = get_scanner_positions(scanner);

    vector2 last_pos[2];

    last_pos[0].x = -1;
    last_pos[0].y = -1;
    last_pos[1].x = -1;
    last_pos[1].y = -1;

    //a y value of -1 is impossible - so it's a safe default value

    // Cluster not clear and no impact
    while ( !asteroid_cluster_clear(cluster) 
         && !asteroid_cluster_impact(cluster))
    {
        float* dist = scan(scanner, cluster);

        vector2 lowest_asteroid;
        
        lowest_asteroid.x = -1;
        lowest_asteroid.y = -1;

        // Finds the lowest asteroid

        for(int i = 0; i < n_scanners - 1; i++)
        {
            for(int j = i + 1; j < n_scanners; j++)
            {
                vector2 pos;

                // If intersection of two circles detected
                if (find_intersection(scanner_pos[i], dist[i], scanner_pos[j], dist[j], &pos)) 
                {
                    if (lowest_asteroid.x == -1 || pos.y < lowest_asteroid.y)
                    {
                        lowest_asteroid = pos;
                    }
                }
            }
        }
        
        // No asteroids detected
        if (lowest_asteroid.y == -1)
        {
            // Resets last two positions
            for(int i = 0; i < 2; i++)
            {
                last_pos[i].x = -1;
                last_pos[i].y = -1;
            }
            DEBUG_PRINT("x ");
        }
        else 
        {
            DEBUG_PRINT("Lowest Ast: [%f, %f]\n", lowest_asteroid.x, lowest_asteroid.y);
            if (last_pos[0].y == -1)
            {
                last_pos[0] = lowest_asteroid;
            }
            else if (last_pos[1].y == -1)
            {
                last_pos[1] = last_pos[0];
                last_pos[0] = lowest_asteroid;
            }
            else // Last two positions are recorded
            {
                vector2 deltas[2];

                // Most recent delta x and y
                deltas[0].x = lowest_asteroid.x - last_pos[0].x;
                deltas[0].y = lowest_asteroid.y - last_pos[0].y;

                // One before delta x and y
                deltas[1].x = last_pos[0].x - last_pos[1].x;
                deltas[1].y = last_pos[0].y - last_pos[1].y;

                vector2 d_delta;

                // Change in delta x and y
                d_delta.x = deltas[0].x - deltas[1].x;
                d_delta.y = deltas[0].y - deltas[1].y;

                // predicted delta is most recent delta + change in delta
                vector2 predicted_delta;

                predicted_delta.x = deltas[0].x + d_delta.x;
                predicted_delta.y = deltas[0].y + d_delta.y;

                // predicted position is last position + predicted delta
                vector2 predicted_pos;

                predicted_pos.x = lowest_asteroid.x + predicted_delta.x;
                predicted_pos.y = lowest_asteroid.y + predicted_delta.y;

                asteroid_cluster_intercept(cluster, predicted_pos.x, predicted_pos.y);

                // Resets last two positions

                // No way of knowing whether or not asteroid hit. So best way is to just
                // keep intercepting until it works I guess
                for(int i = 0; i < 2; i++)
                {
                    last_pos[i].x = -1;
                    last_pos[i].y = -1;
                }
            }
        }
    }

    return;
}

// Code translated from math equations to code from source
// https://math.stackexchange.com/questions/256100/how-can-i-find-the-points-at-which-two-circles-intersect

/*
 * Finds the intersection of two circles, where the centre of the circles are the positions
 * of the scanners and the radius of the circles are the reported distance to the closest 
 * asteroid of each scanner. Is practically 100% accurate *IF* the two scanners are pointing
 * at the same asteroid. However, will return an inaccurate value if two scanners point at
 * different asteroids and there is still an intersection between the two circles. It's an
 * implementation. Maybe not a good one, but it works mostly.
 * 
 * Returns 1 if the two circles intersect, else 0. vector2 position returned in 'pos' parameter
 * (if it exists)
 */
int find_intersection(float s1_pos, float s1_dist, float s2_pos, float s2_dist, vector2* pos) {
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

    pos->x = ix;

    if (iy1 > iy2)
        pos->y = iy1;
    else
        pos->y = iy2;

    return 1;
}