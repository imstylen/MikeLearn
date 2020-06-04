from MikeLearn import NeuralNetwork
from MikeLearn import ReinforcementClassificationOptimizer
import matplotlib
import matplotlib.pyplot as plt
import time
import random

#=======================================================
# Training Set
#=======================================================

data = open('iris.data','r').read().split('\n')
data = [line.split(',') for line in data]
random.shuffle(data)

X = list();
Y = list();

for line in data:
    if len(line)>1:
        X.append([float(i) for i in line[0:4]])
        if "setosa" in line[4]:
            Y.append([1,0,0])
        elif "versicolor" in line[4]:
            Y.append([0,1,0])
        else:
            Y.append([0,0,1])


#training set
X1 = X[0:100]
Y1 = Y[0:100]

#validation set
X2 = X[101:]
Y2 = Y[101:]

#number of inputs/outputs
nIn = len(X[0]) #~750
nOut = len(Y[0]) #=10

#=======================================================
# Model
#=======================================================
verbosity = 0

#Initualize neural network
# NeuralNetwork([nInputs, nHidden1, nHidden2,..,nOutputs],['Activation1','Activation2'...]
N = NeuralNetwork([nIn,4,nOut],['sigmoid','sigmoid'])
N.setLoggerVerbosity(verbosity)

#Initialize the classification optimizer
#ClassificationOptimizer(NeuralNetwork,Xtrain,Ytrain)
Opt = ReinforcementClassificationOptimizer(N,X,Y)
Opt.setLoggerVerbosity(verbosity)

start_time = time.time();

#fit data
#fit(nEpoch,LearningRate,lambda)
E = Opt.fit(100000,10,0.001,0.0)
print("--- %s seconds ---" % (time.time() - start_time))
Opt.setLoggerVerbosity(3)
Opt.fit(1,5,0.01,0.0)

fig, ax = plt.subplots()
ax.plot(E)
ax.grid()
#fig.savefig("test.png")
plt.show()

print(Opt.predict(X))


