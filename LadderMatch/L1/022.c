# include <stdio.h>
# include <stdlib.h>

int main()
{
    int n;
    scanf("%d", &n);

    int cnt_1=0, cnt_2=0, t;
    for( int i=0; i < n; i++ ){
        scanf("%d", &t);
        if( t%2 ){
            cnt_1 ++;
        }else{
            cnt_2 ++;
        }
    }
    printf("%d %d\n", cnt_1, cnt_2);


    system("pause");
    return 0;
}