#include <stdio.h>

int main() {
    int a[10][10], r, c, i, j;
    int rowSum, colSum;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &r, &c);

    printf("Enter matrix elements:\n");
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    // Sum of rows
    for(i = 0; i < r; i++) {
        rowSum = 0;
        for(j = 0; j < c; j++) {
            rowSum += a[i][j];
        }
        printf("Sum of row %d = %d\n", i+1, rowSum);
    }

    // Sum of columns
    for(j = 0; j < c; j++) {
        colSum = 0;
        for(i = 0; i < r; i++) {
            colSum += a[i][j];
        }
        printf("Sum of column %d = %d\n", j+1, colSum);
    }

    return 0;
}