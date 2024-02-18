#include "pch.h"
#include "cwe_api.h"
#include "SA2ModLoader.h"
#include "ModelInfo.h"

extern "C" 
{
	//registering data functions.
	void (*RegisterDataFunc)(void* ptr);

	//NJS Type texture name and texture list. As is for old documentation.
	NJS_TEXNAME ExampleTreeTex[5];
	NJS_TEXLIST texList_ExampleTree = {arrayptrandlength(ExampleTreeTex)};

	//Defining the tree models.
	ModelInfo* MDLExampleSeed;
	ModelInfo* MDLSaplingExampleTree;
	ModelInfo* MDLAdultExampleTree;
	ModelInfo* MDLDeadExampleTree;
	
	//Defining the fruit ID, fruit model, stats and Black Market attributes.
	int ExampleFruitID;
	ModelInfo* MDLExampleFruit;
	ChaoItemStats ExampleStats = { 10, 30, 200, 200, 200, 200, 200, 0, 0 }; //mood, belly, swim, fly, run, power, stamina, luck, intel, unknown;

	// Black Market Item Attributes
	BlackMarketItemAttributes BMExample = { 300, 150, 999, -1, -1, 0 };
	BlackMarketItemAttributes BMExampleTree = { 500, 250, 0, -1, -1, 0 };

	//registration functions to make things neater.
	void CWELoad(CWE_REGAPI* cwe_api)
	{
		cwe_api->RegisterChaoTexlistLoad("ExampleTex", &texList_ExampleTree);
		ExampleFruitID = cwe_api->RegisterChaoFruit(MDLExampleFruit->getmodel(), &texList_ExampleTree, &ExampleStats, &BMExample, NULL, "Example Fruit", "Sweet fruit from a Example tree.");
		
		//cwe_api->RegisterBlackMarketGeneralFruit(ExampleFruitID, 50);
		
		//Creating the struct for the Tree - See cwe_api.h for more details.
		CWE_API_TREE_DATA ExampleTree =
		{
			MDLExampleSeed->getmodel(),				//pSeedObj	
			MDLSaplingExampleTree->getmodel(),		//pSaplingObj
			MDLAdultExampleTree->getmodel(),		//pAdultObj
			MDLDeadExampleTree->getmodel(),			//pDeadObj
			&texList_ExampleTree,					//pTexList
			"ExampleTree",							//ID
			0,										//Flags
			{ ExampleFruitID, ExampleFruitID, ExampleFruitID }	//Three fruit IDs to Init with
		};
		cwe_api->AddChaoTree(ExampleTree, &BMExampleTree, "Example Seed", "Produces your fruit!");
	}

	__declspec(dllexport) void Init(const char* path)
	{
		HMODULE h = GetModuleHandle(L"CWE");

		std::string pathStr = std::string(path) + "\\";

		//Telling what models need to be associated as.
		MDLExampleSeed = new ModelInfo(pathStr + "ExampleTree_Seed.sa2mdl");
		MDLSaplingExampleTree = new ModelInfo(pathStr + "ExampleTree_Young.sa2mdl");
		MDLAdultExampleTree = new ModelInfo(pathStr + "ExampleTree_Mature.sa2mdl");
		MDLDeadExampleTree = new ModelInfo(pathStr + "ExampleTree_Dying.sa2mdl");
		MDLExampleFruit = new ModelInfo(pathStr + "ExampleFruit.sa2mdl");

		RegisterDataFunc = (void (*)(void* ptr))GetProcAddress(h, "RegisterDataFunc");
		RegisterDataFunc(CWELoad);
	}

	__declspec(dllexport) ModInfo SA2ModInfo = { ModLoaderVer };
}