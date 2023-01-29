# include <stdio.h>
# include <stdlib.h>
# include <sys/syscall.h>
# include <unistd.h>

# define SYS_kernel_2d_memcpy 451

void printMatrix(float *matrix, int rowsize, int colsize);

void printMatrix(float *matrix, int rowsize, int colsize)
{
    int i, j;
    for (i = 0; i < rowsize; i++)
    {
        for (j = 0; j < colsize; j++)
        {
            printf("%f ", matrix[i * colsize + j]);
        }
        printf("\n");
    }
}

int main()
{
    int i, j;

    float matrix1[5][2] = {{10.0, 20.0}, {30.0, 40.0}, {50.0, 60.0}, {70.0, 80.0}, {90.0, 100.0}};
    float matrix2[5][2] = {{10.0, 10.0}, {20.0, 20.0}, {30.0, 30.0}, {40.0, 40.0}, {50.0, 50.0}};

    printf("Initial Matrix1 and Matrix2:\n");
    printf("\n");

    printf("Matrix 1: \n");
    printMatrix(&matrix1[0][0], 5, 2);
    printf("\n");

    printf("Matrix 2: \n");
    printMatrix(&matrix2[0][0], 5, 2);
    printf("\n");

    int operation = syscall(SYS_kernel_2d_memcpy, matrix1, matrix2, 5, 2);

    if (operation < 0)
    {
        printf("Error! Kernel 2D memcpy failed!\n");
        exit(1);
    }

    else
    {
        printf("Kernel 2D memcpy successful!\n");
        printf("\n");

        printf("Final matrix1 and matrix2:\n"); 
        printf("\n");

        printf("Matrix 1: \n");
        printMatrix(&matrix1[0][0], 5, 2);
        printf("\n");

        printf("Matrix 2: \n");
        printMatrix(&matrix2[0][0], 5, 2);
        printf("\n");
    }

    return 0;
}