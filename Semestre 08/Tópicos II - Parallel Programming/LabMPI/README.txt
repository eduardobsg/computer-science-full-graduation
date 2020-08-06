Message Passing Interface
--------------------------
You may use the PDF slides in 'mpi.pdf'. 
3 files are provided:
  * "hello-mpi.c": hello World!
  * "ping-pong.c": ping-pong with MPI.
  * "mslave.c"   : basic Master/Slave program.

Activities.

According to your necessities, you can choose to do all or part of the
following topics. Installing MPI can also be done in Ubuntu with the 
package 'mpich-bin'.

  1) Download and install, for instance, LAM-MPI from http://www.lam-mpi.org. 
  (You may do something like 
   ./configure --prefix=$HOME/lam-7.1.2-install ; make ; make install.)

  2) Compile and run the MPI version of "hello World!" (hello-mpi.c). You
  should use something like:
  mpicc -o hello hello-mpi.c
  mpirun -np 5 ./hello

  3) Take a look at the ping-pong (ping-pong.c). Run it with 1, 2, 3, 4
  processes. What happens? Rewrite the code in order to avoid the problems.

  4) Consider the program 'mslave.c', and transform it so that the master
  may also process its part of the tasks to be run when it does not get any
  result from the slaves. Use MPI_Irecv to do so. Observe how many tasks are
  actually run by the master and by the slaves when executing the program.

  5) Re-write the matrix product 'omp-matrix.c' with MPI. 

  6) Re-write the PI program with MPI. (You probably should use MPI_Reduce - 
  you can look at the program 'mslave-reduce.c' to get help.)

  7) Re-write 'ping-pong' so that it is an real "ping-pong":
  * process 0 must pick up randomly a victime process among the p possible
  ones (i.e. of rank between 1 and MPI_Comm_rank-1), and send it a PING 
  message.
  * whatever process, when is receives a PING message from 0, must send a PONG
  message as answer. 

  The solution must be non-blocking. You may assume that the processes which are
  not envolved in the PING message are running a loop.
