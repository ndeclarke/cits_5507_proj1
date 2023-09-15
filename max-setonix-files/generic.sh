#!/bin/sh -l

#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=4
#SBATCH --time=00:01:00

#export OMP_PLACES=cores 
#export OMP_PROC_BIND=close

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK 

module load gcc
cc -fopenmp $1.c -o $1 
srun -N 1 -c $OMP_NUM_THREADS ./$1
