# include <stdio.h>
# include <stdlib.h>

void printSaddlePoint(int* matrix, int row, int col)
{
    int saddle_point[row][col];
    int i, j;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            saddle_point[i][j] = 0;
        }
    }
    // 找到每一行的最小值
    for (i = 0; i < row; i++) {
        int min, min_col;
        // 最小值初始化为行首元素(第一列的元素)
        min = matrix[i * col];
        // 找到该行中最小值，记录其列号
        for (j = 1; j < col; j++) {
            if (min > matrix[i * col + j]) {
                min = matrix[i * col + j];
            }
        }
        // 记录全部最小值位置
        for (j = 0; j < col; j++) {
            if (min == matrix[i * col + j]) {
                saddle_point[i][j]++;
            }
        }
    }
    
    // 找到每一列的最大值
    for (j = 0; j < col; j++) {
        int max, max_row;
        // 最大值初始化为列首元素(第一行的元素)
        max = matrix[j];
        // 找到该行中最大值，记录其列号
        for (i = 1; i < row; i++) {
            if (max < matrix[i * col + j]) {
                max = matrix[i * col + j];
            }
        }
        // 记录全部最大值位置
        for (i = 0; i < row; i++) {
            if (max == matrix[i * col + j]) {
                saddle_point[i][j]++;
            }
        }
    }
    
    // 值为2的点是鞍点
    puts("鞍点有：");
    int n = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (saddle_point[i][j] == 2) {
                printf("(%d,%d):%d\n", i, j, matrix[i * col + j]);
                n++;
            }
        }
    }
    printf("共 %d 个\n", n);

}
/* 
 * 假设存在两个鞍点 A, B
 * A......m
 * .      .
 * .      .
 * .      .
 * n......B
 * 
 * 则 n < A < m => n < m
 * 且 m < B < n => m < n
 * 
 * 显然任意两个鞍点之间矛盾
 * 故不可能存在多个鞍点
 */

int main()
{
    int matrix[][4] = {
        {1, 1, 1, 1}, 
        {1, 1, 2, 1}, 
        {1, 1, 1, 1}, 
        {1, 1, 1, 1}, 
    };

    printSaddlePoint((int*)matrix, 4, 4);

    system("pause");
    return 0;
}