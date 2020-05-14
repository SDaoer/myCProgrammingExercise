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
    // �ҵ�ÿһ�е���Сֵ
    for (i = 0; i < row; i++) {
        int min, min_col;
        // ��Сֵ��ʼ��Ϊ����Ԫ��(��һ�е�Ԫ��)
        min = matrix[i * col];
        // �ҵ���������Сֵ����¼���к�
        for (j = 1; j < col; j++) {
            if (min > matrix[i * col + j]) {
                min = matrix[i * col + j];
            }
        }
        // ��¼ȫ����Сֵλ��
        for (j = 0; j < col; j++) {
            if (min == matrix[i * col + j]) {
                saddle_point[i][j]++;
            }
        }
    }
    
    // �ҵ�ÿһ�е����ֵ
    for (j = 0; j < col; j++) {
        int max, max_row;
        // ���ֵ��ʼ��Ϊ����Ԫ��(��һ�е�Ԫ��)
        max = matrix[j];
        // �ҵ����������ֵ����¼���к�
        for (i = 1; i < row; i++) {
            if (max < matrix[i * col + j]) {
                max = matrix[i * col + j];
            }
        }
        // ��¼ȫ�����ֵλ��
        for (i = 0; i < row; i++) {
            if (max == matrix[i * col + j]) {
                saddle_point[i][j]++;
            }
        }
    }
    
    // ֵΪ2�ĵ��ǰ���
    puts("�����У�");
    int n = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (saddle_point[i][j] == 2) {
                printf("(%d,%d):%d\n", i, j, matrix[i * col + j]);
                n++;
            }
        }
    }
    printf("�� %d ��\n", n);

}
/* 
 * ��������������� A, B
 * A......m
 * .      .
 * .      .
 * .      .
 * n......B
 * 
 * �� n < A < m => n < m
 * �� m < B < n => m < n
 * 
 * ��Ȼ������������֮��ì��
 * �ʲ����ܴ��ڶ������
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