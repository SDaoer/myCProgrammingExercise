# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define TOP_NUM 20
# define WORD_LEN 50

/*
选择哈希算法：time33算法
【对冲突选择链式扩展（最后补充，应该不会有冲突）】
用数组构建一张哈希表，大小是 unsigned short 的取值范围
表中次数最多的 20个元素，提取出来，作为优先队列
    如果表中有元素出现次数超过优先队列中的最少次数，则替换
    每次对表中元素更新，就看看新更新的元素次数是否超过队列中最少次数元素
*/

typedef struct {
    char word[WORD_LEN];// 单词
    int hash_seq; // hash序列号
} TopWord;

int HashTable[65537] = {0}; // 0-65535 作为 hash_seq，65536 作为 top榜的初始化值

unsigned short Time33 ( char* str );
/* 判断是否是字母 */
int is_char ( char c );
/* 获取下一个单词 */
char* next ( FILE* fp );
/* 对 top榜单排序 */
void sort_top ( TopWord top[] );
/* 判断是否在榜 */
int in_top ( TopWord top[], int hash_seq );
/* 初始化表单 */
void InitializeTop ( TopWord top[] );
/* 输出榜单 */
void OutputTop ( TopWord top[] );


int main()
{
    char* word = NULL;
    int hash_seq;
    int cnt=0;
    TopWord top[TOP_NUM];
    InitializeTop(top);
    
    int last = HashTable[top[0].hash_seq];

    FILE* fp = fopen( "D:\\VS Code\\C\\Algorithmic practice\\a-tale-of-two-cities.txt", "r" );
    if(fp){
        while(1){
            word = next(fp);
            if( word == NULL ){ // 读到 EOF了
                break;
            }

            cnt++;
            hash_seq = Time33(word);
            HashTable[hash_seq]++;

            /* 如果 top榜下限变更，就说明需要重排 top榜（因为只增不减，故只有下限增加时需要注意是否要重排） */
            if( HashTable[top[0].hash_seq] != last ){
                sort_top(top);
            }
            
            /* 更新的元素在榜单里，就不需要做任何，不在的话，就要判断，是否超过了榜单下限 */
            if( !in_top( top, hash_seq ) ){
                /* 超过下限，需要挤掉下限，没超过就不需要做任何 */
                if( HashTable[hash_seq] > HashTable[top[0].hash_seq] ){
                    top[0].hash_seq = hash_seq;
                    strcpy( top[0].word, word );
                }
            }
            
        }
    }else{
        puts("Can't open the file!");
    }

    OutputTop(top);
    printf("Total Num: %d\n", cnt);
/*     cnt = 0;
    for( int i=0; i < 65537; i++){
        if(HashTable[i]){
            cnt++;
        }
    }
    printf("There is %d different word.\n", cnt); */
    


    system("pause");
    return 0;
}

unsigned short Time33 ( char* str )
{
    unsigned short hash = 5381;
    while( *str ){
        hash += ( hash << 5 ) + ( *str++ );
    }
    return hash;
}

int is_char ( char c )
{
    return ( 'a' <= c && c <= 'z' ) || ( 'A' <= c && c <= 'Z' );
}

char* next ( FILE* fp )
{
    char c;
    static char* word = NULL;
    /* 下次进入时，先释放上次的空间，因为上次离开函数时，空间仍需要使用，作为返回值使用了 */
    free(word);
    word = NULL;
    word = (char*)malloc(sizeof(char)*WORD_LEN);
    int i = 0;

    // 初始化这块空间
    for( int i=0; i < WORD_LEN; i++ ){
        word[i] = '\0';
    }

    while( word != NULL && word[0] =='\0' ){
        // 没读到单词，直接遇到了其他字符而退出，重读；但如果读到 EOF 就直接结束，也防止在空指针上取元素
        while(1){
            c = fgetc(fp);
            if( c == EOF ){
                // 如果最后一个单词没有标点或其他字符而直接结束，会直接丢弃最后一个单词
                free(word);
                word = NULL;
                break;
            }
            if( !is_char(c) ){
                break;
            }
            word[i] = c;
            i++;
        }
    }

    return word;
}

void sort_top ( TopWord top[] )
{/* 从小到大排序 */
    int i, j;
    TopWord temp;
    for( i=0; i < TOP_NUM-1; i++ ){
        for( j=TOP_NUM-1; j > i; j-- ){
            if( HashTable[top[j].hash_seq] < HashTable[top[j-1].hash_seq] ){
                temp = top[j];
                top[j] = top[j-1];
                top[j-1] = temp;
            }
        }
    }
}

int in_top ( TopWord top[], int hash_seq )
{
    for( int i=0; i < TOP_NUM; i++ ){
        if( top[i].hash_seq == hash_seq ){
            return 1;
        }
    }
    
    return 0;
}

void InitializeTop ( TopWord top[] )
{
    for( int i=0; i < TOP_NUM; i++ ){
        top[i].hash_seq = 65536;
    }
}

void OutputTop ( TopWord top[] )
{
    for( int i=0; i < TOP_NUM; i++ ){
        printf("%s:%d\n", top[i].word, HashTable[top[i].hash_seq]);
    }
}