from Release import MikeLearn

M = MikeLearn.Model([0,0,0,1,1,0,1,1],2,[0,1,1,0],1,2)
M.fit(10000,0.75)
print(M.predict([0,0]))
print(M.predict([0,1]))
