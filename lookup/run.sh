#!/bin/bash

#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --time=00:01:00
#SBATCH --partition=shas-testing
#SBATCH --output=mpi-job.%j.out

module purge
module load intel
module load impi

echo "== Run the job with four processes =="
# echo "== Not sure if we need to include make=="
make
mpirun -np 4 ./main
echo "== End of Job =="