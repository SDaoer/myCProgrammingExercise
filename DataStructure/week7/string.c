# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define None 0

typedef struct {
    char* str;
    int size;
    int len;
} stirng_block;
typedef stirng_block* String;

String initString_null();
String initString_size(int size);
void destroyString(String s);

void assign(String s, const char* args);

void buildNext(const String pattern, int* next);
int KMP_Search(const String pattern, const String s);

int main()
{
    String s = initString_size(500);
    String pattern = initString_size(50);
    assign(s, "aaabbdaabbde");
    assign(pattern, "aabbd");

    printf("%d\n", KMP_Search(pattern, s));

    destroyString(s);
    destroyString(pattern);

    system("pause");
    return 0;
}

String initString_null()
{
    String s = (String)malloc(sizeof(stirng_block));
    s->size = 0;
    s->len = 0;
    s->str = NULL;

    return s;
}

String initString_size(int size)
{
    String s = (String)malloc(sizeof(stirng_block));
    s->size = size;
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

}

int KMP_Search(const String pattern, const String s)
{
    int i = 0, j = 0;   // i，j 分别是目标串和模式串的索引
    int next[pattern->len];

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
    }

    return (j == pattern->len) ? (i - pattern->len) : -1;
}