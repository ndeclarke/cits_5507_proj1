#!/bin/sh -l

#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:05:00

#export OMP_PLACES=cores 
#export OMP_PROC_BIND=close

#SBATCH --cpus-per-task=16
SCHOOL=1000
STEPS=10000
OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

module load gcc
cc -fopenmp p_fish_school.c timer.c -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -o p_fish_school 
for i in {1..30}; do
	srun -N 1 -c $OMP_NUM_THREADS ./p_fish_school
done
