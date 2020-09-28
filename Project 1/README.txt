ReadMe File - Antonio Hughes/Sandra Chavez

Hello! To run our program simply follow these steps!

1. Download files, “Proj1.c” & “Proj1P2.c” into the directory of your choice

2. Create a file named “Makefile”, open the file in text editor, and input the following
  make: Proj1.c
 
	gcc Proj1.c -pthread -o NoSynch

 	gcc Proj1P2.c -pthread -D FLAG -o Synch

3. You should now see a file named “Makefile” with a hammer icon in the middle

4. In that same directory open the terminal, and input the following commands

	ls -> this is to list everything is in the directory

	make -> this will run the Makefile to compile the code (You should now see the contents of the Makefile displayed on the terminal)

5. To run the program without synchronization, input the following

	./ NoSynch (whatever positive number you want for the # of threads)

	NOTE: Negatives won’t work 

6. To run the program with synchronization, input the following

	./Synch (whatever positive number you want for the # of threads)
