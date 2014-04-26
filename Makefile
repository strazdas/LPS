omp:
	g++ -lrt comb_part_omp.cpp -o out -fopenmp
	./out >> comb_part_omp

mpi:
	mpic++ -lrt comb_part_mpi.cpp -o out
	mpirun -np 4 ./out >> comb_part_mpi

bash:
	sbatch job.sh

py:
	python comb_parallel.py
