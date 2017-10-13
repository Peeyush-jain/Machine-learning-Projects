
%%%%%%%%%%%% file reading %%%%%%%%%%%%%%%%

formatspec= '%f,%f,%f';
fileID = fopen('credit.txt','r');
A = fscanf(fileID,formatspec);
MAXEX=100;
x=zeros(MAXEX,1);
y=zeros(MAXEX,1);
f=zeros(MAXEX,1);
one=0;
for i=1:MAXEX
    x(i)=A(3*i-2);
    y(i)=A(3*i-1);
    f(i)=A(3*i);
    if(f(i)==1)
        one=one+1;
    end
end
xp=zeros(one,1);
yp=zeros(one,1);
xn=zeros(MAXEX-one,1);
yn=zeros(MAXEX-one,1);
pp=1;
pn=1;
for(i=1:MAXEX)
    if(f(i)==1)
        xp(pp)=x(i);
        yp(pp)=y(i);
        pp=pp+1;
    else
        xn(pn)=x(i);
        yn(pn)=y(i);
        pn=pn+1;
    end
end

%%%%%%%%%%%% dataset plot %%%%%%%%%%%%%%

plot (xp,yp,'b*')
hold
plot (xn,yn,'r*')

%%%%%%%%%%%% Gradient Descent %%%%%%%%%%%
w=[0 0.05 -0.05];
XP=ones(one,3);
XN=ones(MAXEX-one,3);
XP(:,2)=xp;
XP(:,3)=yp;
XN(:,2)=xn;
XN(:,3)=yn;
for k=1:10000
    sum=zeros(3,1);
    for i=1:one
        fx=sigmoid(XP(i,:),w);
        sum(:,1)=sum(:,1)+(fx-1)*transpose(XP(i,:));
    end
    for i=1:MAXEX-one
        fx=sigmoid(XN(i,:),w);
        sum(:,1)=sum(:,1)+(fx-0)*transpose(XN(i,:));
    end
    sum=sum*0.1;
    w=w-transpose(sum);
end

ans=sigmoid(XN(8,:),w);
correct=0;
for i=1:one
    ans=round(sigmoid(XP(i,:),w));
    if(ans==1)
        correct=correct+1;
    end
end
for i=1:(MAXEX-one)
    ans=round(sigmoid(XN(i,:),w));
    if(ans==0)
        correct=correct+1;
    end
end
accuracy=correct/MAXEX;
disp('Gradient Descent Accuracy :');
accuracy=accuracy*100;
disp(accuracy);
xx=linspace(1.5,3,1000);
yy=(-w(2)*xx);
yy=yy+(-w(1));
yy=yy/w(3);
plot(xx,yy,'k');
title('Gradient Descent');


%%%%%%%%%%%%%% Newton Raphson %%%%%%%%%%%%%%

X=zeros(MAXEX,3);
X(1:one,:)=XP;
X(one+1:MAXEX,:)=XN;
Y=zeros(MAXEX,1);
Y(1:one,1)=1;
w=[0 0 0];

for k=1:100
    R=zeros(MAXEX,MAXEX);
    for i=1:MAXEX
        fx=sigmoid(X(i,:),w);
        R(i,i)=fx*(1-fx);
    end
    H=transpose(X)*R*X;
    D=zeros(3,1);
    for i=1:MAXEX
        fx=sigmoid(X(i,:),w);
        D=D+(fx-Y(i,1))*transpose(X(i,:));
    end
    w=w-transpose(inv(H)*D);
end

ans=sigmoid(XP(9,:),w);
correct=0;
for i=1:MAXEX
    ans=round(sigmoid(X(i,:),w));
    if(ans==Y(i))
        correct=correct+1;
    end
end
accuracy=correct/MAXEX;
accuracy=accuracy*100;
disp('Newton Raphson accuracy : ');
disp(accuracy);
xx=linspace(3.7,4.7,1000);
yy=(-w(2)*xx);
yy=yy+(-w(1));
yy=yy/w(3);
figure;
plot (xp,yp,'b*')
hold
plot (xn,yn,'r*')
plot(xx,yy,'g');
title('Newton Raphson');



% %%%%%%%%%% transformed newton raphson %%%%%%%%%%%%

figure,plot (xp,yp,'b*')
hold
plot (xn,yn,'r*')

transform_degree=2;   %%%%%%% degree of transformation can be changed here.
X=transform(X,transform_degree);
ATT=(transform_degree+1)*(transform_degree+2)/2;
w=zeros(1,ATT);

lambda=0;   %%%%%lambda can be changed here.

for k=1:5
    R=zeros(MAXEX,MAXEX);
    for i=1:MAXEX
        fx=sigmoid(X(i,:),w);
        R(i,i)=fx*(1-fx);
    end
    H=transpose(X)*R*X;
    %H=H/MAXEX;
    iden=eye(ATT);
    %iden(1,1)=0;
    H=H+lambda*iden;
    D=zeros(ATT,1);
    for i=1:MAXEX
        fx=sigmoid(X(i,:),w);
        D=D+(fx-Y(i,1))*transpose(X(i,:));
    end
    D=D+lambda*transpose(w);
    w=w-transpose(inv(H)*D);
end

ans=sigmoid(X(ATT,:),w);
correct=0;
for i=1:MAXEX
    ans=round(sigmoid(X(i,:),w));
    if(ans==Y(i))
        correct=correct+1;
    end
end
accuracy=correct/MAXEX;
accuracy=accuracy*100;
disp('accuracy after transformation : ');
disp(accuracy);


%%%%%%%% test set %%%%%%%%%%%


testx=ones(1000,3);
testx(:,2:3)=data;
testx=transform(testx,transform_degree);
correct=0;
for i=1:1000
    ans=round(sigmoid(testx(i,:),w));
    if(ans==label(i))
        correct=correct+1;
    end
end
accuracy=correct/1000;
accuracy=accuracy*100;
disp('test accuracy after transformation : ');
disp(accuracy);

%%%%%%% plotting decision boundary %%%%%%%%%

xx=linspace(0,6,1000);
yy=linspace(2,7,1000);
threshold=0.01;
for i=1:1000
    for j=1:1000
        x=[1 xx(i) yy(j)];
        x=transform(x,transform_degree);
        f=sigmoid(x,w);
        if(abs(f-0.5)<threshold)
            plot(xx(i),yy(j),'k.');
        end
    end
end
title('Newton Raphson (Degree 2)');
