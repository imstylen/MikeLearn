clear;clc;close all;

s = @(z) 1./(1+exp(-z));
ds = @(z) diag(s(z).*(1-s(z)));

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
 nepoch = 10000;
 for epoch = 1:nepoch
     for i = 1:length(X)

        n0 = X(i,:)'; #x0 2x1
        
        n1 = W1; #W1 2x2
        J13 = blkdiag(n0',n0'); #2x2
        
        n2 = B1; #B1 2x1
        J23 = eye(2); #2x2
        
        n3 = n1*n0 + n2; #Z1 2x1
        J34 = ds(n3); # 2x2
        
        n4 = s(n3); #X1 2x1
        J47 = W2; #2x1
        
        n5 = W2; #W2
        J57 =blkdiag(n4'); #2x1
        
        n6 = B2;#B2 1x1
        J67 = 1;
        
        n7 = n5*n4 + n6; #Z2 1x1
        J78 = ds(n7); #1x1
        
        n8 = s(n7); #X2
        J810 = 1;
        
        n9 = Y(i); #T
        
        n10 = n8 - n9; #Y
        J1011 = n10;
        
        n11 = 0.5*norm(n10)^2; #L
        
        gradW2starL = ((J810*J78)*J57)'*J1011;
        gradW2L = reshape(gradW2starL,1,2);
     
        gradB2L = ((J810*J78)*J67)'*J1011;
        
        gradW1starL = ((((J810*J78)*J47)*J34)*J13)'*J1011;
        gradW1L = reshape(gradW1starL,2,2);
        
        gradB1L = ((((J810*J78)*J47)*J34)*J23)'*J1011;
        
        alpha = 0.1;

        W2 = W2 - alpha*gradW2L;
        W1 = W1 - alpha*gradW1L;

        B2 = B2 - alpha*gradB2L;
        B1 = B1 - alpha*gradB1L;
        
        E(index) = n11;
        E(index);
        index = index + 1;
        
        if mod(epoch,1000) == 0
          E(index-1)
          epoch/100000*100
        endif

     end
     

     
 end
 
 plot(E)
 title("Error")
 Predict = @(I) s(W2*s(W1*I + B1)+B2)
 