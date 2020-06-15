from MikeLearn import Node
from MikeLearn import ComputationGraph

comp_graph = ComputationGraph()

n = list();
for i in range(0,3):
    n.append(comp_graph.AddNode())

n.append(comp_graph.AddZNode())
comp_graph.setParent(0,3)
comp_graph.setParent(1,3)
comp_graph.setParent(2,3)
comp_graph.setLeaf(1)
comp_graph.setLeaf(2)

comp_graph.setRootNode(3)

#xor

x0 = [1,0]
nCol = 1
comp_graph.setNodeData(0,x0,nCol)

W1 = [0.5,0.4,0.3,0.1]
nCol = 2
comp_graph.setNodeData(1,W1,nCol)

B1 = [0.1,0.1]
nCol = 1
comp_graph.setNodeData(2,B1,nCol)

comp_graph.printstuff();