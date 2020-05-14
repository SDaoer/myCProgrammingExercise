# include <stdio.h>
# include <stdlib.h>

# define ID_LEN 18

int main()
{
    int weight[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
    char M[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};

    char ID[ID_LEN+1] = {0};
    int n, i, j;
    int unpassed_sum = 0, check_sum = 0, pass = 1;
    scanf("%d\n", &n);

    for( i = 0; i < n; i++ ){
        gets(ID);
        check_sum = 0;
        pass = 1;
        for( j = 0; j < ID_LEN-1; j++ ){
            if( 48 <= ID[j] && ID[j] <= 57 ){
                check_sum += (ID[j]-48)*weight[j];
            }else{
                pass = 0;
                break;
            }
        }
        if( M[check_sum%11] != ID[ID_LEN-1] ){
            pass = 0;
        }
        if(pass == 0){
            unpassed_sum++;
            puts(ID);
        }
    }

    if(unpassed_sum == 0){
        printf("All passed\n");
    }

    system("pause");
    return 0;
}