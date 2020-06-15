#include "ZNode.h"

void ZNode::Compute()
{
	Node::Compute();
	Logger logger = Logger(1);
	logger.LogGeneral("Znode compute!!");

	Eigen::MatrixXf newData = children[1]->getData() * children[0]->getData() + children[2]->getData();
	logger.LogGeneral("Child0",children[0]->getData());
	logger.LogGeneral("Answer",newData);
}
