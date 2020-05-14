# include <stdio.h>
# include <stdlib.h>
# define OUT_NUM 3

/* 
**有n个人围成一圈，顺序排号，从第一个人开始报数（从1到3
**报数），凡报到3的人退出圈子，问最后留下的人是原来的第几
**号？
*/

int main()
{
/*     int n;
    printf("请输入人数：");
    scanf("%d", &n); */
    
    int i = 0, cnt = 1, out = 0;
    
    int m = 0;
    int player[20];
for (int j = 1; j < 15; j++) {
    m = 0;
    out = 0;
    for (i = 0; i < j; i++) {
        player[i] = 0;
    }
    /* 开始报数游戏 */
    for (i = 0, cnt = 1; out < j - 1; i++) {
        m++;
        /* 下标越界，循环下标 */
        if (i == j) {
            i = 0;
        }
        /* 跳过已淘汰的玩家 */
        if (player[i] == 1) {
            continue;
        }
        /* 淘汰玩家 */
        if (cnt == OUT_NUM) {
            player[i] = 1;
            out++;
            cnt = 1;
            continue;
        }
        cnt++;
    }
    printf("%d-->%d\n", j, m);
}


    /* 找到最后的玩家 */
    /* 若是上个循环结束条件为 out < n; 最后的 i 就是最终玩家的序号（数组下标+1），但不便于理解 */
    /* for (i = 0; i < n; i++) {
        if ( player[i] == 0 ){
            break;
        }
    } */

    printf("最后的玩家是%d号\n", i+1);

    system("pause");
    return 0;
}