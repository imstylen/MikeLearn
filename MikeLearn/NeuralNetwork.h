#pragma once
#include <vector>
#include <Eigen/Dense>
#include "Logger.h"
#include <string>
class NeuralNetwork
{
private:

	Logger* logger;

	std::vector<int> layers;

	std::vector<Eigen::MatrixXf> X;
	std::vector<Eigen::MatrixXf> B;
	std::vector<Eigen::MatrixXf> W;

	Eigen::MatrixXf sigmoid(Eigen::MatrixXf x);
	Eigen::MatrixXf dSigmoid(Eigen::MatrixXf sig);

protected:


public:
	NeuralNetwork(std::vector<int> layers, std::vector<std::string> Activations);
	void setLoggerVerbosity(int verbosity);
	Eigen::MatrixXf forward(Eigen::MatrixXf& x0);
	void backward(Eigen::MatrixXf& back, float learningRate);

	
	int GetNumInputs();
	int GetNumOutputs();

};

