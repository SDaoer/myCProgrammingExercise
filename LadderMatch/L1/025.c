# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define LEN 100

int IsDigit ( char c );

int main()
{
    char str1[LEN] = {'\0'}, str2[LEN] = {'\0'};
    scanf("%s", str1);
    getchar();/* 读取第一个空格 */
    gets(str2);/* 完整读取可能有空格分隔的字符串，用 scanf 则会读取不完整，如 B：123 456 41 */

    int i=0;
    int str1_ok = 1, str2_ok = 1;
    int n1 = -1, n2 = -1;
    for( i=0; i < LEN; i++ ){
        if( IsDigit(str1[i]) == 0 ){
            if( str1[i] != '\0' ){
                str1_ok = 0;
            }
        }
        if( IsDigit(str2[i]) == 0 ){
            if( str2[i] != '\0' ){
                str2_ok = 0;
            }
        }
    }
    /***************************/
    if( str1_ok ){
        n1 = atoi(str1);
        if( n1 < 1 || n1 > 1000 ){
            strcpy( str1, "?" );
            n1 = -1;
        }
    }else{
        strcpy( str1, "?" );
    }
    /***************************/
    if( str2_ok ){
        n2 = atoi(str2);
        if( n2 < 1 || n2 > 1000 ){
            strcpy( str2, "?" );
            n2 = -1;
        }
    }else{
        strcpy( str2, "?" );
    }

    if( n1 < 0 || n2 < 0 ){
        printf("%s + %s = ?\n", str1, str2);
    }else{
        printf("%s + %s = %d\n", str1, str2, n1 + n2);
    }

    
    system("pause");
    return 0;
}

int IsDigit ( char c )
{
    return ( 48 <= c && c <= 57 );
}