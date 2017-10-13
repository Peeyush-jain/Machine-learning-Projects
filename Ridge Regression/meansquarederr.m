function [ mean_error ] = meansquarederr( f , y )
% as f and y both are column vector
[m,n] = size(f);
square_sum = 0 ;
for i = 1:m
    square_sum =  square_sum + (f(i,1) - y(i,1))^2 ;
end
mean_error = square_sum/(2*m) ;

end

