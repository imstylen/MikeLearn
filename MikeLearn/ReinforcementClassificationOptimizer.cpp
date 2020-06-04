#include "ReinforcementClassificationOptimizer.h"
#include <stdlib.h>
#include <time.h>
ReinforcementClassificationOptimizer::ReinforcementClassificationOptimizer(NeuralNetwork* policy, std::vector<std::vector<float>> xtrain, std::vector<std::vector<float>> ytrain)
{
	this->xTrain = xtrain;
	this->yTrain = ytrain;
	this->policy = policy;

	logger = new Logger(1);

}

std::vector<float> ReinforcementClassificationOptimizer::fit(int nEpochs, int episodeLength, float learningRate, float lambda)
{
	std::vector<float> E;

	srand(time(0));
	int randomIndex;

	std::vector<Eigen::MatrixXf> logPolicies;
	float currentReward = 0.f;
	std::vector<float> cumulativeReward;
	

	//Collect data
	for (int k = 0; k < nEpochs;k++)
	{
		currentReward = 0;
		logPolicies.clear();
		cumulativeReward.clear();

		for (int i = 0; i < episodeLength; i++)
		{
			//Use policy
			randomIndex = rand() % xTrain.size();

			Eigen::MatrixXf X0 = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(xTrain[randomIndex].data(), policy->GetNumInputs(), 1);
			logger->LogVerbose("X0", X0);

			Eigen::MatrixXf XL = policy->forward(X0);
			logger->LogVerbose("XL", XL);

			Eigen::MatrixXf Y = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(yTrain[randomIndex].data(), policy->GetNumOutputs(), 1);
			logger->LogVerbose("Y", Y);

			//Reward
			//COMPLETE TRASH, REDO!!!! WILL BREAK CODE that is NONBINARY

			Eigen::MatrixXf prediction = XL.array().round();
			logger->LogVerbose("Prediction: ", prediction);
			if (prediction.isApprox(Y))
			{
				currentReward += 100;
			}
			else
			{
				currentReward -= 100;
			}

			logger->LogGeneral("CurrentReward", currentReward);

			cumulativeReward.push_back(currentReward);

			Eigen::MatrixXf e = XL - prediction;
			logPolicies.push_back(e);

			float ei = (e).norm();
			ei = ei * ei;

			E.push_back(ei);

		}

		//Update policy
		for (int i = 0; i < logPolicies.size(); i++)
		{
			logger->LogGeneral("LogPolicy", logPolicies[i]);
			logger->LogGeneral("RewardToGo:", cumulativeReward[cumulativeReward.size() - i - 1]);
			
			Eigen::MatrixXf back = -1*logPolicies[i] * cumulativeReward[cumulativeReward.size() - i - 1];
			logger->LogGeneral("BackValue:", back);
			policy->backward(back, learningRate, lambda);
		}
	}





	//for (int i = 0; i < nEpochs; i++)
	//{
	//	logger->LogGeneral("-------------------------", "Epoch", i, "-------------------------");
	//	for (int j = 0; j < xTrain.size(); j++)
	//	{
	//		Eigen::MatrixXf X0 = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(xTrain[j].data(), policy->GetNumInputs(), 1);
	//		logger->LogVerbose("----------", "X0", "-----------", X0);

	//		Eigen::MatrixXf XL = policy->forward(X0);
	//		logger->LogVerbose("----------", "XL", "-----------", XL);

	//		Eigen::MatrixXf Y = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(yTrain[j].data(), policy->GetNumOutputs(), 1);
	//		logger->LogVerbose("----------", "Y", "-----------", Y);

	//		Eigen::MatrixXf e = XL - Y;

	//		float ei = (e).norm();
	//		ei = ei * ei;
	//		logger->LogVerbose("Error:", ei);

	//		if (j % 5000 == 0)
	//		{
	//			logger->LogGeneral("E= ", ei);
	//		}

	//		E.push_back(ei);

	//		policy->backward(e, learningRate, lambda);

	//	}
	//}
	return E;
}

void ReinforcementClassificationOptimizer::setLoggerVerbosity(int verbosity)
{
	logger->setVerbosity(verbosity);
}

std::vector<std::vector<float>> ReinforcementClassificationOptimizer::predict(std::vector<std::vector<float>> x0)
{
	std::vector<std::vector<float>> Out;

	for (auto& xi : x0)
	{
		Eigen::MatrixXf X0 = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(xi.data(), policy->GetNumInputs(), 1);
		Eigen::MatrixXf xL = policy->forward(X0);
		Out.push_back(std::vector<float>(xL.data(), xL.data() + xL.rows() * xL.cols()));
	}

	return Out;
}
