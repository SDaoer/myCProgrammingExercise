# include <stdio.h>
# include <stdlib.h>

const char* NianShuZi[10] = {
    "ling", "yi", "er", "san", "si", 
    "wu", "liu", "qi", "ba", "jiu"
};


int main()
{
    char number[100];
    scanf("%s", number);

    char digit_char_next = number[0];
    int t;
    if( number[0] == '-' ){
        printf("fu ");
        int i=1;
        while( number[i] != '\0' ){
            digit_char_next = number[i+1];
            t = number[i] - 48;
            if( digit_char_next ){
                printf("%s ", NianShuZi[t]);
            }else{
                printf("%s", NianShuZi[t]);
            }
            i++;
        }
    }else{
        int i=0;
        while( number[i] != '\0' ){
            digit_char_next = number[i+1];
            t = number[i] - 48;
            if( digit_char_next ){
                printf("%s ", NianShuZi[t]);
            }else{
                printf("%s", NianShuZi[t]);
            }
            i++;
        }
    }

    putchar('\n');

    system("pause");
    return 0;
}