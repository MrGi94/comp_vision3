function [ fund_matrix, residual ] = FMatrix( matchpoints1, matchpoints2 )
% construct m x 9 matrix A
x1 = matchpoints1(:,1);
x2 = matchpoints2(:,1);
y1 = matchpoints1(:,2);
y2 = matchpoints2(:,2);
A = [x1.*x2 x1.*y2 x1 x2.*y1 y1.*y2 y1 x2 y2 ones(length(x1),1)];

%% compute a first approximation of the fundamental matrix
[~,~,V] = svd(A);
f = V(:,length(V));
fund_matrix_approx = vec2mat(f,3);

%% compute fundamental matrix
[Uf,Df,Vf] = svd(fund_matrix_approx);
% impose the rank-2 constraint by setting Df(3,3) to 0
Df(3,3) = 0;
fund_matrix = Uf*Df*Vf;

%residual = A\b;
end

