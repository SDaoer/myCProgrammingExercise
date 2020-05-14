# include <stdio.h>
# include <stdlib.h>

# define N 3

int gcd ( int a, int b );
int lcm ( int a, int b );

typedef struct _rationalNumber{
    int numerator;
    int denominator;
} RationalNumber;

void get_RN ( RationalNumber *a );
void output_RN ( const RationalNumber *a );

RationalNumber RN ( int numerator, int denominator);

RationalNumber add ( const RationalNumber *a, const RationalNumber *b );
RationalNumber substract ( const RationalNumber *a, const RationalNumber *b );
RationalNumber multiply ( const RationalNumber *a, const RationalNumber *b );
RationalNumber divide ( const RationalNumber *a, const RationalNumber *b );

void canonicalize ( RationalNumber *a );

/*
���ù�ϵ��
1��ÿ����������󣬵����� canonicalize ���з����淶��
2��RN �����죩������ get_RN����ȡ������������ canonicalize �����˷����淶��
3��lcm ���������� gcd ����
4��
*/

int main ()
{
/*     RationalNumber a, b, c;
    get_RN (&a);
    get_RN (&b);
    output_RN (&a);
    output_RN (&b);

    c = add ( &a, &b );
    output_RN (&c);
    c = substract ( &a, &b );
    output_RN (&c);
    c = multiply ( &a, &b );
    output_RN (&c);
    c = divide ( &a, &b );
    output_RN (&c); */

    // Q1
    int i;
    RationalNumber q, sum;
    sum = RN( 0, 1 );
    for ( i = 1; i <= N; i++ ){
        q = RN( 1, i );
        sum = add( &sum, &q );
    }
    output_RN ( &sum );

    // Q2
    int k = 1;
    sum = RN( 0, 1 );
    for ( i = 1; i <= N; i++ ){
        q = RN( k, i );
        sum = add( &sum, &q );
        k *= -1;
    }
    output_RN ( &sum );



    system ("pause");
    return 0;
}

int gcd ( int a, int b )
{
    int temp;
    if( a && b ){       // a, b����
        if( a < b ){
            temp = a;
            a = b;
            b = temp;
        }
    }else{              // a, b��������һ��Ϊ�㣬���ط�������Ϊ gcd����Ϊ���򷵻� 0 Ϊ gcd
        return ( (a>b)?a:b );
    }

    int mod = a % b;

    while ( mod )
    {
        a = b;
        b = mod;
        mod = a % b;
    }

    return b;
}

int lcm ( int a, int b )
{
    return (a*b/gcd(a, b));
}

void get_RN ( RationalNumber *a )
{
    printf ("Please input a rational number (divide by '/'):");
    scanf ("%d/%d", &a->numerator, &a->denominator);
    canonicalize (a);
}

void output_RN ( const RationalNumber *a )
{
    printf ("The rational number is %d/%d\n", a->numerator, a->denominator);
}

RationalNumber RN ( int numerator, int denominator)
{
    RationalNumber new;
    new.numerator = numerator;
    new.denominator = denominator;

    canonicalize ( &new );

    return new;
}

RationalNumber add ( const RationalNumber *a, const RationalNumber *b )
{
    RationalNumber ret;

    ret.denominator = lcm( a->denominator, b->denominator );
    ret.numerator = ret.denominator / a->denominator * a->numerator + ret.denominator / b->denominator * b->numerator;

    canonicalize ( &ret );

    return ret;
}

RationalNumber substract ( const RationalNumber *a, const RationalNumber *b )
{
    RationalNumber ret;

    ret.denominator = lcm( a->denominator, b->denominator );
    ret.numerator = ret.denominator / a->denominator * a->numerator - ret.denominator / b->denominator * b->numerator;

    canonicalize ( &ret );

    return ret;
}

RationalNumber multiply ( const RationalNumber *a, const RationalNumber *b )
{
    RationalNumber ret;

    ret.denominator = a->denominator * b->denominator;
    ret.numerator = a->numerator * b->numerator;

    canonicalize ( &ret );

    return ret;
}

RationalNumber divide ( const RationalNumber *a, const RationalNumber *b )
{
    RationalNumber ret;

    ret.denominator = a->denominator * b->numerator;
    ret.numerator = a->numerator * b->denominator;

    canonicalize ( &ret );

    return ret;
}

void canonicalize ( RationalNumber *a )
{
    int gcd_num;

    if ( a->denominator ){  // ��ĸ��Ϊ 0 
        gcd_num = gcd ( a->numerator, a->denominator );

        a->numerator /= gcd_num;
        a->denominator /= gcd_num;
    }else{  // ��ĸΪ 0��������������
        puts("Wrong rational number!");
    }

}
