<h1> <b> Shellinator </b></h1>
<p> Shellinator is a shell script that allows you to create a shell that can be used to run shell commands. </p>
<hr> 

<br>
<h2> <b> Usage </b> </h2>

``` bash
 ./Shellinator
```
<br>
<hr>

<br>
<h2> <b> Commands </b> </h2>
<br>
<ul>
<li> <b>
cd </b> - Change directory </li>
<li> <b> ls </b> - List directory contents 
<ul> <li> <b> -a </b> - List all files </li> 
<li> <b> -l </b> - List all files with details </li> 
</ul>

<li> <b> pwd </b> - Print working directory </li>
<li> <b> cat </b> - Concatenate files and print on the standard output
<ul>
<li> <b> -n </b> - Number all output lines </li>
<li> <b> -b </b> - Display non blank lines </li>
</li>
</ul>

<li> <b> rm </b> - Remove files or directories 
<ul> <li> <b> -f </b> - Remove file </li>
<li> <b> -v </b> - Remove verbosely </li>
</li>
</ul>

<li> <b> mkdir </b> - Make directories 
<ul>
<li> <b> -m </b> - Set file mode (as in chmod) </li>
<li> <b> -v </b> - Print a message for each created directory </li>
</li>
</ul>

<li> <b> date </b> - Print or set the system date and time 
<ul>
<li> <b> -t </b> - Print time </li>
<li> <b> -w </b> - Print weekday </li>
</li>
</ul>

<li> <b> echo </b> - Display a line of text </li>
<li> <b> help </b> - Display help </li>
<li> <b> exit </b> - Exit the shell </li>
</ul>
<br>
<hr>
<br>
<h2> <b> Errors Handled</b> </h2>
<br>
<ul>
<li> Fork Errors </li>
<li> Invalid command </li>
<li> Invalid arguments </li>
</ul><br>

<hr>
<br>

<h2> <b> Test Cases </b></h2>
<br>
<ul>
<h2> Test Case 1 </h2>
<ul>
<li> ls . </li>
<li> ls -l . </li>
<li> ls -a . </li>
</ul>
<br>
<h2> Test Case 2 </h2>
<ul>
<li> mkdir -v testing</li>
<li> mkdir &t testing2 </li>
<li> rm -v testing </li>
<li> rm testing2 </li>
</ul>
<br>
<h2> Test Case 3 </h2>
<ul>
<li> cat -n README.md </li>
<li> date </li>
<li> date -t </li>
<li> date -w </li>
</ul>
</ul>
<br>
<hr>