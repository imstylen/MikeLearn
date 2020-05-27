#pragma once
#include <Eigen/Dense>
#include <vector>

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

public:
	Model(std::vector<float> xIn,int nInputs, std::vector<float> yIn,int nOutputs,int nHidden);

	std::vector<float> fit(int epochs, float learningRate);

	std::vector<float> predict(std::vector<float> xIn);

};

