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
1���ҵ������λ�� (x, y)����Ϊ 0
2������� (x, y)���Ѵ��ڵ����ִ� 1������
3������Ƿ�Ϸ���Check����
    �Ϸ����� (x, y)�ƶ�����һ��λ�á�GetNext��������λ������������Ϊ 0
    �Ƿ���
        �� (x, y)������С�������������� n���ص� 2
        �� (x, y)�����ִ������������� n��(x, y)�ص���һ��λ�á�GetPrev��
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
    /* �����׼��� */
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
    /* ���� */
    if( *y == 0 ){
        (*x) --;
        *y = n-1;
    }
}

void GetNext ( int* x, int* y, int n )
{
    (*y) ++;
    /* ���� */
    if( *y == n ){
        (*x) ++;
        *y = 1;
    }
}

int Check ( const int x, const int y, int n, int LatinSquare[n][n] )
{
    int i = 0;

    /* �̶� x������� */
    for( i=0; i < n; i++ ){
        if( LatinSquare[x][i] == LatinSquare[x][y] ){
            if( i != y ){
                return 0;
            }
        }
    }
    /* �̶� y������� */
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