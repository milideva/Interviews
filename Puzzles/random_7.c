/*
  Given a function which produces a random integer in the range 1 to 5, write
  a function which produces a random integer in the range 1 to 7.
*/

int rand7 (void) {
    int val = rand5() + rand5() + rand5() + rand5() + rand5() + rand5() + rand5(); 
    return val % 7;
}

// I do not know if the below is correct. 
int rand7()
{
    int vals[5][5] = {
        { 1, 2, 3, 4, 5 },
        { 6, 7, 1, 2, 3 },
        { 4, 5, 6, 7, 1 },
        { 2, 3, 4, 5, 6 },
        { 7, 0, 0, 0, 0 }
    };

    int result = 0;
    while (result == 0)
    {
        int i = rand5();
        int j = rand5();
        result = vals[i-1][j-1];
    }
    return result;
}
