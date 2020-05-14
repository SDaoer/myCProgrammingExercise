# include <stdio.h>
# include <stdlib.h>

# define N 3

void Sort ( int arr[], int len );

int main()
{
    int num[N];
    int i;

    for( i = 0; i<N; i++ ){
        scanf("%d", &num[i]);
    }

    Sort( num, N );

    for( i=0; i < N-1; i++ ){
        printf("%d->", num[i]);
    }
    printf("%d\n", num[N-1]);

    system("pause");
    return 0;
}

void Sort ( int arr[], int len )
{
    int i, j, t;
    for( i=0; i < len; i++ ){
        for( j = len-1; j > i; j-- ){
            if( arr[j] < arr[j-1] ){
                t = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = t;
            }
        }
    }
}