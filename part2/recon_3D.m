function [ recon_3d ] = recon_3D( matchpoints1, matchpoints2, Camera1, Camera2)
% applies the algebraic triangulation method to find the position of every
% pair of matching points

% convert the matchpoints into homogeneous coordinates
homo_mp1 = cart2homo(matchpoints1);
homo_mp2 = cart2homo(matchpoints2);
% 3 dimensions + homogeneous coordinate
recon_4d = []; 

for i = 1:length(matchpoints1)
    equation_1 = [0 -homo_mp1(i,3) homo_mp1(i,2); homo_mp1(i,3) 0 -homo_mp1(i,1); -homo_mp1(i,2) homo_mp1(i,1) 0];
    equation_2 = [0 -homo_mp2(i,3) homo_mp2(i,2); homo_mp2(i,3) 0 -homo_mp2(i,1); -homo_mp2(i,2) homo_mp2(i,1) 0];
    A = [equation_1*Camera1; equation_2*Camera2];
    [~, ~, V] = svd(A);
    recon_4d(i,:) = V(:,end)';
end

% transform homogeneous coordinates to cartesian
% by dividing each row with last number in that row
recon_3d = homo2cart(recon_4d);
end