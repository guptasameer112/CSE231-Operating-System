<h2><b> Assignment 2.1(a) </b></h2>
<hr>

<br>

<h3><b><u> Explaination </u></b></h3>
<hr>

<br>

- There are three count functions, <code>countA()</code>, <code>countB()</code>, <code>countC()</code>, which all count from 1 - 2^32. 
- These three functions are using three different threads to run, <code>ThrA</code>, <code>ThrB</code>, <code>ThrC</code>.
- ThrA runs countA() using scheduling policy <code>SCHED_OTHER</code>, ThrB runs countB() using scheduling policy <code>SCHED_FIFO</code>, ThrC runs countC() using scheduling policy <code>SCHED_RR</code>.
- The runtime of each thread is calculated by the difference between the start time and the end time when the respective count functions run.
- By changing the priority of each thread, we can see the difference in the runtime of each thread. 
- A <u>histogram</u> is plotted to show the difference in the runtime of each thread and each priority value.

<br>

<ul>

```cpp
pthread_setschedparam(ThrA, SCHED_OTHER, &paramA);
``` 
It is used to set the scheduling policy and priority of the thread ThrA to SCHED_OTHER and paramA respectively.

<br>

</ul>

<b> The three threads run on a single processor and the priority of each thread is changed, providing us different time values. </b>

<br>


<h3><b><u> Sample Input </u></b></h3>
<hr>
<br>
<u><i>(SCHED_OTHER = 0, SCHED_RR = 41, SCHED_FIFO = 21)</i></u>

<br>

<h3><b><u> Output</u></b></h3>
<hr>
<br>

<ul>
<li><b><u> Case 1 </u></b></li>
<ul>
17.478195, 9.801696, 9.347985
</ul>
<li><b><u> Case 2 </u></b></li>
<ul>
17.186481, 9.406047, 9.018146
</ul>
<li><b><u> Case 3 </u></b></li>
<ul>
17.320831, 9.566162, 9.136702
</ul>
<li><b><u> Case 4 </u></b></li>
<ul>
17.042877, 9.585662, 8.938115
</ul>
<li><b><u> Case 5 </u></b></li>
<ul>
17.090416, 9.430449, 9.051058
</ul>
<li><b><u> Case 6 </u></b></li>
<ul>
17.193245, 9.475475, 9.141013
</ul>
<li><b><u> Case 7 </u></b></li>
<ul>
17.411057, 9.687742, 9.227763
</ul>
<li><b><u> Case 8 </u></b></li>
<ul>
17.152378, 9.568287, 9.126139
</ul>
<li><b><u> Case 9 </u></b></li>
<ul>
17.148756, 9.506135, 9.140384
</ul>
<li><b><u> Case 10</u></b></li>
<ul>
17.494410, 9.591954, 9.295230
</ul>
</ul>

<hr>
<br>
<h3><u> NOTES </u></h3>
<ul>
<li> As confirmed by Professor Arani, nice() and param.setpriority() are also allowed in this assignment. </li>
<li> Readings were found to be correct by him </li>
</ul>

 <br>
<hr style = "border-width:5px; background-color:lightgreen">
<br><br>

<h2><b> Assignment 2.1(b) </b></h2>
<hr>

<br>

<h3><b><u> Explaination </u></b></h3>
<hr>

<br>

- The parent process creates three child processes using <code>fork()</code> function and <code>execl()</code>.
- A new child is forked in the <code>else</code> of the previous child.
- The process uses a <code>bash script</code> to compile a copy of the kernel.
- The running time of the process is calculated by the difference between the start time and the end time when the respective process runs.

<br>

<h3><u><b> Output </b></u></h3>
<hr>
<ul>
<li> <b>Time taken to compile the 1st kernel (OTHER): </b> 
<ul>
<li> <b>real:</b> 32m27.699s </li>
<li> <b>user:</b> 52m59.693s </li>
<li> <b>sys: </b> 5m44.172s </li>
</ul>
</li>

<li> <b>Time taken to compile the 2nd kernel (FIFO): </b>  
<ul>
<li> <b>real:</b> 16m22.746ss </li>
<li> <b>user:</b> 26m15.882s </li>
<li> <b>sys: </b> 2m47.783s </li>

</ul>
</li>

<li> <b>Time taken to compile the 3rd kernel (RR): </b> 

<ul>
<li><b> real:</b> 22m29.018s </li>
<li><b> user:</b> 34m37.653s </li>
<li><b> sys: </b> 4m2.525s </li>
</ul>

</li>
</ul>

<br>

<hr>
<br>
<h3><u> NOTES </u></h3>
<ul>
<li> As confirmed by him, sequential execution is allowed, due to space issues in the artix system and problem in space expansion. </li>
<li> Priority values are not to be changed. </li>
<li> Scheduling classes have been changed for every forking process. </li>
<li> For Blocking and Non-Blocking waitpid(), it is not needed for sequential execution, however if done in parallel is done using <code> waitpid(-1, NULL, 0). </code>
</li>
</ul>
<br>

<hr style = "border-style: dotted;">
<center><b> THE END </b></center>
<hr style = "border-style: dotted;">
