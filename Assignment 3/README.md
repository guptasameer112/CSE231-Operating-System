<h1> Assignment 3 </h1>

<h2><u> Question 1 </u></h2>

<h3><b> q1a1.c </b></h3>

This is a program that simulates the "dining philosophers" problem using pthreads and semaphores in C.

The dining philosophers problem is a classic example of a problem in concurrent programming that involves multiple threads trying to access shared resources. In this case, the shared resources are forks, and the threads are philosophers.
The program creates an array of semaphores, one for each fork, and initializes them with a value of 1 (i.e., available). Each philosopher thread then enters a loop in which it "thinks" for a moment, takes its forks, eats for a moment, puts the forks down, and then "thinks" again.
The takeForks() and putForks() functions are used to acquire and release the forks. The sem_wait() and sem_post() functions are used to manipulate the semaphores.
The program uses pthreads to create and manage the philosopher threads. The pthread_create() function is used to create a new thread, and the pthread_join() function is used to wait for a thread to complete.
Uses Strict Ordering and therefore there is no deadlock problem as one philosopher at a time is allowed to it.

<h3><b> q1a2.c </b></h3>

This code is a solution to the dining philosophers problem that uses semaphores to synchronize the philosopher threads and manage access to the forks. The semaphores are used to ensure that each philosopher can only pick up the forks if they are both available, and that no more than four philosophers can be seated at the table at the same time.

Some changes that were made to the original code include:

Adding a semaphore "table" to limit the number of philosophers seated at the table to four.
Changing the modulo operation in the takeForks() and putForks() functions to use 4+1 instead of 5, since there are only four forks available.
Adding sitOnTable() and leaveTable() functions to manage access to the table using the "table" semaphore.

<h3><b> q1b1.c </b></h3>

In this implementation, the philosopher's threads are implemented using the pthread_create and pthread_join functions, which are part of the POSIX thread library. Each philosopher is represented by a separate thread that executes the PhiloFunction function.

The PhiloFunction function simulates the actions of a philosopher. It first enters a thinking state, then tries to acquire the forks to the left and right of it using the takeForks function. Once it has acquired both forks, it eats from a randomly chosen saucebowl and then returns the forks to their original positions using the putForks function. After eating, the philosopher enters a thinking state again and the process repeats.

The takeForks and putForks functions use semaphores to ensure that only one philosopher can use a fork at a time. The semaphores are initialized using the sem_init function before the philosopher threads are created.

The thinking function simply puts the thread to sleep for a short time to simulate the philosopher thinking.

<h3><b> q1b2.c </b></h3>

In this version, the sitOnTable function is used to acquire the table semaphore and the saucebowl semaphore before a philosopher starts eating. The leaveTable function is used to release the saucebowl semaphore and the table semaphore after the philosopher finishes eating.

The table semaphore is initialized to 4, which means that up to 4 philosophers can sit at the table at the same time. The saucebowl semaphore is initialized to 2, which means that there are two saucebowls available for the philosophers to eat from.

By using these additional semaphores to control access to the table and saucebowls, the program ensures that no more than 4 philosophers are sitting at the table at the same time, and no more than 2 philosophers are eating from the saucebowls at the same time. This helps to prevent deadlock, which can occur when all philosophers are trying to acquire the forks they need to eat simultaneously

<hr>
<br>

<h2><u> Question 2 </u></h2>

<h3><b> P1_FIFO.c and P2_FIFO.c </b></h3>

This program creates a FIFO file and then writes the messages to it. The program then waits for the message to be read by the other program. The messages along with ids are printed on the console and the time is calculated for all these messages.

<h3><b> P1_Socket.c and P2_Socket.c </b></h3>

This program creates a socket and then writes the messages to it. The program then waits for the message to be read by the other program. The messages along with ids are printed on the console and the time is calculated for all these messages.

<h3><b> P1_SharedMemory.c and P2_SharedMemory.c </b></h3>

This program creates a shared memory and then writes the messages to it. The program then waits for the message to be read by the other program. The messages along with ids are printed on the console and the time is calculated for all these messages.

<hr>

<br>
<h2><u> Question 3 </u></h2>

<h3><b> KernelModule.c </b></h3>

This program creates a kernel module which prints the pid, user_id, pgid, command path. 

<b> command to run after copying Question3 directory to kernel directory: </b>
<br>
<code>
>sudo make <br>
sudo insmod KernelModule.ko <br>
sudo rmmod KernelModule.ko <br>
dmesg
</code>

<br>

<hr>










