# include<stdio.h>
# include <stdlib.h>
# include <stdbool.h>

int GetStdLatinSquare ( int n );
void GetPrev ( int* x, int* y, int n );
void GetNext ( int* x, int* y, int n );
int Check ( const int x, const int y, int n, int LatinSquare[n][n] );
void Output ( int n, int LatinSquare[n][n] );

int LatinSquare[3][3];

/*
1、找到可填充位置 (x, y)，置为 0
2、填入比 (x, y)中已存在的数字大 1的数字
3、检查是否合法【Check】：
    合法：将 (x, y)移动至下一个位置【GetNext】，并将位置内数字重置为 0
    非法：
        当 (x, y)中数字小于于拉丁方阶数 n，回到 2
        当 (x, y)中数字大于拉丁方阶数 n，(x, y)回到上一个位置【GetPrev】
*/

int main()
{
    GetStdLatinSquare( 4 );
    
    system("pause");
    return 0;
}

int GetStdLatinSquare ( int n )
{
    int LatinSquare[n][n];
    int i, j, cnt = 0;
    /* 构造标准框架 */
    for( i = 0; i < n; i++ ){
        for( j = 0; j < n; j++ ){
            if( i == 0 ){
                LatinSquare[i][j] = j+1;
            }else if( j == 0 ){
                LatinSquare[i][j] = i+1;
            }else{
                LatinSquare[i][j] = 0;
            }
        }
    }
    int x = 1, y = 1;
    LatinSquare[x][y] = 0;
    while(1){
        LatinSquare[x][y] ++;
        if( LatinSquare[x][y] > n ){
            if( x == 1 && y == 1 ){
                break;
            }
            GetPrev( &x, &y, n );
            LatinSquare[x][y] ++;
        }
        //printf("[%d][%d]: %d\n", x, y, LatinSquare[x][y]);

        if( Check( x, y, n, LatinSquare ) ){
            if( x == n-1 && y == n-1 ){
                cnt ++;
                Output( n, LatinSquare );
                continue;
            }
            GetNext( &x, &y, n );
            LatinSquare[x][y] = 0;
        }

    }

    return cnt;
}

void GetPrev ( int* x, int* y, int n )
{
    (*y) --;
    /* 换行 */
    if( *y == 0 ){
        (*x) --;
        *y = n-1;
    }
}

void GetNext ( int* x, int* y, int n )
{
    (*y) ++;
    /* 换行 */
    if( *y == n ){
        (*x) ++;
        *y = 1;
    }
}

int Check ( const int x, const int y, int n, int LatinSquare[n][n] )
{
    int i = 0;

    /* 固定 x，检查列 */
    for( i=0; i < n; i++ ){
        if( LatinSquare[x][i] == LatinSquare[x][y] ){
            if( i != y ){
                return 0;
            }
        }
    }
    /* 固定 y，检查行 */
    for( i=0; i < n; i++ ){
        if( LatinSquare[i][y] == LatinSquare[x][y] ){
            if( i != x ){
                return 0;
            }
        }
    }
    return 1;
}

void Output ( int n, int LatinSquare[n][n] )
{
    int i, j;
    for( i = 0; i < n; i++ ){
        for( j = 0; j < n; j++ ){
            printf("%d ", LatinSquare[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}