#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Logger.h"
#include "ComputationGraph.h"
#include "Node.h"
#include "ZNode.h"

class NeuralNet
{

private:

	Logger* logger;
	std::vector<int> layers;

	ComputationGraph* compGraph;

	Node* inputNode;
	Node* outputNode;


protected:


public:
	NeuralNet(std::vector<int> layers, std::vector<std::string> Activations);
	void setLoggerVerbosity(int verbosity);


	int GetNumInputs();
	int GetNumOutputs();

};

