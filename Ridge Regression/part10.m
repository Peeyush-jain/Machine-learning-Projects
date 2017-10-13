function [] = part10(X,Y)
    [lambda , frac] = part9(X,Y);
    
    
        
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

      
            Weight = mylinridgereg(trainExamples,trainTarget,lambda); % learning linear ridge regression model
            trainOutput = mylinridgeregeval(trainExamples,Weight);
            testoutput = mylinridgeregeval(testExamples,Weight);    
           
           
            figure
            subplot(1,2,1)
            
            plot(testTarget,testoutput,'*')
            refline(1,0);
            ylim([0 30]);
            xlabel('Actual Values');
            ylabel('Predicted Values');
            title('Predicted Output Vs Actual Output for Test Data');
            
            subplot(1,2,2)
            
            plot(trainTarget,trainOutput,'*')
            refline(1,0);
            ylim([0 30]);
            xlabel('Actual Values');
            ylabel('Predicted Values');
            title('Predicted Output Vs Actual Output for train Data');
            
end

