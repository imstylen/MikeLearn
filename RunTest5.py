from x64.Release.MikeLearn import NeuralNetwork
from x64.Release.MikeLearn import ClassificationOptimizer
import matplotlib.pyplot as plt
import numpy as np
import pickle
import time

#=======================================================
# Training Set
#=======================================================

modeldata = pickle.load( open( "mnist_data.p", "rb" ) )
X = modeldata['X']
Y = modeldata['Y']

X = np.array(X)
X = X/255
X = X.tolist()

nIn = len(X[0])
nOut = len(Y[0])

#=======================================================
# Model
#=======================================================
verbosity = 1

N = NeuralNetwork([nIn,350,350,nOut],['sigmoid','sigmoid','softmax'])
N.setLoggerVerbosity(verbosity)

Opt = ClassificationOptimizer(N,X,Y)

Opt.setLoggerVerbosity(verbosity)
start_time = time.time();
E = Opt.fit(2,0.1)
print("--- %s seconds ---" % (time.time() - start_time))

#plt.plot(E)
#plt.show()
#================================

model_test_data = pickle.load( open( "mnist_test_data.p", "rb" ) )
X2 = model_test_data['X']
Y2 = model_test_data['Y']
print(len(X2))
print(len(Y2))
X2 = np.array(X2)
X2 = X2/255
X2 = X2.tolist()

XL = Opt.predict(X2)

print(len(XL))

correct = 0
for i,x in enumerate(XL):
    if XL[i].index(max(XL[i])) == Y[i].index(max(Y2[i])):
        correct = correct + 1

print("Correct = " +  str(correct))
Accuracy = correct/len(XL)*100;
print("Accuracy = " + str(Accuracy))


