from MikeLearn import NeuralNetwork
from MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import numpy as np
import pickle
import time

#=======================================================
# Data Set
#=======================================================

#load the data dictionary
modeldata = pickle.load( open( "mnist_data.p", "rb" ) )
X = modeldata['X']
Y = modeldata['Y']

#normalize data
X = np.array(X)
X = X/255
X = X.tolist()

#training set
X1 = X[0:49999]
Y1 = Y[0:49999]

#validation set
X2 = X[50000:59999]
Y2 = Y[50000:59999]

#number of inputs/outputs
nIn = len(X[0]) #~750
nOut = len(Y[0]) #=10


thisline = ""
for i,pixel in enumerate(X[0]):

    if (i) % 28 == 0:
        thisline = thisline + "\n"
    if pixel > 0.1:
        thisline = thisline + "+"
    else:
        thisline = thisline + "-"

print(thisline)
print(Y[0])

#=======================================================
# Model
#=======================================================
verbosity = 1

#Initualize neural network
# NeuralNetwork([nInputs, nHidden1, nHidden2,..,nOutputs],['Activation1','Activation2'...]
N = NeuralNetwork([nIn,20,20,20,nOut],['sigmoid','sigmoid'])
N.setLoggerVerbosity(verbosity)

#Initialize optimizer
#ClassificationOptimizer(NeuralNetwork,Xtrain,Ytrain)
Opt = ClassificationOptimizer(N,X1,Y1)
Opt.setLoggerVerbosity(verbosity)

start_time = time.time();
#fit data
#fit(nEpoch,LearningRate,lambda)
E = Opt.fit(10,0.1,0.00)
print("--- %s seconds ---" % (time.time() - start_time))

#================================
#Final Accuracy on training set
#================================
XL = Opt.predict(X1)

correct = 0
for i,x in enumerate(XL):
    if XL[i].index(max(XL[i])) == Y1[i].index(max(Y1[i])):
        correct = correct + 1

print("Training set Correct = " +  str(correct))
Accuracy = correct/len(XL)*100;
print("Accuracy = " + str(Accuracy) + '%')

#================================
#Final Accuracy on validation set
#================================
XL = Opt.predict(X2)

correct = 0
for i,x in enumerate(XL):
    if XL[i].index(max(XL[i])) == Y2[i].index(max(Y2[i])):
        correct = correct + 1

print("Testing set Correct = " +  str(correct))
Accuracy = correct/len(XL)*100;
print("Accuracy = " + str(Accuracy)+'%')
