# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <windows.h>

# define SLEEP_TIME 500

typedef struct {
    char* str;
    int len;
} stirng_block;
typedef stirng_block* String;

String initString_null();
String initString_size(int size);
void destroyString(String s);

void assign(String s, const char* args);

void buildNext(const String pattern, int* next);
int KMP_SearchAll(const String pattern, const String s);
void Display(int i, int j, String pattern, String s);

int main()
{
    String s = initString_size(500);
    String pattern = initString_size(50);
    /* 题目给的测试用例为 aaabbdaabbde 和 aabbd 没有测试
     * 模式串首尾有相同字母的例子，则可能遗漏进行第二次匹配时目标串
     * 索引没有回到匹配位置的下一个，而是直接匹配下去
     */
    assign(s, "aaabbdaabbdae");
    assign(pattern, "aabbda");

    printf("\"%s\"在\"%s\"中出现%d次\n", pattern->str, s->str, KMP_SearchAll(pattern, s));

    destroyString(s);
    destroyString(pattern);

    system("pause");
    return 0;
}

String initString_null()
{
    String s = (String)malloc(sizeof(stirng_block));
    s->len = 0;
    s->str = NULL;

    return s;
}

String initString_size(int size)
{
    String s = (String)malloc(sizeof(stirng_block));
    s->len = 0;
    s->str = (char*)malloc(sizeof(char) * size);

    return s;
}

void destroyString(String s)
{
    free(s->str);
    s->str = NULL;
    free(s);
}

void assign(String s, const char* args)
{
    s->len = strlen(args);
    strcpy(s->str, args);
}

void buildNext(const String pattern, int* next)
{
    int k = -1, j = 0; // k，j 是 pattern 的前后索引
    next[0] = -1;

    while (j < pattern->len - 1) {
        if (k == -1 || pattern->str[j] == pattern->str[k]) {  // k == -1 代表 k 在 pattern[0] 再次回退，退无可退
            j++;
            k++;
            next[j] = k;
        } else {
            // 回退索引 k
            k = next[k];
        }
    }

    /* for (int i = 0; i < pattern->len; i++) {
        printf("%d", next[i]);
    }
    putchar('\n'); */

}

int KMP_SearchAll(const String pattern, const String s)
{
    int i = 0, j = 0;   // i，j 分别是目标串和模式串的索引
    int next[pattern->len];
    int times = 0;

    // 目标串比模式串短，直接返回 0
    if (s->len < pattern->len) {
        return times;
    }

    buildNext(pattern, next);

    while (j < pattern->len && i < s->len){
        if (s->str[i] == pattern->str[j]) {
            i++;
            j++;
        } else {
            if (j > 0) {
                j = next[j - 1] + 1;
            } else {
                i++;
            }
        }
        Display(i, j, pattern, s);

        if (j == pattern->len) {
            times++;
            j = 0;
            // display successful match
            for(int k = 0; k < i - pattern->len; k++) {
                putchar(' ');
            }
            for(int k = 0; k < pattern->len; k++) {
                putchar('#');
            }
            putchar('\r');
            Sleep(SLEEP_TIME);
            
            i = i - pattern->len + 1;
            Display(i, j, pattern, s);
        }
    }
    
    // for display
    system("cls");
    
    return times;
}

void Display(int i, int j, String pattern, String s)
{
    system("cls");
    int k;
    // 显示目标串
    for (k = 0; k < s->len; k++){
        if (k == i) {
            printf("_%c_", s->str[k]);
        } else {
            printf("%c", s->str[k]);
        }
    }
    putchar('\n');
    // 填补空白
    for(k = 0; k < i - j; k++) {
        putchar(' ');
    }
    // 显示模式串
    for(k = 0; k < pattern->len; k++) {
        if (k == j) {
            printf("_%c_", pattern->str[k]);
        } else {
            printf("%c", pattern->str[k]);
        }
    }
    putchar('\r');
    Sleep(SLEEP_TIME);
}