from Release import MikeLearn
import pickle
#=======================================================
# Problem Statement
#=======================================================
# Create a nueral network to differentiate between 
# diagonal linesand non-diagonal lines in  2X2 of pixels.

#=======================================================
# Training Set
#=======================================================

modeldata = pickle.load( open( "modeldata.p", "rb" ) )
X = modeldata['X_flatten_list']
Y = modeldata['Y_flatten_list']
nIn = modeldata['ninputs']
nOut = modeldata['noutputs']

print(len(X))
print(len(Y))
#=======================================================
# Fit Model
#=======================================================
# 4 input layer
# 3 hidden layer
# 2 output layer
print("Learning")
#Model(std::vector<float> xIn,int nInputs, std::vector<float> yIn,int nOutputs,int nHidden);
M = MikeLearn.Model(X,nIn,Y,nOut,350)
FinalE = M.fit(36,0.3)
print("Final Error: " + str(FinalE[0]))

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
pickle.dump( modeldata, open( "Mnist.p", "wb" ) )

