#include "GVD_RVD.hpp"
#include<vector>
using namespace std;
using namespace GVD;

void GvdExample() {
	Model3D::CRichModel model("bunny.obj");
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
	WriteLineObjFile(res2, "gvd_rersult.obj");
}

void EDBVDExample() {
	Model3D::CRichModel model("bunny.obj");

	model.LoadModel();
	model.PrintInfo(std::cerr);

	vector<tuple<double, double, double, int>> sources;

	int ApproSitesNum = 1000;
	for (int fid = 0; fid < model.GetNumOfFaces(); ++fid) {
		if(fid%(model.GetNumOfFaces()/ ApproSitesNum)==0)
			sources.push_back(make_tuple(model.Vert(model.Face(fid)[0]).x, model.Vert(model.Face(fid)[0]).y, model.Vert(model.Face(fid)[0]).z, fid));
	}

        auto startTime = std::chrono::high_resolution_clock::now();
	auto res2 = GetLRVD_Bisectors(model, sources);
        auto endTime = std::chrono::high_resolution_clock::now();
    double t = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() / 1000.0;
	cerr << "EDBVD total time: " << t  << "  seconds..." << endl;
	WriteLineObjFile(res2.first, "EDBVD_rersult.obj");

}

int main() {
	GvdExample();
	EDBVDExample();

	return 0;
}
