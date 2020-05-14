# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

# define OP_NUM 8
# define A_LIM 3
# define B_LIM 5

int nodes[A_LIM][B_LIM] = {0};


int GetNodes ( int A, int B );/* 菰寥 */
void Empty ( int G );

int main()
{
    int num_of_nodes;
    int i, j;
    num_of_nodes = GetNodes( 0, 0 );
    int acessable_nodes[num_of_nodes][2];

    for( int i=0, k=0; i < A_LIM; i++ ){
        for( j=0; j < B_LIM; j++ ){
            if( nodes[i][j] ){
                acessable_nodes[k][0] = i;
                acessable_nodes[k][1] = 1;
                k++;
            }
        }
    }
    
    system("pause");
    return 0;
}

int GetNodes ( int A, int B )
{
    int cnt = 0;
    int A_t = A, B_t = B;
    /* 給諾A */
    A_t = 0;
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* 給諾B */
    B_t = 0;
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* 給雛A */
    A_t = A_LIM;
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* 給雛B */
    B_t = B_LIM;
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* A->B, A->0 */
    B_t += A_t;
    if( B_t > B_LIM ){
        B_t = B_LIM;
    }
    A_t = 0;
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* A->B, B->FULL */
    if(A_t > B_LIM-B_t){
        A_t -= B_LIM-B_t;
        B_t = B_LIM;
    }else{
        B_t += A_t;
        A_t = 0;
    }
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* B->A, B->0 */
    A_t += B_t;
    if( A_t > A_LIM ){
        A_t = A_LIM;
    }
    B_t = 0;
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }
    /* B->A, A->FULL */
    if(B_t > A_LIM-A_t){
        B_t -= A_LIM-A_t;
        A_t = A_LIM;
    }else{
        A_t += B_t;
        B_t = 0;
    }
    if( nodes[A_t][B_t] == 0 ){
        nodes[A_t][B_t] = 1;
        cnt++;
        cnt += PourWater( A_t, B_t );
        A_t = A;
        B_t = B;
    }

    return cnt;
}