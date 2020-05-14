# include <stdio.h>
# include <stdlib.h>

# define SUM 24
# define NUM_OF_UNKNOWNS 6

int SolveLinerEquation ( int sum, int num_of_unknowns );
int Unknowns[NUM_OF_UNKNOWNS] = {0};

int main()
{
    int cnt=0;
    cnt = SolveLinerEquation(SUM, NUM_OF_UNKNOWNS);
    printf("%d\n", cnt);

    system("pause");
    return 0;
}

int SolveLinerEquation ( int sum, int num_of_unknowns )
{
    int x=0;
    int cnt=0;
    int seq_num = NUM_OF_UNKNOWNS-num_of_unknowns;

    if( num_of_unknowns == 1 ){
        x = sum;
        Unknowns[seq_num] = x;
        cnt++;
        /* for( int i=0; i<seq_num+1; i++ ){
            printf("%d ", Unknowns[i]);
        }
        putchar('\n'); */
        return cnt;
    }

    for( x=0; x <= sum; x++ ){
        Unknowns[seq_num] = x;
        cnt += SolveLinerEquation(sum-x, num_of_unknowns-1);
    }

    return cnt;
}