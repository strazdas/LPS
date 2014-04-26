#!/bin/sh
#SBATCH --output=sout
#SBATCH --error=serr
#SBATCH -p short
#SBATCH -n 1

mpirun ./out >> comb_part_mpi
