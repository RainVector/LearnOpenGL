#include <iostream>
#include "volumetricMesh.h"
#include "volumetricMeshLoader.h"

using std::cin;
using std::cout;
using std::endl;


int main()
{
	char inputFilename[96] = "turtle-volumetric-homogeneous.veg";
	VolumetricMesh* vMesh = VolumetricMeshLoader::load(inputFilename);
	if (vMesh == NULL)
		cout << "Error:faild to load mesh." << endl;
	else
	{
		cout << "Success! Number of vertices: " << vMesh->getNumVertices()
			<< " Number of elements : " << vMesh->getNumElements() << endl;

	}
	return 0;
}