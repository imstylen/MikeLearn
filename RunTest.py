from Release.MikeLearn import Model
import pickle

M = Model([0,0,0,1,1,0,1,1],2,[0,1,1,0],1,2)
#M.setLoggerVerbosity(3)
FinalE = M.fit(10000,0.75)
print("FinalE " + str(FinalE[0]))
print(M.predict([0,0]))
print(M.predict([0,1]))

print("================================")
print("Saving Model")
print("================================")
W1 = list(M.getW1())
W2 = list(M.getW2())
B1 = list(M.getB1())
B2 = list(M.getB2())

modeldata = {
    "W1" : W1,
    "W2" : W2,
    "B1" : B1,
    "B2" : B2  
    }
pickle.dump( modeldata, open( "XOR.p", "wb" ) )

print("================================")
print("Loading Model")
print("================================")
modelin = pickle.load(open("XOR.p","rb"))
N = Model([],2,[],1,2)
N.setW1(modelin["W1"],2)
N.setW2(modelin["W2"],1)
N.setB1(modelin["B1"],2)
N.setB2(modelin["B2"],1)

print("=============Predict============")
print(N.predict([0,0]))
print(N.predict([0,1]))
