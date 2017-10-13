function [ans]=sigmoid(X,W)
    XT=transpose(X);
    f=W*XT;
    ans=1/(1+exp(-f));
end