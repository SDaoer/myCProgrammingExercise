# include <stdio.h>
# include <stdlib.h>

# define ABS(x) ( (x)>0?(x):(-1*(x)) )

typedef struct {
    long zhengshu;
    long fenzi;
    long fenmu;
} RationalNumber;

long gcd ( long a, long b );
long lcm ( long a, long b );
RationalNumber Add2RationalNumber ( RationalNumber* a, RationalNumber* b );
void OutputRationalNumber ( const RationalNumber* a );
void YouLiHua ( RationalNumber* a );
void ToJiafenshu ( RationalNumber* a );
void ToZhenfenshu ( RationalNumber* a );

int main()
{
    int N;
    scanf("%d", &N);
    RationalNumber temp;
    RationalNumber result = {.zhengshu=0,.fenzi=0,.fenmu=1};

    for( int i=0; i < N; i++ ){
        temp.zhengshu = 0;
        scanf("%ld/%ld", &temp.fenzi, &temp.fenmu);   
        //printf("%ld/l%d  ", temp.fenzi, temp.fenmu);
        result = Add2RationalNumber( &temp, &result );
    }

    OutputRationalNumber( &result );

    system("pause");
    return 0;
}

long gcd ( long a, long b )
{
    long mod;

    if( a && b ){
        if( a < b ){
            long t;
            t = a;
            a = b;
            b = t;
        }
    }else{
        return ( (a>b)?a:b );
    }

    mod = a % b;
    while( mod ){
        a = b;
        b = mod;
        mod = a % b;
    }

    return b;
}

long lcm ( long a, long b )
{
    return ( a*b/gcd(a,b) );
}

RationalNumber Add2RationalNumber ( RationalNumber* a, RationalNumber* b )
{
    RationalNumber result = {.zhengshu=0,.fenzi=0,.fenmu=1};

    ToJiafenshu(a);
    ToJiafenshu(b);
    result.fenmu = lcm( a->fenmu, b->fenmu );
    result.fenzi = result.fenmu / a->fenmu * a->fenzi + result.fenmu / b->fenmu * b->fenzi;

    YouLiHua( &result );
    ToZhenfenshu(&result);

    return result;
}

void OutputRationalNumber ( const RationalNumber* a )
{
    if( a->zhengshu ){
        if( a->fenzi ){
            printf("%ld %ld/%ld\n", a->zhengshu, a->fenzi, a->fenmu);
        }else{
            printf("%ld\n", a->zhengshu);
        }
    }else{
        if( a->fenzi ){
            printf("%ld/%ld\n", a->fenzi, a->fenmu);
        }else{
            printf("0\n");
        }
    }
}

void YouLiHua ( RationalNumber* a )
{
    long temp;
    if(a->fenmu){
        temp = gcd( a->fenzi, a->fenmu );
        /* 保证约去正数 */
        temp = ABS(temp);
        a->fenzi /= temp;
        a->fenmu /= temp;
    }else{
        printf("This rational number is wrong:%d/%d\n", a->fenzi, a->fenmu);
    }
}

void ToJiafenshu ( RationalNumber* a )
{
    if(a->zhengshu >= 0){
        a->fenzi += a->zhengshu*a->fenmu;
        a->zhengshu = 0;
    }else{
        a->fenzi *= -1;
        a->fenzi += a->zhengshu*a->fenmu;
        a->zhengshu = 0;
    }
}

void ToZhenfenshu ( RationalNumber* a )
{
    ToJiafenshu(a);
    a->zhengshu = a->fenzi / a->fenmu;
    a->fenzi %= a->fenmu;
    if( a->zhengshu != 0 ){
        /* 如果有整数部分，符号就该在整数部分上了，分子上消去符号位 */
        /* 如果没有符号位，符号才应该在分子上 */
        a->fenzi = ABS(a->fenzi);
    }
}
