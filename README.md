compile OpenMP
 gcc -o some_test -fopenmp OpenMpTest.cpp -std=gnu++14 -lstdc++

run OpenMP
 ./some_test 
 set number of threads 
  export OMP_NUM_THREADS=4
  
  
  
  compile MPI
   mpic++ -o test MPI_Test.cpp
   
  run MPI 
   mpiexec -n 4 ./test  
   
  compile
   gcc -o classic main.cpp -std=gnu++14 -lstdc++
   
 run 
   ./classic
