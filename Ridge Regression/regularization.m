function [sgnTrainError, sgnTestError] = regularization(trainData , testData,trainExamples , testExamples ,trainTarget,testTarget,Weight,sortedW,remove )
removeIndex = zeros(remove,1);
[m1,n1] = size(Weight);
ind = 1 ;
for i =1:remove
    num = sortedW(i,1);
    for j=1:m1
       if (Weight(j,1) == num)
          removeIndex(ind,1) = j ;
          ind = ind+1 ;
       end
    end
end

sgnTrainEx = zeros(trainData, 11-remove);
sgnTestEx = zeros(testData,11-remove);
sgnWeight = zeros( 11-remove,1);
ind = 1 ;
for i = 1:11
    find = search(removeIndex,i); 
    if (find == 0)
       sgnTrainEx(:,ind) = trainExamples(:,i);
       sgnTestEx(:,ind) = testExamples(:,i);
       %sgnWeight(ind,1) = W1(i,1);
       ind = ind + 1 ;
    end
end
sgnlambda = 1 ;
sgnTrainEx = standardization(sgnTrainEx);
sgnWeight = mylinridgereg(sgnTrainEx , trainTarget,sgnlambda);
sgnTrainOutput = mylinridgeregeval(sgnTrainEx,sgnWeight);
sgnTrainError = meansquarederr(sgnTrainOutput,trainTarget);

sgnTestOutput = mylinridgeregeval(sgnTestEx,sgnWeight);
sgnTestError = meansquarederr(sgnTestOutput,testTarget);
disp(sgnTestError);


end

