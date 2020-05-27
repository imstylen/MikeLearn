from Release import MikeLearn
import random

#=======================================================
# Problem Statement
#=======================================================
# Create a nueral network to differentiate between 
# diagonal linesand non-diagonal lines in  2X2 of pixels.

#=======================================================
# Training Set
#=======================================================

X = []
Y = []

for i in range(0,100):
	x = list()
	for j in range(0,4):
		x.append(random.randint(0,1))
	if x == [1,0,0,1] or x == [0,1,1,0]:
		Y.append(1)
		Y.append(0)
	else:
		Y.append(0)
		Y.append(1)
	for num in x:
		X.append(num)

#=======================================================
# Fit Model
#=======================================================
# 4 input layer
# 3 hidden layer
# 2 output layer

#Model(std::vector<float> xIn,int nInputs, std::vector<float> yIn,int nOutputs,int nHidden);
M = MikeLearn.Model(X,4,Y,2,3)
FinalE = M.fit(10000,0.75)
print("Final Error: " + str(FinalE[0]))

#=======================================================
# Predict
#=======================================================

print(M.predict([0,0,0,0]))
print(M.predict([0,1,1,0]))
