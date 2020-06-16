clear;clc;close all;

s = @(z) 1./(1+exp(-z));
ds = @(z) s(z).*(1-s(z));

X = [0 0;
     0 1;
     1 0;
     1 1]
Y = [0;
     1;
     1;
     0]
 
 W1 = rand(2,2)
 W2 = rand(1,2)
 
 B1 = rand(2,1)
 B2 = rand(1,1)
  
 index = 1
 
 for epoch = 1:10000
     for i = 1:length(X)

        x0 = X(i,:)';
        t = Y(i);

        x1N = W1*x0 + B1;
        x1 = s(x1N);

        x2N = W2*x1 + B2;
        x2 = s(x2N);

        delta2 = (x2-t).*ds(x2N);
        delta1 = W2'*delta2.*ds(x1N);

        dedw2 = delta2*x1';
        dedw1 = delta1*x0';

        alpha = 0.1;

        W2 = W2 - alpha*dedw2;
        W1 = W1 - alpha*dedw1;

        B2 = B2 - alpha*delta2;
        B1 = B1 - alpha*delta1;
        
         E(index) = 0.5*norm(x2-t)^2;
         E(index);
         index = index + 1;

     end
     

     
 end
 
 plot(E)
 title("Error")
 Predict = @(I) s(W2*s(W1*I + B1)+B2)
 