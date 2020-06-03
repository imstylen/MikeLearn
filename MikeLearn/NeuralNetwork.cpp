#include "NeuralNetwork.h"
#include <unsupported/Eigen/MatrixFunctions>


Eigen::MatrixXf NeuralNetwork::sigmoid(Eigen::MatrixXf x)
{
	Eigen::ArrayWrapper<Eigen::MatrixXf> A_T = x.array();
	A_T = -1 * A_T;
	A_T = A_T.exp();
	A_T = 1 + A_T;
	A_T = 1 / A_T;

	return A_T.matrix();
}

Eigen::MatrixXf NeuralNetwork::dSigmoid(Eigen::MatrixXf sig)
{
	Eigen::ArrayWrapper<Eigen::MatrixXf> A_sig = sig.array();
	A_sig = A_sig * (1 - A_sig);

	return A_sig.matrix();
}

NeuralNetwork::NeuralNetwork(std::vector<int> layers, std::vector<std::string> Activations)
{
	logger = new Logger(0);

	this->layers = layers;

	logger->LogGeneral("Initializing Weigth and Bias Matricies");

	X = std::vector<Eigen::MatrixXf>(layers.size());
	W = std::vector<Eigen::MatrixXf>(layers.size()-1);
	B = std::vector<Eigen::MatrixXf>(layers.size()-1);

	logger->LogGeneral("layers size", layers.size());
	for (int i = 1; i < layers.size(); i++)
	{	
		W[i-1] = Eigen::MatrixXf::Random(layers[i], layers[i - 1]);
		B[i - 1] = Eigen::MatrixXf::Random(layers[i],1);
		logger->LogGeneral("---------", "W", i-1, "---------", W[i-1]);
		logger->LogGeneral("---------", "B", i - 1, "---------", B[i - 1]);
	}


}

void NeuralNetwork::setLoggerVerbosity(int verbosity)
{
	logger->setVerbosity(verbosity);
}

Eigen::MatrixXf NeuralNetwork::forward(Eigen::MatrixXf& x0)
{
	X[0] = x0;
	logger->LogVerbose("--------", "X", 0, "---------", X[0]);
	for (int i = 0; i < W.size(); i++)
	{
		Eigen::MatrixXf xiN = W[i] * X[i] + B[i];
		X[i + 1] = sigmoid(xiN);
		logger->LogVerbose("--------", "X", i, "---------", X[i]);
	}
	return X[X.size()-1];
}

void NeuralNetwork::backward(Eigen::MatrixXf& back, float learningRate, float lambda)
{
	std::vector<Eigen::MatrixXf> dedw;
	std::vector<Eigen::MatrixXf> delta;

	int nLayers = layers.size();
	//logger->LogGeneral(nLayers);
	int dIt = 0;
	for (int i = nLayers -1;i > 0; i=i-1)
	{
		logger->LogVerbose("--------","Back", i,"---------");
		Eigen::MatrixXf deltai;
		if (i == (nLayers - 1))
		{
			deltai.noalias() = back.cwiseProduct(dSigmoid(X[i]));
			delta.push_back(deltai);
			dIt++;
		
		}
		else
		{
			logger->LogVerbose("W", i);
			deltai.noalias() = (W[i].transpose() * delta[dIt - 1]).cwiseProduct(dSigmoid(X[i]));
			delta.push_back(deltai);
			dIt++;
		}
		
		Eigen::MatrixXf dedwi;
		dedwi.noalias() = delta[dIt - 1] * X[i - 1].transpose();
		dedw.push_back(std::move(dedwi));
		//logger->LogVerbose("dedw", dIt - 1, dedw[dIt - 1]);
		
		Eigen::MatrixXf WiNew;
		WiNew.noalias() = W[i - 1] - learningRate * dedw[dIt - 1] - lambda* W[i - 1];
		W[i-1] = WiNew;

		logger->LogVerbose("W", i - 1);
		//logger->LogVerbose(W[i - 1]);

		Eigen::MatrixXf BiNew = B[i-1] - learningRate * delta[dIt - 1];
		B[i-1] = BiNew;
		logger->LogVerbose("B", i - 1);
		logger->LogVerbose(B[i - 1]);

		
	}
}

int NeuralNetwork::GetNumInputs()
{
	return layers[0];
}

int NeuralNetwork::GetNumOutputs()
{
	return layers[layers.size()-1];
}


