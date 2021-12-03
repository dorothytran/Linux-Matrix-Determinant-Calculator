# Linux-Concurrent-Matrix-Determinant-Calculator


## DESCRIPTION
This concurrent program developed uses Linux shared memory that creates three child processes from a parent process to compute the determinant of a given 3 x 3 input matrix of integers. The program will use Gaussian elimination for each row calculation and save the variables into shared memory which can be accessed by each process.
Given a matrix M, where:
M = a  b  c
    d  e  f
    g  h  i

The application consists of one source file for execution that includes 2 test cases which will test the concurrent program with different intialized sets of data values to ensure functionality of the program:
```DET.c		(main C source file)```


The application is supported by a single header file that contains delcarations:
```DET.h		(header file for DET.c)```




## INSTALLATION
To successfully run the program, the user must have access to Linux OS and Fedora 30 Workstation.



## USAGE
#### Program Compilation
The program can be executed after opening the TAR file with the required C files onto the Linux terminal. 
First, please change the current directory to the directory containing these files by using the command cd.
To compile this program type the following commands onto the terminal when the current directory is the required directory...

##### Running DET.c file
```
$ gcc DET.c -o DET
$ ./DET
```


## RESULTS
After compilation, the program should display information about each row in the matrix such as the determinant calculation each row has executed, the largest integer in each respective row, and the elapsed runtime of the program after each process completes execution.
Finally, the program should output the calculated determinant of the input matrix and the largest integer of the matrix.

To test the various test cases provided in the DET.c source file, please comment out the initialized mandatory input data provided using '/* code here */' and uncomment the test case initializations.

### Test Case 1
The input matrix for Test Case 1 was provided:
````
10  5  9
3  15  4
7  12  20
````

#### Test Case 1: Output on the Terminal
```
Child Process: working with element 1 of D
Calculation 1 = 2520
Largest Integer in Row 1 = 10
Elapsed Time: 82 micro sec

Child Process: working with element 2 of D
Calculation 2 = 160
Largest Integer in Row 2 = 15
Elapsed Time: 124 micro sec

Child Process: working with element 3 of D
Calculation 3 = -621
Largest Integer in Row 3 = 20
Elapsed Time: 136 micro sec

Calculated Matrix Determinant = 1739
Largest Integer of the Matrix = 20
```
After compiling the DET.c program, the expected results of a Matrix Determinant of 1739 and a largest integer value of 20 was obtained.

### Test Case 2
The input matrix for Test Case 2 was provided:
``` 
50  75  90
24   9  14
40  29  95
```

##### Test Case 2: Output on the Terminal
```
Child Process: working with element 1 of D
Calculation 1 = 22450
Largest Integer in Row 1 = 90
Elapsed Time: 141 micro sec

Child Process: working with element 2 of D
Calculation 2 = 129000
Largest Integer in Row 2 = 24
Elapsed Time: 129 micro sec

Child Process: working with element 3 of D
Calculation 3 = 30240
Largest Integer in Row 3 = 95
Elapsed Time: 300 micro sec

Calculated Matrix Determinant = -76310
Largest Integer of the Matrix = 95
```
After compiling the DET.c program, the expected results of a Matrix Determinant of -76310 and a largest integer value of 95 was obtained.

The provided test cases show that the program works with various different integers and combinations of matrix values as the expects results were achieved.


## LICENSE
Copyright 2021 Dorothy Tran. All rights reserved.
