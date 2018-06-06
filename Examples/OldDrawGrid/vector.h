#ifndef _VECTORS_H
#define _VECTORS_H

#include "inmost.h"
#include "coord.h"


namespace INMOST
{
	
	struct vec_t
	{
		coord cnt, dir;
		double length;
		int eid;
	};
	
	class Vectors
	{
	private:
		double max_length;
		double scale;
		Mesh * m;
		ElementType etype;
		std::vector<vec_t> vecs;
	public:
		Vectors(Mesh * m, TagRealArray t, ElementType etype);
		Vectors(const Vectors & b)
		: max_length(b.max_length),  scale(b.scale), m(b.m), etype(b.etype), vecs(b.vecs){}
		Vectors & operator =(Vectors const & b)
		{
			max_length = b.max_length;
			scale = b.scale;
			m = b.m;
			etype = b.etype;
			vecs = b.vecs;
			return *this;
		}
		void SetScale(double s) {scale = s;}
		~Vectors() { vecs.clear(); }
		void Draw(int reduced);
		void SVGDraw(std::ostream & file, double modelview[16], double projection[16], int viewport[4]);
	};

}
#endif
