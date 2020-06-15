#pragma once
#include "Logger.h"
#include <vector>
#include <Eigen/Dense>

class Node
{
private:


protected:

	int id;

	Node* parent = nullptr;
	std::vector<Node*> children;

	bool isLeaf = false;

	bool doesCompute = false;
	
	std::vector<Node*> pathToLoss;

	Eigen::MatrixXf data;

public:
	void setParent(Node* newParent) { parent = newParent; parent->addChild(this); };
	Node* getParent() { return parent; };

	void addChild(Node* newChild) { children.push_back(newChild); };
	std::vector<Node*> getChildren() { return children; };

	void setId(int newId) { this->id = newId; };
	int getID() { return id; };

	void setIsLeaf(bool newIsLeaf) { isLeaf = newIsLeaf; };
	bool getIsLeaf() { return isLeaf; };

	void setPathToLoss(std::vector<Node*> newPathToLoss) { pathToLoss = newPathToLoss; };

	void printPathToLoss();

	Eigen::MatrixXf getData() { return data; };
	void setData(std::vector<float> inData, int nCol);
	void setData(Eigen::MatrixXf& inData);

	virtual void Compute();
};

