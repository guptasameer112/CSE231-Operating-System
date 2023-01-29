SYSCALL_DEFINE4(kernel_2d_memcpy, float *, matrix1, float *, matrix2, int, rows, int, cols)
{
    float temp[rows][cols];

    int operation1 = copy_from_user(&temp, matrix2, sizeof(temp));

    if ( operation1 != 0)
    {
        printk("Error! Copy from user failed!\n");
        return -EFAULT;
    }

    int operation2 = copy_to_user(matrix1, &temp, sizeof(temp));

    if ( operation2 != 0)
    {
        printk("Error! Copy to user failed!\n");
        return -EFAULT;
    }

    return 0;
}