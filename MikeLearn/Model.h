#pragma once
#include <Eigen/Dense>
#include <vector>
#include "Logger.h"

class Model
{
protected:

private:
	std::vector<float> X;
	int nInputs;
	std::vector<float> Y;
	int nOutputs;

	int nHidden;

	Eigen::MatrixXf M_W1;
	Eigen::MatrixXf M_W2;

	Eigen::MatrixXf M_B1;
	Eigen::MatrixXf M_B2;

	Eigen::MatrixXf sigmoid(Eigen::MatrixXf x);
	Eigen::MatrixXf dSigmoid(Eigen::MatrixXf sig);

	Logger* logger;

public:
	Model(std::vector<float> xIn,int nInputs, std::vector<float> yIn,int nOutputs,int nHidden);

	std::vector<float> fit(int epochs, float learningRate);

	std::vector<float> predict(std::vector<float> xIn);

	std::vector<float> getW1();
	std::vector<float> getW2();
	
	std::vector<float> getB1();
	std::vector<float> getB2();

	void setW1(std::vector<float> in, int nRows);
	void setW2(std::vector<float> in, int nRows);

	void setB1(std::vector<float> in, int nRows);
	void setB2(std::vector<float> in, int nRows);

	void setLoggerVerbosity(int verbosity);

};

