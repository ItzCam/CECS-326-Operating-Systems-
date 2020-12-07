ReadMe File - Antonio Hughes/Sandra Chavez

Hello! To run our program simply follow these steps!

1. Download file, “Project3.c” into the directory of your choice
2. Create a file named “Makefile”, open the file in text editor, and input the following

	CC = gcc
	CFLAGS = -pthread -o sorting
	project3:
	  ${CC} ${CFLAGS} Project3.c
	
	clean:
	   rm sorting 
3. You should now see a file named “Makefile” with a hammer icon in the middle

4. In that same directory open the terminal, and input the following commands

	ls -> this is to list everything is in the directory

	make -> this will run the Makefile to compile the code (You should now see the contents of the Makefile displayed on the terminal)
5. To run the code, input the following:
		./sorting
		After runnning the executable, input the size n of the array (PRESS ENTER when done) 
		Then, input the numbers with a space in between (PRESS ENTER When done)