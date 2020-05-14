# include <stdio.h>
# include <stdlib.h>

typedef struct _player{
    char tag;
    int limit;
    int drinks;
    int says;
    int play;
} Player;

int main()
{
    Player jia = {.tag='A', .limit=0, .drinks=0}, yi = {.tag='B', .limit=0, .drinks=0};
    Player* loser, * winner;
    int N;
    scanf("%d%d", &jia.limit, &yi.limit);
    scanf("%d", &N);

    for( int i=0; i < N; i++ ){
        scanf("%d%d%d%d", &jia.says, &jia.play, &yi.says, &yi.play);
        if( jia.play == jia.says + yi.says ){
            if( yi.play == jia.says + yi.says ){
                continue;
            }else{
                jia.drinks++;
                if( jia.drinks > jia.limit ){
                    loser = &jia;
                    winner = &yi;
                    break;
                }
            }
        }else if( yi.play == jia.says + yi.says ){
            yi.drinks++;
            if( yi.drinks > yi.limit ){
                loser = &yi;
                winner = &jia;
                break;
            }
        }
    }
    
    printf("%c\n%d\n", loser->tag, winner->drinks);

    system("pause");
    return 0;
}