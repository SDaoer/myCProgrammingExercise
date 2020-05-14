# include <stdio.h>
# include <stdlib.h>

int main()
{
    int hour, minute;
    int i;

    scanf("%d:%d", &hour, &minute);
    if( 12 < hour && hour < 24 ){
        if( minute == 0 ){
            for( i = 0; i < hour-12; i++ ){
                printf("Dang");
            }
            putchar('\n');
        }else{
            for( i = 0; i < hour-11; i++ ){
                printf("Dang");
            }
            putchar('\n');
        }
    }else{
        if( hour == 12 ){
            if( minute ){
                printf("Dang\n");
            }else{
                printf("Only %02d:%02d.  Too early to Dang.\n", hour, minute);
            }
        }else{
            printf("Only %02d:%02d.  Too early to Dang.\n", hour, minute);
        }
    }

    system("pause");
    return 0;
}