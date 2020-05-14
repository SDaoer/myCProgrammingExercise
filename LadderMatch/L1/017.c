# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int main()
{
    char string[52];
    gets(string);

    float stupidity = 1;
    int cnt=0, len;
    len = strlen(string);

    if( string[len-1] % 2 == 0 ){
        stupidity *= 2;
    }

    if( string[0] == '-' ){
        len--;
        stupidity *= 1.5;
    }

    for( int i=0; i < len; i++ ){
        if( string[i] == '2' ){
            cnt++;
        }
    }
    stupidity *= cnt*1.0/len;

    stupidity *= 100;

    printf("%.2f%%\n", stupidity);

    system("pause");
    return 0;
}