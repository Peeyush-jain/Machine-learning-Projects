function [meanTrainError , meanTestError] = part7(X,Y)
    fraction = zeros(1,8);
    for i = 1:8
        fraction(1,i) = 0.1*i ;
    end
    
    disp('Output of Part 7 format : fraction , lambda ,meanTrainingError ,meanTestError');
    for fractions = 1:8
        frac = fraction(1,fractions);
        [rows cols] = size(X);
        
        lambdaCount = 15 ;
        lambdaVector =  zeros(1,lambdaCount);
        
        lambdaVector(1,1) = 10 ;
        
        for i = 2 : lambdaCount
             lambdaVector(1,i) = lambdaVector(1,i-1) + 10 ;  
        end
        
        for i = 1:lambdaCount
            lambda = lambdaVector(1,i);
            meanTrainError = 0 ;
            meanTestError = 0 ;
    
            for iteration = 1:100
                randomNumber = randperm(rows);
                trainData = fix(rows*frac);
                testData = rows - trainData ; 

                trainExamples = zeros(trainData,11);
                testExamples = zeros(testData,11);

                testTarget = zeros(testData,1);
                trainTarget = zeros(trainData,1);

                for j = 1 : trainData
                    index =  randomNumber(1,j);
                    trainExamples(j,:) = X(index,:);
                    trainTarget(j,:) = Y(index,:);
                end
                
                k =1;
                for j = trainData+1 :rows
                    index =  randomNumber(1,j);
                    testExamples(k,:) = X(index,:);
                    testTarget(k,:) = Y(index,:);
                    k= k + 1 ;
                end

                Variance = var(trainExamples,0,1);
                Mean = mean(trainExamples,1);
                trainExamples = standardization(trainExamples);
                % standardizing test data
                [m2,n2] = size(testExamples);

                for j = 2:n2
                    mean_attribute = Mean(1,j);
                    deviation = sqrt(Variance(1,j));
                    for k = 1:m2
                        testExamples(k,j) = (testExamples(k,j) - mean_attribute)/deviation ;
                    end
                end

            
            
        
            
                Weight = mylinridgereg(trainExamples,trainTarget,lambda); % learning linear ridge regression model
                trainOutput = mylinridgeregeval(trainExamples,Weight);
                trainError = meansquarederr(trainOutput,trainTarget);
                meanTrainError = meanTrainError + trainError ;

                testoutput = mylinridgeregeval(testExamples,Weight);    
                testError = meansquarederr(testoutput,testTarget);
                meanTestError = meanTestError + testError ;
            
        
            end
              meanTrainError = meanTrainError/(100) ;
              meanTestError = meanTestError/(100) ;
            disp('Output :')  
            disp(frac);
            disp(lambda);
            disp(meanTrainError);
            disp(meanTestError);
        end
        
        
        
       
    end
    
   
end

