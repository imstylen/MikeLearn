from MikeLearn import NeuralNetwork
from MikeLearn import ClassificationOptimizer
import random
import time

#=======================================================
# Data Set
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

#Initialize optimizer
#ClassificationOptimizer(NeuralNetwork,Xtrain,Ytrain)
Opt = ClassificationOptimizer(N,X1,Y1)
Opt.setLoggerVerbosity(verbosity)

start_time = time.time();
#fit data
#fit(nEpoch,LearningRate)
E = Opt.fit(1000,0.1)
print("--- %s seconds ---" % (time.time() - start_time))

#================================
#Final Accuracy on training set
#================================
XL = Opt.predict(X1)

correct = 0
for i,x in enumerate(XL):
    if XL[i].index(max(XL[i])) == Y[i].index(max(Y1[i])):
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
    if XL[i].index(max(XL[i])) == Y[i].index(max(Y2[i])):
        correct = correct + 1

print("Testing set Correct = " +  str(correct))
Accuracy = correct/len(XL)*100;
print("Accuracy = " + str(Accuracy)+'%')
