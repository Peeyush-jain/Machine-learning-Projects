function [ans] = transform(X,degree)
    [n,m]=size(X);
    useless=m;
    dim=(degree+1)*(degree+2)/2;
    ans=zeros(n,dim);
    index=2;
    for i=1:n
        ans(i,1)=1;
        x1=X(i,2);
        x2=X(i,3);
        index=2;
        for j=1:degree
            for k=0:j
                ans(i,index)=(x2^k)*(x1^(j-k));
                index=index+1;
            end
        end
    end
            
end