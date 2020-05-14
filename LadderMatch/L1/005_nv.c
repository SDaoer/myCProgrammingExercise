# include <stdio.h>
# include <stdlib.h>

# define LEN 17

typedef struct {
    char stu_NO[LEN];
    int seatNO1;
    int seatNO2;
} StudentInfo;

int main()
{
    int i, j;
    int N;
    scanf("%d", &N);

    StudentInfo list[N];

    // 读入数据
    for( i=0; i < N; i++ ){
        scanf("%s%d%d", list[i].stu_NO, &list[i].seatNO1, &list[i].seatNO2);
    }

    // 读入查找数量
    int num;
    scanf("%d", &num);
    // 读入查找的号码
    int search1[num];
    for( i=0; i < num; i++ ){
        scanf("%d", &search1[i]);
    }
    
    // 查找
    for( i=0; i < num; i++ ){
        for( j=0; j < N; j++ ){
            if( list[j].seatNO1 == search1[i] ){
                printf("%s %d\n", list[j].stu_NO, list[j].seatNO2);
            }
        }
    }

    system("pause");
    return 0;
}