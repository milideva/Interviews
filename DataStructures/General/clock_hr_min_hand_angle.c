#include <stdio.h>
#include <stdlib.h>

typedef unsigned int uint;

/* Get the angle between hr hand and minute hand of a clock */

uint get_angle (uint hr, uint min) {
    uint hr_angle, min_angle, one_tick_angle, result;

#define one_tick_angle (360/60)    
    min_angle = min * one_tick_angle;
    
    hr_angle = hr * 5 * one_tick_angle;
    hr_angle += (one_tick_angle * (min/12));

    result = abs(hr_angle - min_angle);

    if (result > 180) {
        /* Return the smaller angle */
        result = 360 - result;
    }
    printf("hr:%u min:%u angle:%d\n", hr, min, result);
    return result;
}

int main (void) {
    get_angle(1, 10);
    get_angle(11, 10);
    return 0;
}
