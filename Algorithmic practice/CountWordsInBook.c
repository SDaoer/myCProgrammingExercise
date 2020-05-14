# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define TOP_NUM 20
# define WORD_LEN 50

/*
ѡ���ϣ�㷨��time33�㷨
���Գ�ͻѡ����ʽ��չ����󲹳䣬Ӧ�ò����г�ͻ����
�����鹹��һ�Ź�ϣ����С�� unsigned short ��ȡֵ��Χ
���д������� 20��Ԫ�أ���ȡ��������Ϊ���ȶ���
    ���������Ԫ�س��ִ����������ȶ����е����ٴ��������滻
    ÿ�ζԱ���Ԫ�ظ��£��Ϳ����¸��µ�Ԫ�ش����Ƿ񳬹����������ٴ���Ԫ��
*/

typedef struct {
    char word[WORD_LEN];// ����
    int hash_seq; // hash���к�
} TopWord;

int HashTable[65537] = {0}; // 0-65535 ��Ϊ hash_seq��65536 ��Ϊ top��ĳ�ʼ��ֵ

unsigned short Time33 ( char* str );
/* �ж��Ƿ�����ĸ */
int is_char ( char c );
/* ��ȡ��һ������ */
char* next ( FILE* fp );
/* �� top������ */
void sort_top ( TopWord top[] );
/* �ж��Ƿ��ڰ� */
int in_top ( TopWord top[], int hash_seq );
/* ��ʼ���� */
void InitializeTop ( TopWord top[] );
/* ����� */
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
            if( word == NULL ){ // ���� EOF��
                break;
            }

            cnt++;
            hash_seq = Time33(word);
            HashTable[hash_seq]++;

            /* ��� top�����ޱ������˵����Ҫ���� top����Ϊֻ����������ֻ����������ʱ��Ҫע���Ƿ�Ҫ���ţ� */
            if( HashTable[top[0].hash_seq] != last ){
                sort_top(top);
            }
            
            /* ���µ�Ԫ���ڰ���Ͳ���Ҫ���κΣ����ڵĻ�����Ҫ�жϣ��Ƿ񳬹��˰����� */
            if( !in_top( top, hash_seq ) ){
                /* �������ޣ���Ҫ�������ޣ�û�����Ͳ���Ҫ���κ� */
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
    /* �´ν���ʱ�����ͷ��ϴεĿռ䣬��Ϊ�ϴ��뿪����ʱ���ռ�����Ҫʹ�ã���Ϊ����ֵʹ���� */
    free(word);
    word = NULL;
    word = (char*)malloc(sizeof(char)*WORD_LEN);
    int i = 0;

    // ��ʼ�����ռ�
    for( int i=0; i < WORD_LEN; i++ ){
        word[i] = '\0';
    }

    while( word != NULL && word[0] =='\0' ){
        // û�������ʣ�ֱ�������������ַ����˳����ض������������ EOF ��ֱ�ӽ�����Ҳ��ֹ�ڿ�ָ����ȡԪ��
        while(1){
            c = fgetc(fp);
            if( c == EOF ){
                // ������һ������û�б��������ַ���ֱ�ӽ�������ֱ�Ӷ������һ������
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
{/* ��С�������� */
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