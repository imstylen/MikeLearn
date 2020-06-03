#include "ClassificationOptimizer.h"

ClassificationOptimizer::ClassificationOptimizer(NeuralNetwork* neuralNetwork, std::vector<std::vector<float>> xtrain, std::vector<std::vector<float>> ytrain)
{
	this->xTrain = xtrain;
	this->yTrain = ytrain;
	this->neuralNetwork = neuralNetwork;

	logger = new Logger(1);

}

std::vector<float> ClassificationOptimizer::fit(int nEpochs, float learningRate, float lambda)
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

			Eigen::MatrixXf e = XL - Y;

			float ei = (e).norm();
			ei = ei * ei;
			logger->LogVerbose("Error:", ei);

			if (j % 5000 == 0)
			{
				logger->LogGeneral("E= ", ei);
			}

			E.push_back(ei);

			neuralNetwork->backward(e, learningRate, lambda);

		}
	}
	return E;
}

void ClassificationOptimizer::setLoggerVerbosity(int verbosity)
{
	logger->setVerbosity(verbosity);
}

std::vector<std::vector<float>> ClassificationOptimizer::predict(std::vector<std::vector<float>> x0)
{
	std::vector<std::vector<float>> Out;

	for (auto& xi : x0)
	{
		Eigen::MatrixXf X0 = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(xi.data(), neuralNetwork->GetNumInputs(), 1);
		Eigen::MatrixXf xL = neuralNetwork->forward(X0);
		Out.push_back(std::vector<float>(xL.data(), xL.data() + xL.rows() * xL.cols()));
	}

	return Out;
}


