from Release import MikeLearn
import random

X = []
Y = []

for i in range(0,100):
	x = list()
	for j in range(0,4):
		x.append(random.randint(0,1))
	if x == [1,0,0,1] or x == [0,1,1,0]:
		Y.append(1)
	else:
		Y.append(0)
	for num in x:
		X.append(num)

#Model(std::vector<float> xIn,int nInputs, std::vector<float> yIn,int nOutputs,int nHidden);
M = MikeLearn.Model(X,4,Y,1,3)
FinalE = M.fit(1000,0.75)
print("Final Error: " + str(FinalE[0]))

print(M.predict([0,0,0,0]))
print(M.predict([0,1,1,0]))
