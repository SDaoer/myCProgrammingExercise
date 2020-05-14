# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define LEN 17
/* 将上机号作为数组下标，省去遍历数组查找上机号 */

typedef struct {
    char stu_NO[LEN];
    int seatNO;
} ShangJiHao;

int main()
{
    int i;
    int N;
    scanf("%d", &N);

    ShangJiHao list[N];
    char temp[LEN];
    int t;

    // 读入数据
    for( i=0; i < N; i++ ){
        scanf("%s%d", temp, &t);
        temp[LEN-1] = '\0';
        scanf("%d", &list[t].seatNO);
        strcpy( list[t].stu_NO, temp );
        list[t].stu_NO[LEN-1] = '\0';
    }

    // 读入查找数量
    int num;
    scanf("%d", &num);
    // 读入查找的号码
    int search[num];
    for( i=0; i < num; i++ ){
        scanf("%d", &search[i]);
    }
    
    // 查找
    for( i=0; i < num; i++ ){
        printf("%s %d\n", list[search[i]].stu_NO, list[search[i]].seatNO);
    }

    system("pause");
    return 0;
}