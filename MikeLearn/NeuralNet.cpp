#include "NeuralNet.h"
#include <unsupported/Eigen/MatrixFunctions>

NeuralNet::NeuralNet(std::vector<int> layers, std::vector<std::string> Activations)
{
	logger = new Logger(1);
	compGraph = new ComputationGraph();
	logger->LogGeneral("Comp graph created!");


	int lastZNodeID = -1;
	int xNodeID;
	int wNodeID;
	int bNodeID;
	int zNodeID = -1;

	for (int i = 0; i < layers.size(); i++)
	{
		logger->LogGeneral("==========","Layer",i,"==========");

		Node* XNode = new Node();
		xNodeID = compGraph->AddNode(XNode);

		if (i != layers.size() - 1)
		{
			Node* WNode = new Node();
			Node* BNode = new Node();

			Eigen::MatrixXf W = Eigen::MatrixXf::Random(layers[i + 1], layers[i]);
			logger->LogGeneral("W");
			WNode->setData(W);
			WNode->setIsLeaf(true);

			Eigen::MatrixXf B = Eigen::MatrixXf::Random(layers[i + 1], 1);
			logger->LogGeneral("B");
			BNode->setData(B);
			BNode->setIsLeaf(true);

			ZNode* zNode = new ZNode();

			wNodeID = compGraph->AddNode(WNode);
			bNodeID = compGraph->AddNode(BNode);
			zNodeID = compGraph->AddNode(zNode);

			WNode->setParent(zNode);
			BNode->setParent(zNode);
			XNode->setParent(zNode);

		}



		if (i == 0)
		{
			inputNode = XNode;
			
		} 
		else
		{
			outputNode = XNode;
			compGraph->setParent(zNodeID, xNodeID);
		}

	}

	std::vector<float> testData;
	testData.push_back(1.f);
	testData.push_back(1.f);

	inputNode->setData(testData, 1);
	compGraph->setRootNode(xNodeID);
	compGraph->printstuff();
}

void NeuralNet::setLoggerVerbosity(int verbosity)
{
	logger->setVerbosity(verbosity);
}

int NeuralNet::GetNumInputs()
{
	return layers[0];
}

int NeuralNet::GetNumOutputs()
{
	return layers[layers.size() - 1];
}
