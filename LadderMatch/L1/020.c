# include <stdio.h>
# include <stdlib.h>

# define NUM 100000

int main()
{
    int not_handsome_chart[NUM] = {0};  // Everyone is handsome.
    int num_of_circle, num_of_friends;
    int id;
    int nobody_handsome = 1;
    int i, j; 
    scanf("%d", &num_of_circle);

    for( i = 0; i < num_of_circle; i++ ){
        scanf("%d", &num_of_friends);
        for( j = 0; j < num_of_friends; j++ ){
            scanf("%d", &id);
            if( num_of_friends != 1 ){
                not_handsome_chart[id] = 1;
            }
        }
    }

    int search_num;
    scanf("%d", &search_num);

    for( int i=0, cnt=0; i < search_num; i++ ){
        scanf("%d", &id);
        if( not_handsome_chart[id] == 0 ){
            if( cnt ){
                printf(" ");
            }
            cnt++;
            nobody_handsome = 0;
            printf("%d", id);
            // have checked, become not hansome
            not_handsome_chart[id] = 1;
        }
        if( i == search_num ){
            putchar('\n');
        }
    }

    if( nobody_handsome ){
        printf("No one is handsome\n");
    }

    system("pause");
    return 0;
}