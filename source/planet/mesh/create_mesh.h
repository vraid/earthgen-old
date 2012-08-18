#ifndef create_mesh_h
#define create_mesh_h

#define nullptr NULL

class Mesh;

namespace mesh {
	void add_corner (int, Mesh*, int, int, int);
	void add_edge (int, Mesh*, int, int);
	Mesh* create (int);
	Mesh* icosahedron ();
	Mesh* subdivision (const Mesh*);
}

#endif
