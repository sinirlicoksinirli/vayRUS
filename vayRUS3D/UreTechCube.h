#include"vertexStructs.hpp"
Vertex testCubeVertices[24];
void initTestCubeVertices() {
	testCubeVertices[0].pos.x = 0.2;//sað üst
	testCubeVertices[0].pos.y = 0.2;
	testCubeVertices[0].pos.z = 0.2;
	testCubeVertices[0].tex.x = 0.0;
	testCubeVertices[0].tex.y = 0.0;

	testCubeVertices[1].pos.x = 0.2;
	testCubeVertices[1].pos.y = -0.2;//sað alt
	testCubeVertices[1].pos.z = 0.2;
	testCubeVertices[1].tex.x = 0.0;
	testCubeVertices[1].tex.y = 1.0;

	testCubeVertices[2].pos.x = -0.2;
	testCubeVertices[2].pos.y = 0.2;//sol üst
	testCubeVertices[2].pos.z = 0.2;
	testCubeVertices[2].tex.x = 1.0;
	testCubeVertices[2].tex.y = 0.0;

	testCubeVertices[3].pos.x = -0.2;
	testCubeVertices[3].pos.y = -0.2;// sol alt
	testCubeVertices[3].pos.z = 0.2;
	testCubeVertices[3].tex.x = 1.0;
	testCubeVertices[3].tex.y = 1.0;

	testCubeVertices[4].pos.x = 0.2;//sað üst arka
	testCubeVertices[4].pos.y = 0.2;
	testCubeVertices[4].pos.z = -0.2;
	testCubeVertices[4].tex.x = 0.0;
	testCubeVertices[4].tex.y = 0.0;

	testCubeVertices[5].pos.x = 0.2;
	testCubeVertices[5].pos.y = -0.2;//sað alt arka
	testCubeVertices[5].pos.z = -0.2;
	testCubeVertices[5].tex.x = 0.0;
	testCubeVertices[5].tex.y = 1.0;

	testCubeVertices[6].pos.x = -0.2;
	testCubeVertices[6].pos.y = 0.2;//sol üst arka
	testCubeVertices[6].pos.z = -0.2;
	testCubeVertices[6].tex.x = 1.0;
	testCubeVertices[6].tex.y = 0.0;

	testCubeVertices[7].pos.x = -0.2;
	testCubeVertices[7].pos.y = -0.2;// sol alt arka
	testCubeVertices[7].pos.z = -0.2;
	testCubeVertices[7].tex.x = 1.0;
	testCubeVertices[7].tex.y = 1.0;
	//********************************************************
	testCubeVertices[8].pos.x = 0.2;//sað üst yan
	testCubeVertices[8].pos.y = 0.2;
	testCubeVertices[8].pos.z = 0.2;
	testCubeVertices[8].tex.x = 1.0;
	testCubeVertices[8].tex.y = 0.0;

	testCubeVertices[9].pos.x = 0.2;
	testCubeVertices[9].pos.y = -0.2;//sað alt yan
	testCubeVertices[9].pos.z = 0.2;
	testCubeVertices[9].tex.x = 1.0;
	testCubeVertices[9].tex.y = 1.0;

	testCubeVertices[10].pos.x = -0.2;
	testCubeVertices[10].pos.y = 0.2;//sol üst yan
	testCubeVertices[10].pos.z = 0.2;
	testCubeVertices[10].tex.x = 0.0;
	testCubeVertices[10].tex.y = 0.0;

	testCubeVertices[11].pos.x = -0.2;
	testCubeVertices[11].pos.y = -0.2;// sol alt yan
	testCubeVertices[11].pos.z = 0.2;
	testCubeVertices[11].tex.x = 0.0;
	testCubeVertices[11].tex.y = 1.0;

	testCubeVertices[12].pos.x = 0.2;//sað üst arka yan
	testCubeVertices[12].pos.y = 0.2;
	testCubeVertices[12].pos.z = -0.2;
	testCubeVertices[12].tex.x = 0.0;
	testCubeVertices[12].tex.y = 0.0;

	testCubeVertices[13].pos.x = 0.2;
	testCubeVertices[13].pos.y = -0.2;//sað alt arka yan
	testCubeVertices[13].pos.z = -0.2;
	testCubeVertices[13].tex.x = 0.0;
	testCubeVertices[13].tex.y = 1.0;

	testCubeVertices[14].pos.x = -0.2;
	testCubeVertices[14].pos.y = 0.2;//sol üst arka yan
	testCubeVertices[14].pos.z = -0.2;
	testCubeVertices[14].tex.x = 1.0;
	testCubeVertices[14].tex.y = 0.0;

	testCubeVertices[15].pos.x = -0.2;
	testCubeVertices[15].pos.y = -0.2;// sol alt arka yan
	testCubeVertices[15].pos.z = -0.2;
	testCubeVertices[15].tex.x = 1.0;
	testCubeVertices[15].tex.y = 1.0;
	//*****************************************
	testCubeVertices[16].pos.x = 0.2;//sað üst taban/tavan
	testCubeVertices[16].pos.y = 0.2;
	testCubeVertices[16].pos.z = 0.2;
	testCubeVertices[16].tex.x = 0.0;
	testCubeVertices[16].tex.y = 1.0;

	testCubeVertices[20].pos.x = 0.2;//sað üst arka taban/tavan
	testCubeVertices[20].pos.y = 0.2;
	testCubeVertices[20].pos.z = -0.2;
	testCubeVertices[20].tex.x = 0.0;
	testCubeVertices[20].tex.y = 0.0;

	testCubeVertices[18].pos.x = -0.2;
	testCubeVertices[18].pos.y = 0.2;//sol üst taban/tavan
	testCubeVertices[18].pos.z = 0.2;
	testCubeVertices[18].tex.x = 1.0;
	testCubeVertices[18].tex.y = 1.0;

	testCubeVertices[22].pos.x = -0.2;
	testCubeVertices[22].pos.y = 0.2;//sol üst arka taban/tavan
	testCubeVertices[22].pos.z = -0.2;
	testCubeVertices[22].tex.x = 1.0;
	testCubeVertices[22].tex.y = 0.0;

	testCubeVertices[17].pos.x = 0.2;
	testCubeVertices[17].pos.y = -0.2;//sað alt taban/tavan
	testCubeVertices[17].pos.z = 0.2;
	testCubeVertices[17].tex.x = 1.0;
	testCubeVertices[17].tex.y = 1.0;

	testCubeVertices[19].pos.x = -0.2;
	testCubeVertices[19].pos.y = -0.2;// sol alt taban/tavan
	testCubeVertices[19].pos.z = 0.2;
	testCubeVertices[19].tex.x = 0.0;
	testCubeVertices[19].tex.y = 1.0;

	testCubeVertices[21].pos.x = 0.2;
	testCubeVertices[21].pos.y = -0.2;//sað alt arka taban/tavan
	testCubeVertices[21].pos.z = -0.2;
	testCubeVertices[21].tex.x = 1.0;
	testCubeVertices[21].tex.y = 0.0;

	testCubeVertices[23].pos.x = -0.2;
	testCubeVertices[23].pos.y = -0.2;// sol alt arka taban/tavan
	testCubeVertices[23].pos.z = -0.2;
	testCubeVertices[23].tex.x = 0.0;
	testCubeVertices[23].tex.y = 0.0;
}
indexData testCubeIndecies[] = {
	0,1,2,
	3,1,2,
	4,5,6,
	7,5,6,//yan
	8,9,12,
	9,12,13,//sol
	10,11,14,
	11,14,15,//taban/tavan
	16,18,22,
	16,20,22,
	17,19,21,
	19,21,23

};
#pragma once
