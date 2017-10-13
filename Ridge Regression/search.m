function [ isPresent ] = search(A , key)

[m,n] = size(A);
isPresent = 0 ;
if (n == 1) % it means it is column vector
   for i = 1:m
       if (A(i,n) == key)
           isPresent = 1 ;
       end
   end
  
else 
    for i = 1:n
       if (A(m,i) == key)
           isPresent = 1 ;
       end
   end
    
    
end

end

