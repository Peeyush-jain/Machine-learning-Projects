function [ W ] = mylinridgereg( X,Y,lambda)
    K = transpose(X)*X ;
    [m,m] = size(K);
    I = zeros(m);
    for i = 1:m
        I(i,i) = 1 ;
    end
    
    W = inv(K + lambda*I)*transpose(X)*Y ;
    

end

