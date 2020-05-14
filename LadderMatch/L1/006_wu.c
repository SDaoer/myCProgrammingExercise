# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/* 在大于根号 N的整数中，不可能有连续的因子*/
/* 可证如下：
假设存在连续因子，m, m+1，其中 m>[sqrt(N)]，
对应有 x, y为 N的因子，满足 x*m=N, y*(m+1)=N
两式相乘可证得 x*y小于 1，与 “x, y为 N的因子”矛盾，原命题成立 */

/* 故而只会在小于等于 sqrt(N)+1 的范围产生连续因子
需要注意的是，大于等于 sqrt(N)+1 范围不会产生连续因子，
但 sqrt(N)+1 可能会作为其前面连续因子的最后一个，例如：
20：1、2、4、5、10、20
边界 sqrt(N)+1=5，作为前面连续因子的最后一个被算在内 */

/* 由上已知因子易求，剩下的就是查找因子序列的最长子列，复杂度 o(N) */

int main()
{
    int N;
    int i;
    scanf("%d", &N);

    int limit = (int)sqrt(N) + 1;
    int yinzi[limit];
    int cnt = 0;

    for( i=2; i <= limit; i++ ){
        if( N % i == 0 ){
            yinzi[cnt] = i;
            cnt++;
        }
    }
    yinzi[cnt+1] = 0;
/*     封零，因为根据变量定义的数组无法初始化，避免再搞一个循环进行初始化
    以及避免出现 yinzi[cnt] 恰好（尽管可能性很小）与前面元素连续，以
    导致不可意料的误差，对后面一位元素赋零，标识结束 */

    int head, tail;
    int loc_1, loc_2;
    int len=0, max_len=0;
    head = tail = 0;
    loc_1 = loc_2 = 0;
    
    for( i=0; i <= cnt; i++ ){
        // 寻找连续子列
        if( yinzi[i+1] == yinzi[i] + 1 ){   // 连续
            loc_2 = i+1;
            len = loc_2 - loc_1 + 1;
        }else{  // 不连续，重定位
            loc_1 = i+1;
            len = loc_2 - loc_1;
        }

        // 刷新最长连续子列
        if( len > max_len ){
            head = loc_1;
            tail = loc_2;
            max_len = len;
        }

    }

    if( max_len ){
        printf("%d\n", max_len);
        for( i=head; i < tail; i++ ){
            printf("%d*", yinzi[i]);
        }
        printf("%d\n", yinzi[tail]);
    }else{
        printf("无连续因子！\n");
    }

    system("pause");
    return 0;
}