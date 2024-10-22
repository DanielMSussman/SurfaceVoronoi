#include "Xin_Wang.h"
#include <iostream>
using namespace std;

using namespace Model3D;
using namespace Geodesic;
int main()
{
	CRichModel model("../data/sphere.obj");
	model.LoadModel();
	model.PrintInfo(cout);

	set<int> destinations;
	CXin_Wang alg(model, 0, 0);
	alg.Execute();
	cout << alg.GetMaxDistance() << endl;
	alg.GetDistanceField();
    return 0;
}
