# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define N 87539319

// 87539319
/*
352**3*2 < 87539319
353**3*2 > 87539319
=>  1<= x <= 352

444**3 < 87539319
445**3 > 87539319
=>  352<= y <= 444
*/

int main()
{
    int x, y;
    int i, j;

    int mid;
    mid = (int)pow( N/2.0, 1/3.0 );
    int N_left;
    int maybe_y;

    for( i=1; i <= mid; i++ ){
        N_left = N-i*i*i;
        maybe_y = (int)pow( N_left, 1/3.0 );
        if( maybe_y*maybe_y*maybe_y == N_left ){
            x = i;
            y = maybe_y;
            printf("%d %d\n", x, y);
        }
        maybe_y ++;
        if( maybe_y*maybe_y*maybe_y == N_left ){
            x = i;
            y = maybe_y;
            printf("%d %d\n", x, y);
        }
    }

    system("pause");
    return 0;
}