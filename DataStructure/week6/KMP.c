# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define NotFound -1

typedef int Position;

void buildMatch(char* pattern, int* match)
{
    int j, k;
    int m = strlen(pattern);    /* O(m) */
    match[0] = -1;

    for (j = 1; j < m; j++) {   /* O(m) */
        k = match[j - 1];
        while ((k >= 0) && (pattern[k + 1] != pattern[j])) {
            k = match[k];
        }
        if (pattern[k + 1] == pattern[j]) {
            match[j] = k + 1;
        } else {
            match[j] = -1;
        }
    }
}

Position KMP(char* str, char* pattern)
{
    int n = strlen(str);    /* O(n) */
    int m = strlen(pattern);/* O(m) */
    int s = 0, p = 0;

    if (n < m) {
        return NotFound;
    }

    int* match = (int*)malloc(m * sizeof(int));
    buildMatch(pattern, match);

    while (s < n && p < m) {
        if (str[s] == pattern[p]) {
            s++;
            p++;
        } else {
            if (p > 0) {
                p = match[p-1] + 1;
            } else {
                s++;
            }
        }
    }
    free(match);
    return (p==m) ? (s-m) : NotFound;
}



int main()
{
/*     char str[] = "This is a simple example";
    char pattern[] = "simple";

    Position p = KMP(str, pattern);
    if (p == NotFound) {
        printf("NotFound.\n");
    } else {
        printf("Position: %d \n", p);
    } */


    char* pattern = "ababaa";
    int match[strlen(pattern)];

    buildMatch(pattern, match);

    for (int i = 0; i < strlen(pattern); i++) {
        printf("%d ", match[i]);
    }

    putchar('\n');



    system("pause");
    return 0;
}

