
unsigned next_power_of_two (unsigned int n) {

    unsigned count = 0;

    while (n) {
        n = n >> 1;
        count++;
    }

    return 0x1 << count;
}

