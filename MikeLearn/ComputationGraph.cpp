#include "ComputationGraph.h"
#include "ZNode.h"
int ComputationGraph::AddNode()
{
	Node* newNode = new Node();
	newNode->setId(currentNodeIndex);
	NodeVector.push_back(newNode);
	currentNodeIndex++;

	return currentNodeIndex - 1;
}

int ComputationGraph::AddZNode()
{
	ZNode* newNode = new ZNode();
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
	setLossPath(rootNode, path);
	
	for (Node* node : NodeVector)
	{
		if (node->getIsLeaf())
		{
			logger.LogGeneral("========", "Node", node->getID(), "========");
			node->printPathToLoss();
		}


	}

	forward(NodeVector[0]);

}

void ComputationGraph::setLossPath(Node* node, std::vector<Node*> path)
{
	path.push_back(node);

	if (node->getIsLeaf() == true)
	{
		node->setPathToLoss(path);
	}

	for (Node* child : node->getChildren())
	{

		setLossPath(child, path);

	}

}

void ComputationGraph::setNodeData(int nodeId, std::vector<float> inData, int nCol)
{
	NodeVector[nodeId]->setData(inData, nCol);
}

void ComputationGraph::forward(Node* node)
{
	Logger logger = Logger(1);
	ZNode* zNode = dynamic_cast<ZNode*>(node);
	logger.LogGeneral("==============", "Node", node->getID(), "==============");
	if (zNode != nullptr)
	{
		logger.LogGeneral("Cast succesful!");
		zNode->Compute();
	}
	else
	{
		logger.LogGeneral("Cast unsuccesful!");
	}

	if (node == rootNode)
	{
		return;
	}
	else
	{
		forward(node->getParent());
	}


}
