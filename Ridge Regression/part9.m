function [bestLambda , bestFrac] = part9(X,Y)
    
    fraction = zeros(1,8);
    for i = 1:8
        fraction(1,i) = 0.1*i ;
    end
    minAverageError = zeros(1,8);
    minLambda = zeros(1,8);

    for fractions = 1:8
        minimumError = 10000 ;
        minimumLambda = 1000 ;
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

            
            lambdaCount = 1000;
            lambdaVector = zeros(1,lambdaCount);
           
           
            testArray = zeros(1,lambdaCount);
            trainArray = zeros(1,lambdaCount);
            
            lambdaVector(1,1) = 0.01 ;
            for i = 2 : lambdaCount
               lambdaVector(1,i) = lambdaVector(1,i-1) + 0.01 ;  
            end
            
        for i = 1:lambdaCount
            lambda = lambdaVector(1,i);
            Weight = mylinridgereg(trainExamples,trainTarget,lambda); % learning linear ridge regression model
            trainOutput = mylinridgeregeval(trainExamples,Weight);
            trainError = meansquarederr(trainOutput,trainTarget);
           

            testoutput = mylinridgeregeval(testExamples,Weight);    
            testError = meansquarederr(testoutput,testTarget);
            if (testError < minimumError)
                minimumError = testError ;
                minimumLambda = lambda ;
            end
            trainArray(1,i) = trainError ;
            testArray(1,i) = testError ;
            
        end
        
        minAverageError(1,fractions) = minimumError ;
        minLambda(1,fractions) = minimumLambda;
        
        
    end  
    minimumError = 100000 ;
    
    for i = 1:8
        if (minAverageError(1,i) < minimumError )
           bestLambda = minLambda(1,i);
           bestFrac = fraction(1,i);
        end
    end
    
    figure
    title('minimum Average Testing Error Vs fraction');
    plot(fraction,minAverageError);
    xlabel('Fraction Values');
    ylabel('Minimum Average Testing Error');
    
    figure
    title('minimum Average Testing Error Vs fraction');
    plot(fraction,minLambda);
    xlabel('Fraction Values');
    ylabel('Lambda For minimum Average Testing Error');
    
    
end

