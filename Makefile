mpi:
	mpic++ -lrt comb_part_mpi.cpp -o out
	sbatch job.sh

omp:
	g++ -lrt comb_part_omp.cpp -o out -fopenmp
	./out >> comb_part_omp

py:
	python comb_parallel.py
