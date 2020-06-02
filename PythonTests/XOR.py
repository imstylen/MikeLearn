from MikeLearn import NeuralNetwork
from MikeLearn import ClassificationOptimizer
import time

#=======================================================
# Training Set
#=======================================================

X = [[0,1],[1,0],[1,1],[0,0]]
Y = [[1],[1],[0],[0]]

nIn = len(X[0])
nOut = len(Y[0])

#=======================================================
# Model
#=======================================================
verbosity = 0

#Initualize neural network
# NeuralNetwork([nInputs, nHidden1, nHidden2,..,nOutputs],['Activation1','Activation2'...]
N = NeuralNetwork([nIn,2,nOut],['sigmoid','sigmoid','softmax'])
N.setLoggerVerbosity(verbosity)

#Initialize the classification optimizer
#ClassificationOptimizer(NeuralNetwork,Xtrain,Ytrain)
Opt = ClassificationOptimizer(N,X,Y)
Opt.setLoggerVerbosity(verbosity)

start_time = time.time();

#fit data
#fit(nEpoch,LearningRate)
E = Opt.fit(10000,0.1)
print("--- %s seconds ---" % (time.time() - start_time))

print(Opt.predict(X))


