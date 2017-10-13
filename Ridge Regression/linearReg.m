
% Question 1 linear regression
formatspec= '%c,%f,%f,%f,%f,%f,%f,%f,%d ';
fileID = fopen('linregdata.txt','r');
A = fscanf(fileID,formatspec);
[p,q] = size(A);
rows = 4177 ;
cols = 9 ;
input = zeros(rows,cols);
k = 1 ;
for i = 1:p
    index = mod(i-1,cols) + 1;
    input(k,index) = A(i,1);
    if (index == cols)
        k = k+1 ;
    end
end



y = zeros(rows,3);

% Part 1
for i = 1:rows
   if (fix(input(i,1)) == 77)% that means he is male
       y(i,3) = 1 ;
   elseif (fix(input(i,1)) == 70)
        y(i,1) = 1 ;
   else 
       y(i,2) = 1 ;
   end
end

%Part2
standardInput = standardization(input);
V = var(standardInput,0,1);
M = mean(standardInput,1);



%Part 3

X = zeros(rows,11);
X(:,2:4) = y(:,1:3);
X(:,5:11) = standardInput(:,2:8);
for i = 1:rows
   X(i,1) = 1 ; 
end
Y = zeros(rows,1);
Y(:,1) = input(:,9);
%Part4
randomNumber = randperm(rows);
% return a row vector 
frac = 0.2 ;
trainData = fix(rows*frac);
testData = rows - trainData ; 

trainExamples = zeros(trainData,11);
testExamples = zeros(testData,11);

testTarget = zeros(testData,1);
trainTarget = zeros(trainData,1);

for i = 1 : trainData
   index =  randomNumber(1,i);
   trainExamples(i,:) = X(index,:);
   trainTarget(i,:) = Y(index,:);
end
k =1;
for i = trainData+1 :rows
    index =  randomNumber(1,i);
    testExamples(k,:) = X(index,:);
    testTarget(k,:) = Y(index,:);
    k= k + 1 ;
end

lambda = 100 ;

Weight = mylinridgereg(trainExamples,trainTarget,lambda); % learning linear ridge regression model
trainOutput = mylinridgeregeval(trainExamples,Weight);
trainError = meansquarederr(trainOutput,trainTarget);


testoutput = mylinridgeregeval(testExamples,Weight);
testError = meansquarederr(testoutput,testTarget);


%Part6
% So to reduce the error we will reduce the number of attributes
sortedW = sort(Weight);

%Removing top 3 elements 
remove = 3 ;



[sgnTrainError , sgnTestError] = regularization(trainData , testData,trainExamples , testExamples ,trainTarget,testTarget,Weight,sortedW,remove);

%If removing smallest Weight does not increase accuracy then remove
%maximum weight
if (sgnTestError > testError)
    sortedW = sort(Weight,'descend');
    [sgnTrainError , sgnTestError] = regularization(trainData , testData,trainExamples , testExamples ,trainTarget,testTarget,Weight,sortedW,remove);
end
disp('Output of Part 6 format : TrainError , TestError , TrainError and TestError After Removal of features');
disp(trainError ); disp(testError) ; disp(sgnTrainError) ; disp(sgnTestError);
[meanTrainError , meanTestError] = part7(X,Y);

part8(X,Y);
part9(X,Y);
part10(X,Y);


    







