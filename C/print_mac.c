#include <stdio.h>
#include <string.h>

char *get_mac_in_buffer (unsigned char *mac) {
#define MAC_STR_SIZE (14+1) /* For example 0011.25aa.b846 */
    static unsigned char buffer[MAC_STR_SIZE];
    memset(buffer, 0, sizeof buffer);

    int len = snprintf(buffer, sizeof buffer, "%x%x.%x%x.%x%x", 
                       mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    return buffer;
}

int main () {

    char mac[] = { 0, 0x11, 0x25, 0xaa, 0xb8, 0x46 };
    printf("mac_str: %s \n", get_mac_in_buffer(mac));
    
    mac[0] = 0x22;
    printf("mac_str: %s \n", get_mac_in_buffer(mac));

    return 0;
}
