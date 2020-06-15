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
