#!/bin/sh -l

#SBATCH --account=courses0101
#SBATCH --partition=debug
#SBATCH --ntasks=1
#SBATCH --ntasks-per-node=1
#SBATCH --time=00:35:00

#export OMP_PLACES=cores 
#export OMP_PROC_BIND=close

#SBATCH --cpus-per-task=4
SCHOOL=1000000
STEPS=1000
OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

module load gcc
cc -fopenmp chunk_p_fish_school.c timer.c -DREDUCTION -DBARY_REDUCTION -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -DSCHED=dynamic -DCHUNK_SIZE=1600 -o chunk_p_fish_school -lm 
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./chunk_p_fish_school
done

cc -fopenmp chunk_p_fish_school.c timer.c -DREDUCTION -DBARY_REDUCTIOND -SCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -DSCHED=dynamic -DCHUNK_SIZE=12800 -o chunk_p_fish_school -lm
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./chunk_p_fish_school
done

cc -fopenmp chunk_p_fish_school.c timer.c -DREDUCTION -DBARY_REDUCTION -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -DSCHED=dynamic -DCHUNK_SIZE=250000 -o chunk_p_fish_school -lm
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./chunk_p_fish_school
done

cc -fopenmp chunk_p_fish_school.c timer.c -DREDUCTION -DBARY_REDUCTION -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -DSCHED=dynamic -DCHUNK_SIZE=50000 -o chunk_p_fish_school -lm
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./chunk_p_fish_school
done

cc -fopenmp chunk_p_fish_school.c timer.c -DREDUCTION -DBARY_REDUCTION -DSCHOOL=$SCHOOL -DSTEPS=$STEPS -DOMP_NUM_THREADS=$OMP_NUM_THREADS -DSCHED=dynamic -o chunk_p_fish_school -lm
for i in {1..10}; do
	srun -N 1 -c $OMP_NUM_THREADS ./chunk_p_fish_school
done
