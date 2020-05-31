#include "ClassificationOptimizer.h"

ClassificationOptimizer::ClassificationOptimizer(NeuralNetwork* neuralNetwork, std::vector<std::vector<float>> xtrain, std::vector<std::vector<float>> ytrain)
{
	this->xTrain = xtrain;
	this->yTrain = ytrain;
	this->neuralNetwork = neuralNetwork;

	logger = new Logger(1);

}

std::vector<float> ClassificationOptimizer::fit(int nEpochs, float learningRate)
{
	std::vector<float> E;

	for (int i = 0; i < nEpochs; i++)
	{
		logger->LogGeneral("-------------------------", "Epoch", i, "-------------------------");
		for (int j = 0; j < xTrain.size(); j++)
		{
			Eigen::MatrixXf X0 = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(xTrain[j].data(), neuralNetwork->GetNumInputs(), 1);
			logger->LogVerbose("----------", "X0", "-----------", X0);

			Eigen::MatrixXf XL = neuralNetwork->forward(X0);
			logger->LogVerbose("----------", "XL", "-----------", XL);

			Eigen::MatrixXf Y = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(yTrain[j].data(), neuralNetwork->GetNumOutputs(), 1);
			logger->LogVerbose("----------", "Y", "-----------", Y);

			float ei = (XL - Y).norm();
			ei = ei * ei;
			logger->LogVerbose("Error:", ei);

			if (j % 5000 == 0)
			{
				logger->LogGeneral("E= ", ei);
			}

			E.push_back(ei);

			neuralNetwork->backward(XL - Y, learningRate);

		}
	}
	return E;
}

void ClassificationOptimizer::setLoggerVerbosity(int verbosity)
{
	logger->setVerbosity(verbosity);
}

std::vector<float> ClassificationOptimizer::predict(std::vector<float> x0)
{

	Eigen::MatrixXf X0 = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(x0.data(), neuralNetwork->GetNumInputs(), 1);
	Eigen::MatrixXf xL = neuralNetwork->forward(X0);

	std::vector<float> Out(xL.data(), xL.data() + xL.rows() * xL.cols());
	return Out;
}


