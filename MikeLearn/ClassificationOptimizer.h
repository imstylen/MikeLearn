#pragma once
#include "Logger.h"
#include "NeuralNetwork.h"
#include <Eigen/Dense>
#include <vector>;

class ClassificationOptimizer
{
private:
	std::vector<std::vector<float>> xTrain;
	std::vector<std::vector<float>> yTrain;

	NeuralNetwork* neuralNetwork;

	Logger* logger;
protected:

public:
	ClassificationOptimizer(NeuralNetwork* neuralNetwork, 
							std::vector<std::vector<float>> xtrain,
							std::vector<std::vector<float>> ytrain);

	std::vector<float> fit(int nEpochs, float learningRate);

	void setLoggerVerbosity(int verbosity);

	std::vector<float> predict(std::vector<float> x0);

};

