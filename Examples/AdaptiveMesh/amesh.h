#ifndef _AMESH_H
#define _AMESH_H
#include "inmost.h"

namespace INMOST
{
	class AdaptiveMesh
	{
		Mesh * m;
		Model * model;
		ElementSet root; //< Root set that links all the other sets for coarsements
		//TagInteger tag_status;
		TagInteger set_id;
		//TagInteger tag_an; 
        int rank;
        int size;
		/// Prepare sets for coarsements.
		/// Do not do this in constructor, since mesh may contain no cells.
		void CheckParentSet(std::string file, int line, TagInteger indicator);
		void PrepareSet();
        //void PrintSetLocal(std::string offset, ElementSet it, std::stringstream& ss);
        //void SynchronizeIndicated(TagInteger& indicator);
		void SetNewOwner(ElementSet set, TagInteger owner);
		void SetNewProcs(ElementSet set, TagIntegerArray procs);
		void RestoreParent(ElementSet set);
	public:
		TagReference parent_set; //<Link to the set that contains an element.
		TagReferenceArray hanging_nodes; //< Link to current hanging nodes of the cell.
		TagInteger level; //< Refinement level of the cell
		//TagReferenceArray ref_tag; //<Link to the set that contains an element.
		Storage::integer GetLevel(const Storage & e) {return level[e];}
        void SynchronizeSet(ElementSet set);
		AdaptiveMesh(Mesh & m);
		~AdaptiveMesh();
		/// Indicator must be 1 on cells to be refined
		/// and 0 on all other cells
		bool Refine(TagInteger & indicator);
		bool Coarse(TagInteger & indicator);
		/// Delete all data related to mesh refinement-coarsement.
		void ClearData();
		void PrintSet(std::ostream & fout, ElementSet set);
		void SetModel(Model * mm) {model = mm;}
		void Repartition();
        //void Test();
        //void PrintMesh(std::ostream& os, int cell = 0, int face = 0, int edge = 0, int node = 0);
        //void PrintSet();
        //void UpdateStatus();
        //void test_sets();
	};
}

#endif //_AMESH_H
