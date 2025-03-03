#include "Model.h"
#include <iostream>
#include <unsupported/Eigen/MatrixFunctions>
#include <chrono>
using namespace Eigen;

Eigen::MatrixXf Model::sigmoid(Eigen::MatrixXf x)
{
	ArrayWrapper<MatrixXf> A_T = x.array();
	A_T = -1 * A_T;
	A_T = A_T.exp();
	A_T = 1 + A_T;
	A_T = 1 / A_T;

	return A_T.matrix();
}

Eigen::MatrixXf Model::dSigmoid(Eigen::MatrixXf sig)
{
	ArrayWrapper<MatrixXf> A_sig = sig.array();
	A_sig = A_sig * (1 - A_sig);

	return A_sig.matrix();
}

Model::Model(std::vector<float> xIn, int nInputs, std::vector<float> yIn, int nOutputs,int nHidden)
{
	this->X = xIn;
	this->nInputs = nInputs;
	this->Y = yIn;
	this->nOutputs = nOutputs;
	this->nHidden = nHidden;

	//Initialize weights and bias
	M_W1 = MatrixXf::Random(nHidden, nInputs);
	M_W2 = MatrixXf::Random(nOutputs, nHidden);

	M_B1 = MatrixXf::Random(nHidden, 1);
	M_B2= MatrixXf::Random(nOutputs, 1);

	logger = new Logger(0);

	//std::cout << "W1" << std::endl;
	//std::cout << M_W1 << std::endl;

	//std::cout << "W2" << std::endl;
	//std::cout << M_W2 << std::endl;
	
	//std::cout << "B1" << std::endl;
	//std::cout << M_B1 << std::endl;
	
	//std::cout << "B2" << std::endl;
	//std::cout << M_B2 << std::endl;

}

std::vector<float> Model::fit(int epochs, float learningRate)
{
	float E;
	
	int nSamples = X.size() / nInputs;

	for (int i = 0; i < epochs; i++)
	{
		logger->LogGeneral("===========EPOCH===========",
							i,
						   "===========================");


		auto start = std::chrono::high_resolution_clock::now();

		for (int j = 0; j < nSamples; j++)
		{
			//std::cout << "==================================" << std::endl;
			std::vector<float> x0;
			std::vector<float>::iterator f = X.begin() + j * nInputs;
			std::vector<float>::iterator l = (X.begin() + j * nInputs) + nInputs;
			x0 = std::vector<float>(f, l);
			MatrixXf M_x0 = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(x0.data(), nInputs, 1);

			//std::cout << "M_x0:" << std::endl;
			//std::cout << M_x0 << std::endl;

			std::vector<float> t;
			std::vector<float>::iterator f_t = Y.begin() + j * nOutputs;
			std::vector<float>::iterator l_t = (Y.begin() + j * nOutputs) + nOutputs;
			t = std::vector<float>(f_t, l_t);
			MatrixXf M_t = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(t.data(), nOutputs, 1);

			//Forward propagation
			MatrixXf M_x1N = M_W1 * M_x0 + M_B1;
			MatrixXf M_x1 = sigmoid(M_x1N);

			//std::cout << "M_x1:" << std::endl;
			//std::cout << M_x1 << std::endl;

			MatrixXf M_x2N = M_W2 * M_x1 + M_B2;
			MatrixXf M_x2 = sigmoid(M_x2N);

			//std::cout << "M_x2:" << std::endl;
			//std::cout << M_x2 << std::endl;

			//Back propagation
			MatrixXf M_delta2 = (M_x2 - M_t).cwiseProduct(dSigmoid(M_x2));
			MatrixXf M_delta1 = (M_W2.transpose() * M_delta2).cwiseProduct(dSigmoid(M_x1));

			//std::cout << "M_delta1:" << std::endl;
			//std::cout << M_delta1 << std::endl;
			//std::cout << "M_delta2:" << std::endl;
			//std::cout << M_delta2 << std::endl;

			//Back propagation
			MatrixXf M_dedw2 = M_delta2 * M_x1.transpose();
			MatrixXf M_dedw1 = M_delta1 * M_x0.transpose();

			//std::cout << "M_dedw2:" << std::endl;
			//std::cout << M_dedw2 << std::endl;
			//std::cout << "M_dedw1:" << std::endl;
			//std::cout << M_dedw1 << std::endl;

			//Update weight and bias
			MatrixXf M_W1new = M_W1 - learningRate * M_dedw1;
			MatrixXf M_W2new = M_W2 - learningRate * M_dedw2;

			MatrixXf M_B1new = M_B1 - learningRate * M_delta1;
			MatrixXf M_B2new = M_B2 - learningRate * M_delta2;

			M_W1 = M_W1new;
			M_W2 = M_W2new;
			M_B1 = M_B1new;
			M_B2 = M_B2new;

		    E = (M_x2 - M_t).norm();
			E = E * E;

			//std::cout << "E = " << std::endl;
			if (j % 5000 == 0)
			{
				logger->LogVerbose("E= ", E);
			}
			
			logger->LogVeryVerbose("E= ", E);

		}
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);

		logger->LogGeneral("Time for last epoch", duration.count(), "seconds");

	}

	std::vector<float> err{ E };
	return err;

}

