#include "GVD_RVD.hpp"
#include<vector>
#include <tclap/CmdLine.h>

using namespace std;
using namespace GVD;
using namespace TCLAP;

void copmuteGvdExample() {
}

int main(int argc, char*argv[])
    {
    CmdLine cmd("interface to the SurfaceVoronoi libraries",' ',"V1");

    ValueArg<string> meshSwitchArg("m","meshSwitch","filename of the mesh you want to load",false,"../exampleMeshes/bunny.obj","string",cmd);
    /*ValueArg<string> pointsSwitchArg("s","sourceSwitch","filename of the source points you want to compute the geodesic voronoi diagram of",false,"../exampleMeshes/samplePoints.txt","string",cmd);*/

    //parse the arguments
    cmd.parse( argc, argv );

    string meshName = meshSwitchArg.getValue();
    /*string sourceName = pointsSwitchArg.getValue();*/

	Model3D::CRichModel model(meshName);
	model.LoadModel();
	model.PrintInfo(std::cerr);

	set<int>sources;

	int ApproSitesNum = 500;
	for (int i = 0; i < model.GetNumOfVerts(); ++i) {
		if (i % (model.GetNumOfVerts() / ApproSitesNum) == 0) {
			sources.insert(i);
		}
	}

        auto startTime = std::chrono::high_resolution_clock::now();
	auto res2 = GetGVD_Bisectors(model, sources);
        auto endTime = std::chrono::high_resolution_clock::now();
    double t = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
	cerr << "GVD total time: " << t << "  seconds..." << endl;
	WriteLineObjFile(res2, "geodesicVoronoi_result.obj");
	return 0;
}
