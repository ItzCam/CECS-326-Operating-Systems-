ReadMe File - Antonio Hughes/Sandra Chavez

Hello! To run our program simply follow these steps!

1. Download files, “Project2.c” & “Proj2.h” into the directory of your choice
2. Create a file named “Makefile”, open the file in text editor, and input the following

	CC = gcc
	CFLAGS = -pthread -o p2
	
	project2:
	  ${CC} ${CFLAGS} Project2.c
	
	clean:
	   rm p2 

3. You should now see a file named “Makefile” with a hammer icon in the middle

4. In that same directory open the terminal, and input the following commands

	ls -> this is to list everything is in the directory

	make -> this will run the Makefile to compile the code (You should now see the contents of the Makefile displayed on the terminal)

5. To run the code, input the following:
		./p2 (first command line parameter) (second command line parameter)
first command line parameter: represents the number of students entering the office 
second command line parameter: represents the capacity of the professor's office 