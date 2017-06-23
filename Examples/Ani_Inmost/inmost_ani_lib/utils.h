#ifndef UTILS_INMOST_ANI_LIB
#define UTILS_INMOST_ANI_LIB
#include <iostream>
#include <string>
#include <fstream>
#include "inmost.h"
void RepartitionStatistics(INMOST::Mesh *m, std::ostream &os);
void SaveMatrix(INMOST::Sparse::Matrix &mat, int MaxInd,MPI_Comm comm) ;
void WriteTags(std::string filename, INMOST::Mesh *m, std::vector<INMOST::Tag> tags);
void WriteTags_vtk(std::string filename, INMOST::Mesh *m, std::vector<INMOST::Tag> tags) ;
void WriteTags_pvtk(std::string filename, INMOST::Mesh *m, std::vector<INMOST::Tag> tags) ;
#endif
