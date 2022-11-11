#include "main.h"

int main(int argc, char *argv[])
{
	clSliFile sliFile;
	// clJobSliceFile sliFile;
	clSliceData sliceData;

	if (argc > 1)
	{
		sliFile.readFromFile(argv[1]);
	}
	else
	{
		std::cout << "Input a file name" << std::endl;
	}

	int part = 0;
	int numLayers = sliFile.getLayerCount(part);
	printf("# Number of layers: %d\n", numLayers);

	clSliceData::tyMatrix TransMatrix;
	clSliceData::IdentityMatrix(&TransMatrix);

	// for (int layerIndex = 0; layerIndex < numLayers; layerIndex++)
	// {
	// 	sliFile.readSliceData(&sliceData, part, layerIndex);
	// 	int objectCount = sliceData.getObjectCount(part);
	// 	printf("Layer %d has %d objects\n", layerIndex, objectCount);
	// 	for (int object = 0; object < objectCount; object++)
	// 	{
	// 		printf("- %d Object %d is polygon: %s\n", part, object, sliceData.isPolygon(part, object) ? "true" : "false");
	// 		printf("- %d Object %d is hatch  : %s\n", part, object, sliceData.isHatch(part, object) ? "true" : "false");

	// 		// float *points = sliceData.getObjectPointsTransformed(part, object, TransMatrix);
	// 		float *points = sliceData.getObjectPoints(part, object);

	// 		printf("- Num points: %d\n", sliceData.getObjectPointCount(part, object));
	// 		printf("- first point: %f\n", points);
	// 	}
	// }

	int partCount = sliFile.getPartCount();
	printf("# %d parts\n", partCount);
	for (int part = 0; part < partCount; part++)
	{
		int numLayers = sliFile.getLayerCount(part);
		for (int layer = 0; layer < numLayers; layer++)
		{
			sliFile.readSliceData(&sliceData, part, layer);
			int objectCount = sliceData.getObjectCount(part);
			for (int object = 0; object < objectCount; object++)
			{
				float *points = sliceData.getObjectPointsTransformed(part, object, TransMatrix);
				int pointCount = sliceData.getObjectPointCount(part, object);
				printf("# Part %d, Layer %d, Object %d, Num points: %d, isPolyon: %s, isHatch: %s\n",
					   part, layer, object, pointCount,
					   sliceData.isPolygon(part, object) ? "true" : "false",
					   sliceData.isHatch(part, object) ? "true" : "false");

				printf("[");
				for (int point = 0; point < pointCount - 1; point++)
				{
					printf("(%f, %f), ", points[point], points[point + 1]);
				}
				printf("]\n");
				// sliceData.drawRasteredObject(&imgFilled, &imgPolyLine, part, object, TransMatrix, object, w, h);
			}
		}
	}
}
