#include "Node.h"

void Node::printPathToLoss()
{
	Logger logger = Logger(1);
	logger.LogGeneral("Path to loss: ");
	for (auto& node : pathToLoss)
	{
		logger.LogGeneral(node->getID());
	}

}

void Node::setData(Eigen::MatrixXf& inData)
{
	Logger logger = Logger(1);
	data = inData;
	logger.LogGeneral(data);
}

void Node::setData(std::vector<float> inData,int nCol)
{
	Logger logger = Logger(1);

	int nRow = inData.size() / nCol;

	Eigen::MatrixXf M_newData = Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> >(inData.data(), nRow, nCol);
	data = M_newData;
	logger.LogGeneral("Data: ", M_newData);
}

void Node::Compute()
{
	if (!doesCompute)
	{
		return;
	}

}
