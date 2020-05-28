from Release.MikeLearn import Model
import pickle
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
M = Model(X,4,Y,2,3)
FinalE = M.fit(10000,0.75)
print("Final Error: " + str(FinalE[0]))

#=======================================================
# Predict
#=======================================================
print("=============Predict============")
print(M.predict([0,0,0,0]))
print(M.predict([0,1,1,0]))

#=======================================================
# Save and Test
#=======================================================
print("================================")
print("Saving Model")
print("================================")
W1 = list(M.getW1())
W2 = list(M.getW2())
B1 = list(M.getB1())
B2 = list(M.getB2())
print(W1)
modeldata = {
    "W1" : W1,
    "W2" : W2,
    "B1" : B1,
    "B2" : B2  
    }
pickle.dump( modeldata, open( "Diagonal.p", "wb" ) )

print("================================")
print("Loading Model")
print("================================")
modelin = pickle.load(open("Diagonal.p","rb"))
N = Model([],4,[],2,3)
N.setW1(modelin["W1"],3) #nHidden
N.setW2(modelin["W2"],2) #nOut
N.setB1(modelin["B1"],3) #nHidden
N.setB2(modelin["B2"],2) #nOut

print("=============Predict============")
print(N.predict([0,0,0,0]))
print(N.predict([0,1,1,0]))
