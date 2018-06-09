function [ fund_matrix, residual ] = FMatrix( matchpoints1, matchpoints2, image1, image2 )

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

%% calculating epipolar lines
% right epipolar line
matchpoints_left = [matchpoints1 ones(length(matchpoints1), 1)]';
points_right = fund_matrix*matchpoints_left;
right_epipolar_x = 1:2*size(image2, 1);
right_epipolar_y = (-points_right(3)-points_right(1)*right_epipolar_x)/points_right(2);
right_epipolar_line = [right_epipolar_x; right_epipolar_y];

% left epipolar line
matchpoints_right = [matchpoints2 ones(length(matchpoints2), 1)]';
points_left = fund_matrix*matchpoints_right;
left_epipolar_x = 1:2*size(image1, 1);
left_epipolar_y = (-points_left(3)-points_left(1)*left_epipolar_x)/points_left(2);
left_epipolar_line = [left_epipolar_x; left_epipolar_y];

residual = mean(pdist2(right_epipolar_line, left_epipolar_line)^2);
% calculate every point on the left epipolar and every point on the right
% epipolar line
end

