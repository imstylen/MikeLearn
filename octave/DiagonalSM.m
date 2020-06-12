clear;clc;close all;

s = @(z) 1./(1+exp(-z));
ds = @(z) s(z).*(1-s(z));

d1 = [1;0;0;1]
d2 = [0;1;1;0]

 W1 = rand(3,4)
 W2 = rand(2,3)
 
 B1 = rand(3,1)
 B2 = rand(2,1)
    
 index = 1
 
 for epoch = 1:20001
     for i = 1:1

        x0 = round(rand(4,1));
        
        if x0 == d1 || x0 == d2
          t = [1;0];
        else
          t = [0;1];
        end

        x1N = W1*x0 + B1;
        x1 = s(x1N);

        x2N = W2*x1 + B2;
        x2 = softmax(x2N);

        delta2 = (x2-t).*dsoftmax(x2N);
        delta1 = W2'*delta2.*ds(x1N);
        
        dedw2 = delta2*x1';
        dedw1 = delta1*x0';

        alpha = 0.1;

        W2 = W2 - alpha*dedw2;
        W1 = W1 - alpha*dedw1;

        B2 = B2 - alpha*delta2;
        B1 = B1 - alpha*delta1;

     end
     
     if mod(epoch,100) == 0
         E(index) = norm(x2-t)^2;
         E(index)
         index = index + 1;
         
     end
     
 end
 
 plot(E)
 title("Error")
 Predict = @(I) s(W2*s(W1*I + B1)+B2)
 