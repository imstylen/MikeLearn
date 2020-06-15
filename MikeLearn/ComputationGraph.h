#pragma once
#include "Logger.h"
#include <vector>
#include "Node.h"
#include "ZNode.h"

class ComputationGraph
{

private:
	std::vector<Node*> NodeVector;
	Node* rootNode;
	int currentNodeIndex = 0;
protected:
	
public:
	int AddNode();
	int AddNode(Node* newNode);
	int AddZNode();
	void setRootNode(int rootNodeID) { rootNode = NodeVector[rootNodeID]; };
	//void setPaths(Node* node);
	void setParent(int childId, int parentId);
	void setLeaf(int leafNode);
	void printstuff();

	void setLossPath(Node* node, std::vector<Node*> path);

	void setNodeData(int nodeId, std::vector<float> inData, int nCol);

	void forward(Node* node);
	
};

