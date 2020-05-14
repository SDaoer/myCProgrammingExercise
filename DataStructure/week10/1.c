# include <stdio.h>
# include <stdlib.h>

typedef int ElemType;
typedef struct {
    int row_n;  // 行号
    int col_n;  // 列号
    ElemType elem;
} TriTuple;

typedef struct {
    int row;    // 行数
    int col;    // 列数
    int elem_num;// 非零元素个数
    TriTuple* compressed;
} CompressedMatrixBlock;
typedef CompressedMatrixBlock* CompressedMatrix;

CompressedMatrix newCompressedMatrix(ElemType* matrix, int row, int col);
void destroyCompressedMatrix(CompressedMatrix cm);

void transposeCompressedMatrix_saveTime(CompressedMatrix cm);
void transposeCompressedMatrix_saveSpace(CompressedMatrix cm);

CompressedMatrix add2CompressedMatrix(const CompressedMatrix a, const CompressedMatrix b);
CompressedMatrix multi2CompressedMatrix(const CompressedMatrix a, const CompressedMatrix b);

void outputCompressedMatrix(CompressedMatrix cm);

int main()
{
    int A[4][4] = {
        {1, 0, 3, 0}, 
        {0, 1, 0, 0}, 
        {0, 0, 1, 0}, 
        {0, 0, 1, 1}, 
    };
    int B[4][4] = {
        {3, 0, 0, 0}, 
        {0, 4, 0, 0}, 
        {0, 0, 1, 0}, 
        {0, 0, 0, 2}, 
    };

    // 1)
    CompressedMatrix a = newCompressedMatrix((int*)A, 4, 4);
    CompressedMatrix b = newCompressedMatrix((int*)B, 4, 4);
    puts("Matrix 'A' compressed:");
    outputCompressedMatrix(a);
    puts("Matrix 'B' compressed:");
    outputCompressedMatrix(b);
    puts("==============");

    // 2)
    puts("a.T :");
    transposeCompressedMatrix_saveTime(a);
    outputCompressedMatrix(a);
    transposeCompressedMatrix_saveSpace(a);
    puts("==============");

    // 3)
    puts("a + b :");
    CompressedMatrix result = add2CompressedMatrix(a, b);
    outputCompressedMatrix(result);
    puts("==============");

    // 4)
    puts("a × b :");
    result = multi2CompressedMatrix(a, b);
    outputCompressedMatrix(result);
    puts("==============");

    destroyCompressedMatrix(a);
    destroyCompressedMatrix(b);
    destroyCompressedMatrix(result);

    system("pause");
    return 0;
}

CompressedMatrix newCompressedMatrix(ElemType* matrix, int row, int col)
{
    CompressedMatrix cm = (CompressedMatrix)malloc(sizeof(CompressedMatrixBlock));
    cm->row = row;
    cm->col = col;
    
    int elem_num = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (matrix[i * j + j]) {
                elem_num++;
            }
        }
    }

    cm->elem_num = elem_num;
    cm->compressed = (TriTuple*)malloc(sizeof(TriTuple) * elem_num);

    for (int i = 0, n = 0, j; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (matrix[i * col + j]) {
                cm->compressed[n].row_n = i;
                cm->compressed[n].col_n = j;
                cm->compressed[n].elem = matrix[i * col + j];
                n++;
            }
        }
    }

    return cm;
}

void destroyCompressedMatrix(CompressedMatrix cm)
{
    free(cm->compressed);
    free(cm);
}

