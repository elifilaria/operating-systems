Code by: Elif Ilaria Yurtseven
Operating Systems Programming Project Shell

You can compile the code as follows:

gcc -c shell.c
gcc -o shell shell.o

You can run the code as follows:
./shell

Once you run the code you will find yourself in a shell.
If you type the name of an executable with './' before it, it will be executed by the CHILD process after forking the shell. This has been tested and the test print outs are commented out in the code itself.

example : ./hello (I have a hello World! program in my directory, it would print out "Hello World!").


Extra features:

If you want to change directory you will need to trype "chdir" followed by the path to the directory you would like to change to. You will need to write the FULL PATH to this directory.

example: chdir /home/users/yurtse1/OS/lab2 

If you want a list of all the files that are in your current directory you can type 'ls' and this will list you all the files in your current directory.

If you would like to exit the shell it is enough that you type 'exit'.