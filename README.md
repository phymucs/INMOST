INMOST
======

A toolkit for distributed mathematical modeling

## Install Guide

First define the folder where you want to install INMOST and other optional libraries.
```
export INMOST_LIBS="/home/user/inmost-libs"
```
If it doesn't already exist, create this directory:
```
mkdir -p "$INMOST_LIBS"
```

### PETSc

PETSc can install a lot of other dependencies as well.

The following instructions assume that MPI is already installed and functional. You can use option --download-openmpi to install MPI with PETSc.

These steps can take some time
```
cd "$INMOST_LIBS"
wget http://ftp.mcs.anl.gov/pub/petsc/release-snapshots/petsc-3.4.5.tar.gz
tar zxf petsc-3.4.5.tar.gz
rm -f petsc-3.4.5.tar.gz
cd petsc-3.4.5
export PETSC_DIR="`pwd`"
export PETSC_ARCH=linux-gnu-opt
./configure --download-f-blas-lapack --download-metis --download-parmetis  --useThreads=0 --with-debugging=0 --with-mpi-dir=/usr --with-x=0 –with-shared-libraries=0
make all
```

### INMOST

Download and unpack INMOST source archive.
```
cd "$INMOST_LIBS"
wget https://github.com/INM-RAS/INMOST/archive/master.tar.gz
tar zxf INMOST-master.tar.gz
rm -f INMOST-master.tar.gz
```

We will create separate directory for INMOST compilation.
Depending on your version of gcc compiler you may need one of these flags for `CMAKE_CXX_FLAGS variable`: `"-std=c++11"` or `"-std=c++0x"`.
```
mkdir -p INMOST-build
cd INMOST-build
cmake -DUSE_AUTODIFF=OFF -DUSE_SOLVER_PETSC=ON -DUSE_PARTITIONER_PARMETIS=ON  -DCMAKE_CXX_FLAGS="-std=c++11" -DCOMPILE_EXAMPLES=ON ../INMOST-master
make
```

## Examples 

Several representative examples are provided in source archive.
Here we will try three parallel steps: grid generation, FVM discretization and linear matrix solution.
Each example may be executed in serial or parallel ways.

### Parallel Grid Generation

This example creates simple cubic or prismatic mesh. You can use ParaView to 
```
cd "$INMOST_LIBS/INMOST-build"
cd examples/GridGen
mpirun -np 4 GrdiGen 3 32 32 4
```
Generator parameters are: `ng nx ny nz`
where `ng=3` stands for Prismatic generator and
`ng=4` for Cubic one,
while `nx ny nz` are the mesh dimensions.

File grid.pvtk (as well as grid_X.vtk with X=0,1,2,3) will appear in the current directory.
Run
`paraview --data=grid.pvtk`
and try the following tags in objects to display:
- `P_OWNER_PROCESSOR` – partitioning to processors
- `GLOBAL_ID` – global cell ID number

### Parallel Finite Volume Discretization

This example uses simple two-point FVM scheme to solve Laplace's equation in unit cube domain.
```
cd ../FVDiscr
mpirun -np 4 FVDiscr ../GridGen/grid.pvtk A.mtx b.rhs
```
Files result.pvtk (as well as result_X.vtk with X=0,1,2,3) and A.mtx b.rhs will appear in the current directory.
Run
`paraview --data=grid.pvtk`
and try the following tags in objects to display:
- `Solution` – the solution to the problem
- `K` – tensor K (constant equal to 1 in this example)

### Solve the Matrix stored in mtx format

This example solves the linear system using different solvers.
```
cd ../FVDiscr
mpirun -np 4 MatSolve 0 ../FVDiscr/A.mtx ../FVDiscr/b.rhs
```
Solution time and the true residual will output to the screen.
The first parameter selects the solver:
- `0` – INMOST ILU2
- `1` – INMOST MLILUC
- `2` – ANI3D
- `3` – PETSc

### Other Examples

There are other examples:
```
DrawGrid
DrawMatrix
OctreeCutcell
OldDrawGrid
Solver
```
which can be used without warranty.

