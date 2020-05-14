# include <stdio.h>
# include <stdlib.h>

int GetDateInfo ( char chr, char** argv ){
    static int i=0;
    int j = 0;

    char temp[10];

    while( argv[1][i] != chr ){
        temp[j] = argv[1][i];
        i++;
        j++;
    }
    // 截断
    temp[j] = '\0';
    
    // 越过字母信息
    i++;

    return atoi(temp);
}

int main( int argc, char** argv )
{
    unsigned int year, month, day, hour, minute, second;

    year = GetDateInfo( 'Y', argv );
    month = GetDateInfo( 'M', argv );
    day = GetDateInfo( 'D', argv );
    hour = GetDateInfo( 'h', argv );
    minute = GetDateInfo( 'm', argv );
    second = GetDateInfo( 's', argv );

    unsigned long result;
    month += year*12;
    day += month*30;
    hour += day*24;
    minute += hour*60;
    result = minute*60+second;
    
    printf("%d\n", result);

    system("pause");
    return 0;
}