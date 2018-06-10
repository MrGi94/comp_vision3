function [ fund_matrix, residual ] = FMatrix( matchpoints1, matchpoints2 )
% returns the fundamental matrix for each pair of images
% and the residual (mean squared distance)

% construct m x 9 matrix A
x1 = matchpoints1(:,1);
x2 = matchpoints2(:,1);
y1 = matchpoints1(:,2);
y2 = matchpoints2(:,2);
A = [x1.*x2 x1.*y2 x1 x2.*y1 y1.*y2 y1 x2 y2 ones(length(x1),1)];

% compute a first approximation of the fundamental matrix
[~,~,V] = svd(A);
f = V(:,length(V));
fund_matrix_approx = vec2mat(f,3);

% compute fundamental matrix
[Uf,Df,Vf] = svd(fund_matrix_approx);
% impose the rank-2 constraint by setting Df(3,3) to 0
Df(3,3) = 0;
fund_matrix = Uf*Df*Vf';

matches = [matchpoints1 matchpoints2];
N = size(matches,1);
L = [matches(:,1:2) ones(N,1)] * fund_matrix; % transform points from 
% the first image to get epipolar lines in the second image

% find points on epipolar lines L closest to matches(:,3:4)
L = L ./ repmat(sqrt(L(:,1).^2 + L(:,2).^2), 1, 3); % rescale the line
distance = sum(L .* [matches(:,3:4) ones(N,1)],2); % distances from each point to its line

residual = mean(abs(distance));
end