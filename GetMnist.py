from tensorflow.keras.datasets import mnist
import numpy as np
import pickle


(X_train, Y_train), (X_test, Y_test) = mnist.load_data()

x_flatten_list = list()
y_flatten_list = list()

for i,x in enumerate(X_train):
    x_flatten_list.append(list(x.flatten()))
    
    yi = [0]*10;
    yi[Y_train[i]] = 1
    y_flatten_list.append(yi)

 
model_data = {'X':x_flatten_list,
              'Y':y_flatten_list}

pickle.dump( model_data, open( "minst_data.p", "wb" ) )

print(x_flatten_list)
print(y_flatten_list)