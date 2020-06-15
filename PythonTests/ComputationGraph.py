from MikeLearn import Node
from MikeLearn import ComputationGraph

comp_graph = ComputationGraph()

n = list();
for i in range(0,12):
    n.append(comp_graph.AddNode())

comp_graph.setParent(0,3)
comp_graph.setParent(1,3)
comp_graph.setParent(2,3)
comp_graph.setLeaf(1)
comp_graph.setLeaf(2)

comp_graph.setParent(3,4)

comp_graph.setParent(4,7)
comp_graph.setParent(5,7)
comp_graph.setParent(6,7)
comp_graph.setLeaf(5)
comp_graph.setLeaf(6)

comp_graph.setParent(7,8)

comp_graph.setParent(8,10)
comp_graph.setParent(9,10)

comp_graph.setParent(10,11)

comp_graph.setRootNode(11);

comp_graph.printstuff();

