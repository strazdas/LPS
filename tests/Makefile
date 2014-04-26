batch:
	g++ -lrt comb_part_omp.cpp -o out -fopenmp
	./out >> comb_part_omp

main:
	# for threads in 1 2 4 8 16 32 64 128 ; do \
	# echo $$threads ; 
	mpic++ -lrt comb_part_mpi2.cpp -o out#; \
	#mpirun -np $$threads ./out >> comb_part_mpi; \
	# done

	# g++ -lrt loop_omp.cpp -o sleep -fopenmp
	# ./sleep >> loop_omp

sleep_omp:
	g++ -lrt sleep.cpp -o sleep -fopenmp
	./sleep >> sleep_res
	cat sleep_res

mpi:
	mpic++ -lrt mpi_comb_part_parallel.cpp -o mpi_comb_part
	mpirun -np 16 ./mpi_comb_part

all:
	g++ comb_part_parallel.cpp -o ../comb_part -fopenmp

test:
	g++ --std=c++0x -fopenmp test.cc -o test

parallel_test:
	g++ --std=c++0x -fopenmp parallel.cpp -o p4

py_parallel:
	python comb_parallel.py

c:
	g++ comb_part.cpp -o ../comb_part -fopenmp