std::vector<float> Model::predict(std::vector<float> xIn)
{
	//std::cout << "===================Prediction===============" << std::endl;

	MatrixXf M_x0 = Map<Matrix<float, Dynamic, Dynamic, RowMajor> >(xIn.data(), nInputs, 1);
	//std::cout << "M_x0:" << std::endl;
	//std::cout << M_x0 << std::endl;

	//Forward propagation
	MatrixXf M_x1N = M_W1 * M_x0 + M_B1;
	MatrixXf M_x1 = sigmoid(M_x1N);

	//std::cout << "M_x1:" << std::endl;
	//std::cout << M_x1 << std::endl;

	MatrixXf M_x2N = M_W2 * M_x1 + M_B2;
	MatrixXf M_x2 = sigmoid(M_x2N);

	//std::cout << "M_x2:" << std::endl;
	//std::cout << M_x2 << std::endl;

	std::vector<float> Out(M_x2.data(), M_x2.data() + M_x2.rows() * M_x2.cols());

	return Out;
}

std::vector<float> Model::getW1()
{
	//std::cout << "W1: " << std::endl;
	//std::cout << M_W1 << std::endl;

	std::vector<float> outVec(M_W1.data(), M_W1.data() + M_W1.rows() * M_W1.cols());
	return outVec;
}

std::vector<float> Model::getW2()
{
	//std::cout << "W2: " << std::endl;
	//std::cout << M_W2 << std::endl;
	std::vector<float> outVec(M_W2.data(), M_W2.data() + M_W2.rows() * M_W2.cols());
	return outVec;
}

std::vector<float> Model::getB1()
{
	//std::cout << "B1: " << std::endl;
	//std::cout << M_B1 << std::endl;
	std::vector<float> outVec(M_B1.data(), M_B1.data() + M_B1.rows() * M_B1.cols());
	return outVec;
}

std::vector<float> Model::getB2()
{
	//std::cout << "B2: " << std::endl;
	//std::cout << M_B2 << std::endl;
	std::vector<float> outVec(M_B2.data(), M_B2.data() + M_B2.rows() * M_B2.cols());
	return outVec;
}

void Model::setW1(std::vector<float> in, int nRows)
{
	int nCols = in.size() / nRows;
	//std::cout << nCols << std::endl;
	M_W1 = Map<Matrix<float, Dynamic, Dynamic> >(in.data(), nRows, nCols);
	//std::cout << "W1: " << std::endl;
	//std::cout << M_W1 << std::endl;
}

void Model::setW2(std::vector<float> in, int nRows)
{
	int nCols = in.size() / nRows;
	//std::cout << nCols << std::endl;

	M_W2 = Map<Matrix<float, Dynamic, Dynamic> >(in.data(), nRows, nCols);
	//std::cout << "W2: " << std::endl;
	//std::cout << M_W2 << std::endl;
}

void Model::setB1(std::vector<float> in, int nRows)
{
	int nCols = in.size() / nRows;
	//std::cout << nCols << std::endl;

	M_B1 = Map<Matrix<float, Dynamic, Dynamic> >(in.data(), nRows, nCols);
	//std::cout << "B1: " << std::endl;
	//std::cout << M_B1 << std::endl;
}

void Model::setB2(std::vector<float> in, int nRows)
{
	int nCols = in.size() / nRows;
	//std::cout << nCols << std::endl;

	M_B2 = Map<Matrix<float, Dynamic, Dynamic> >(in.data(), nRows, nCols);
	//std::cout << "B2: " << std::endl;
	//std::cout << M_B2 << std::endl;
}

void Model::setLoggerVerbosity(int verbosity)
{
	logger->setVerbosity(verbosity);
}


