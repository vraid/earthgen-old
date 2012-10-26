#include "parameters.h"
#include "../noise/noise_parameters.h"
#include "../math/vector3.h"
#include <fstream>
#include <stdlib.h>

Parameters::Parameters() {
	grid_size = 7;

	axial_tilt = 0.4;
	axis = Vector3(0,0,1);

	terrain_seed = "";
	iterations = 2000;
	elevation_scale = 8000.0;
	water_ratio = 0.7;

	seasons = 1;
}

Parameters::~Parameters() {
}

Parameters& Parameters::operator = (const Parameters& par) {
	grid_size = par.grid_size;
	axial_tilt = par.axial_tilt;
	axis = par.axis;
	rotation = par.rotation;
	terrain_seed = par.terrain_seed;
	iterations = par.iterations;
	elevation_scale = par.elevation_scale;
	water_ratio = par.water_ratio;
	seasons = par.seasons;
	return *this;
}

namespace parameters {

double check_range_float (double n, const double* a) {
	if (n < a[0]) return a[0];
	if (n > a[1]) return a[1];
	return n;
}
int check_range_int (int n, const int* a) {
	if (n < a[0]) return a[0];
	if (n > a[1]) return a[1];
	return n;
}

Parameters* load () {
	return load("default.txt");
}

Parameters* load (std::string file) {
	Parameters* par = new Parameters();

	if (!std::ifstream("default.txt")) {
		std::ofstream fout (file.c_str(), std::ios::out | std::ios::trunc);
		save(par,"default.txt");
	}
	if (std::ifstream(file.c_str())) {
	
		std::ifstream fin (file.c_str());
		std::string name;
		std::string val;
		std::string s;

		while (!fin.eof()) {
			if (fin.peek() == '#') getline(fin, s);
			getline(fin, name, '=');
			getline(fin, s, ' ');
			getline(fin, val);
			if (name.compare("grid_size ") == 0)
				par->grid_size = check_range_int(atoi(val.c_str()), grid_size_range);
			if (name.compare("axial_tilt ") == 0)
				par->axial_tilt = check_range_float(atof(val.c_str()), axial_tilt_range);
			if (name.compare("terrain_seed ") == 0)
				par->terrain_seed = val;
			if (name.compare("iterations ") == 0)
				par->iterations = check_range_int(atoi(val.c_str()), iterations_range);
			if (name.compare("elevation_scale ") == 0)
				par->elevation_scale = check_range_float(atof(val.c_str()), elevation_scale_range);
			if (name.compare("water_ratio ") == 0)
				par->water_ratio = check_range_float(atof(val.c_str()), water_ratio_range);
			if (name.compare("seasons ") == 0)
				par->seasons = check_range_int(atoi(val.c_str()), seasons_range);
		}
		fin.close();
	}
	return par;
}

void save (const Parameters* par, std::string file) {
	std::ofstream fout (file.c_str(), std::ios::out | std::ios::trunc);
	fout << "# grid\n";
	fout << "grid_size = " << par->grid_size << std::endl;
	fout << "\n# orbit\n";
	fout << "axial_tilt = " << par->axial_tilt << std::endl;
	fout << "\n# terrain\n";
	fout << "terrain_seed = " << par->terrain_seed << std::endl;
	fout << "iterations = " << par->iterations << std::endl;
	fout << "elevation_scale = " << par->elevation_scale << std::endl;
	fout << "water_ratio = " << par->water_ratio << std::endl;
	fout << "\n# climate\n";
	fout << "seasons = " << par->seasons << std::endl;
	fout.close();
}

}
