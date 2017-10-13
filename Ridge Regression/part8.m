function [] = part8(X,Y)
    
    fraction = zeros(1,8);
    for i = 1:8
        fraction(1,i) = 0.1*i ;
    end
    

    for fractions = 1:8
        frac = fraction(1,fractions);
        [rows cols] = size(X);
        randomNumber = randperm(rows);
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

        Variance = var(trainExamples,0,1);
        Mean = mean(trainExamples,1);
        trainExamples = standardization(trainExamples);
        % standardizing test data
        [m2,n2] = size(testExamples);

        for j = 2:n2
            mean_attribute = Mean(1,j);
            deviation = sqrt(Variance(1,j));
            for i = 1:m2
                testExamples(i,j) = (testExamples(i,j) - mean_attribute)/deviation ;
            end
        end

            
            lambdaCount = 50 ;
            lambdaVector = zeros(1,lambdaCount);
           
           
            testArray = zeros(1,lambdaCount);
            trainArray = zeros(1,lambdaCount);
            
            lambdaVector(1,1) = 200 ;
            for i = 2 : lambdaCount
               lambdaVector(1,i) = lambdaVector(1,i-1) + 10 ;  
            end
            
        for i = 1:lambdaCount
            lambda = lambdaVector(1,i);
            Weight = mylinridgereg(trainExamples,trainTarget,lambda); % learning linear ridge regression model
            trainOutput = mylinridgeregeval(trainExamples,Weight);
            trainError = meansquarederr(trainOutput,trainTarget);
           

            testoutput = mylinridgeregeval(testExamples,Weight);    
            testError = meansquarederr(testoutput,testTarget);
            
            
            
            trainArray(1,i) = trainError ;
            testArray(1,i) = testError ;
            
        end
        
        subplot(2,4,fractions)
        plot(lambdaVector,trainArray,lambdaVector,testArray);
        title(frac);
        xlabel('lambda values');
        ylabel('Error Values');
        ylim([0 20]);
        
    end  
  
    suptitle('Training and Test Error V/s Lamda Values blue: Train Red : Test Error');
    
end

