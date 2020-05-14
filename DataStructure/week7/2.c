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
    /* ��Ŀ���Ĳ�������Ϊ aaabbdaabbde �� aabbd û�в���
     * ģʽ����β����ͬ��ĸ�����ӣ��������©���еڶ���ƥ��ʱĿ�괮
     * ����û�лص�ƥ��λ�õ���һ��������ֱ��ƥ����ȥ
     */
    assign(s, "aaabbdaabbdae");
    assign(pattern, "aabbda");

    printf("\"%s\"��\"%s\"�г���%d��\n", pattern->str, s->str, KMP_SearchAll(pattern, s));

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
    int k = -1, j = 0; // k��j �� pattern ��ǰ������
    next[0] = -1;

    while (j < pattern->len - 1) {
        if (k == -1 || pattern->str[j] == pattern->str[k]) {  // k == -1 ���� k �� pattern[0] �ٴλ��ˣ����޿���
            j++;
            k++;
            next[j] = k;
        } else {
            // �������� k
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
    int i = 0, j = 0;   // i��j �ֱ���Ŀ�괮��ģʽ��������
    int next[pattern->len];
    int times = 0;

    // Ŀ�괮��ģʽ���̣�ֱ�ӷ��� 0
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
    // ��ʾĿ�괮
    for (k = 0; k < s->len; k++){
        if (k == i) {
            printf("_%c_", s->str[k]);
        } else {
            printf("%c", s->str[k]);
        }
    }
    putchar('\n');
    // ��հ�
    for(k = 0; k < i - j; k++) {
        putchar(' ');
    }
    // ��ʾģʽ��
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