void transposeCompressedMatrix_saveTime(CompressedMatrix cm)
{
    // 本质上是把行排列的压缩矩阵数组变为列排列
    // 先确定cm中哪些位置是哪一列的起始位置
    // 用一个数组记录某一列的起始位置
    // 遇到某个列的元素，就查询数组将其安排到相应位置
    // 因为是顺序遍历压缩矩阵数组，所以这样安排的列元素是按照行序的，符合转置要求

    // 可以通过上一列元素的个数，推算出每一列的起始位置
    int num_of_col[cm->col];
    for (int i = 0; i < cm->col; i++) {
        num_of_col[i] = 0;
    }

    for (int i = 0; i < cm->elem_num; i++) {
        num_of_col[cm->compressed[i].col_n]++;
    }

    int loc_of_col[cm->col];    // 每一列元素的起始位置
    loc_of_col[0] = 0;
    for (int i = 1; i < cm->col; i++) {
        // 某一列起始位置为上一列元素起始位置 + 上一列元素个数
        loc_of_col[i] = loc_of_col[i-1] + num_of_col[i-1];
    }

    int loc;
    TriTuple* transpose = (TriTuple*)malloc(sizeof(TriTuple) * cm->elem_num);
    for (int i = 0; i < cm->elem_num; i++ ) {
        loc = loc_of_col[cm->compressed[i].col_n];
        transpose[loc].col_n = cm->compressed[i].row_n;
        transpose[loc].row_n = cm->compressed[i].col_n;
        transpose[loc].elem = cm->compressed[i].elem;
        loc_of_col[cm->compressed[i].col_n]++;
    }
    free(cm->compressed);
    cm->compressed = transpose;

}

void transposeCompressedMatrix_saveSpace(CompressedMatrix cm)
{
    for (int i = 0; i < cm->elem_num; i++) {
        int temp;
        temp = cm->compressed[i].col_n;
        cm->compressed[i].col_n = cm->compressed[i].row_n;
        cm->compressed[i].row_n = temp;
    }

    for (int i = 0, j; i < cm->elem_num - 1; i++) {
        TriTuple temp;
        for (j = 0; j < cm->elem_num - 1 - i; j++) {
            if (cm->compressed[j].row_n > cm->compressed[j+1].row_n) {
                temp = cm->compressed[j];
                cm->compressed[j] = cm->compressed[j+1];
                cm->compressed[j+1] = temp;
            }
        }
    }
}

CompressedMatrix add2CompressedMatrix(const CompressedMatrix a, const CompressedMatrix b)
{
    CompressedMatrix result = NULL;

    if (a->col == b->col && a->row == b->row) {
        int i = 0, j = 0, k = 0, n = 0;
        int c[a->row][a->col];
        for (i = 0; i < a->row; i++) {
            for (j = 0; j < a->col; j++) {
                c[i][j] = 0;
            }
        }
        for (i = 0; i < a->elem_num; i++) {
            c[a->compressed[i].row_n][a->compressed[i].col_n] += a->compressed[i].elem;
        }
        for (j = 0; j < b->elem_num; j++) {
            c[b->compressed[j].row_n][b->compressed[j].col_n] += b->compressed[j].elem;
        }
        result = newCompressedMatrix((int*)c, a->row, a->col);
    }

    return result;
}

CompressedMatrix multi2CompressedMatrix(const CompressedMatrix a, const CompressedMatrix b)
{
    CompressedMatrix result = NULL;

    if (a->col == b->row) {
        int c[a->row][b->col];
        for (int i = 0, j; i < a->row; i++) {
            for (j = 0; j < b->col; j++) {
                c[i][j] = 0;
            }
        }
        for (int i = 0, j = 0; i < a->elem_num; i++) {
            for (j = 0; j < b->elem_num; j++) {
                if (a->compressed[i].col_n == b->compressed[j].row_n) {
                    c[a->compressed[i].row_n][b->compressed[j].col_n] += a->compressed[i].elem * b->compressed[j].elem;
                }
            }
        }
        result = newCompressedMatrix((int*)c, a->row, b->col);
    }

    return result;
}

void outputCompressedMatrix(CompressedMatrix cm)
{
    for (int i = 0; i < cm->elem_num; i++) {
        printf("(%d, %d, %d)\n", cm->compressed[i].row_n,cm->compressed[i].col_n, cm->compressed[i].elem);
    }
}