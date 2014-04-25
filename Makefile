omp:
	g++ --std=c++0x -fopenmp comb_part_omp.cpp -o out 

mpi:
	mpic++ comb_part_mpi.cpp -o out
	mpirun -np 4 ./out

py:
	python comb_parallel.py
