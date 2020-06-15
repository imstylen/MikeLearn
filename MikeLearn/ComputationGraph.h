#pragma once
#include "Logger.h"
#include <vector>
#include "Node.h"

class ComputationGraph
{

private:
	std::vector<Node*> NodeVector;
	Node* rootNode;
	int currentNodeIndex = 0;
protected:
	
public:
	int AddNode();
	void setRootNode(int rootNodeID) { rootNode = NodeVector[rootNodeID]; };
	//void setPaths(Node* node);
	void setParent(int childId, int parentId);
	void setLeaf(int leafNode);
	void printstuff();

	void recur(Node* node, std::vector<Node*> path);
	
};

