function [ standardInput ] = standardization(input )
[rows cols] = size(input);
Variance = var(input,0,1);
Mean = mean(input,1);

standardInput = input ;

for j = 2:cols
    mean_attribute = Mean(1,j);
    deviation = sqrt(Variance(1,j));
    for i = 1:rows
        standardInput(i,j) = (standardInput(i,j) - mean_attribute)/deviation ;
    end
end


end

