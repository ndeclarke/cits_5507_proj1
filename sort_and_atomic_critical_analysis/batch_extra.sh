#!/bin/sh -l

#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:10:00

#export OMP_PLACES=cores 
#export OMP_PROC_BIND=close

#SBATCH --cpus-per-task=128
SCHOOL=100000
STEPS=1000
OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

module load gcc
cc -fopenmp -Wall -Werror -pedantic p_fish_school_extra.c timer.c sorter.c -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -DREDUCTION -DBARY_ATOMIC -o p_fish_school_extra -lm 
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./p_fish_school_extra
done

