#!/bin/sh -l

#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:22:00

#export OMP_PLACES=cores 
#export OMP_PROC_BIND=close

#SBATCH --cpus-per-task=1
SCHOOL=1000000
STEPS=1000
OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

module load gcc
cc -fopenmp s_fish_school.c timer.c -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -o s_fish_school -lm 
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./s_fish_school
done
