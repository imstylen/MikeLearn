#pragma once
#include <vector>
#include "NeuralNetwork.h"

class ReinforcementClassificationOptimizer
{

private:
	std::vector<std::vector<float>> xTrain;
	std::vector<std::vector<float>> yTrain;

	NeuralNetwork* policy;

	Logger* logger;
protected:

public:
	ReinforcementClassificationOptimizer(NeuralNetwork* policy,
		std::vector<std::vector<float>> xtrain,
		std::vector<std::vector<float>> ytrain);

	std::vector<float> fit(int nEpochs, int episodeLength, float learningRate, float lambda);

	void setLoggerVerbosity(int verbosity);

	std::vector<std::vector<float>> predict(std::vector<std::vector<float>> x0);

};

