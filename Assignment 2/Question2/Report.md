<h2> <b> Assignment 2.2 </b> </h2>
<hr>

<br>

<h3> <b> <u> Methodology </u> </b> </h3>
<hr>
<br>
<p>
1. Writing a syscall <code> kernel_2d_memcpy </code>  to do the mentioned task in the assignment. <br>
2. Add the syscall in the syscall table present in <code> arch/x86/entry/syscalls/syscall_64.tbl</code>. <br>
3. Add the syscall_define4 into <code>arch/linux 5.19.8/kernel/sys.c</code>. <br>
3. Recompile the kernel, compile the program and run it.
</p>

<br> 

<h3><b><u> The syscall </u></b></h3>
<hr>

<br>

<p>

```cpp 
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
```       

- The above syscall takes 4 arguments, the first two are the pointers to the matrices, the third and fourth are the number of rows and columns respectively. <br>
- Creates a temporary matrix which acts as an intermediate. <br>
- Using the copy_from_user(), the contents of the temporary matrix are copied into the second matrix. If 0 is returned, the operation is successful. If not, an error is printed.<br>
- Using the copy_to_user function, the contents of the temporary matrix are copied into the first matrix. If 0 is returned, the operation is successful. If not, an error is printed.<br>
- Finally the syscall returns 0 and copying is successful.<br>
</p>

<br>

<hr style = "border-style: dotted;">
<center><b> THE END </b></center>
<hr style = "border-style: dotted;">
