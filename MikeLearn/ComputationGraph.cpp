#include "ComputationGraph.h"

int ComputationGraph::AddNode()
{
	Node* newNode = new Node();
	newNode->setId(currentNodeIndex);
	NodeVector.push_back(newNode);
	currentNodeIndex++;

	return currentNodeIndex - 1;
}

void ComputationGraph::setParent(int childId, int parentId)
{
	NodeVector[childId]->setParent(NodeVector[parentId]);
}

void ComputationGraph::setLeaf(int leafNode)
{

	NodeVector[leafNode]->setIsLeaf(true);

}

void ComputationGraph::printstuff()
{
	Logger logger = Logger(1);
	for (Node* node : NodeVector)
	{
		logger.LogGeneral("========", "Node",node->getID(), "========");
		for (Node* child : node->getChildren())
		{
			logger.LogGeneral(child->getID());

		}
	}

	std::vector<Node*> path;
	recur(rootNode, path);
	
	for (Node* node : NodeVector)
	{
		if (node->getIsLeaf())
		{
			logger.LogGeneral("========", "Node", node->getID(), "========");
			node->printPathToLoss();
		}


	}
}

void ComputationGraph::recur(Node* node, std::vector<Node*> path)
{
	path.push_back(node);

	for (Node* child : node->getChildren())
	{
		if (child->getIsLeaf() == true)
		{
			child->setPathToLoss(path);
		}
		else
		{
			recur(child, path);
		}
	}

}
