function [ recon_3d ] = recon_3D( matchpoints1, matchpoints2, Camera1, Camera2, Image1, Image2 )
% generate equations
x1 = matchpoints1(:,1);
x2 = matchpoints2(:,1);
y1 = matchpoints1(:,2);
y2 = matchpoints2(:,2);

p11T = Camera1(1,:);
p12T = Camera1(3,:);
p13T = Camera1(2,:);

p21T = Camera1(1,:);
p22T = Camera1(3,:);
p23T = Camera1(2,:);

for i = 1:length(matchpoints1)
    A = [x1(i)*p13T-p11T; y1(i)*p13T-p12T; x2(i)*p23T-p21T; y2(i)*p23T-p22T];
    [v,d] = eig(A);
end

% extract center of projection for each camera
[~,~,Vc1] = svd(Camera1);
COP1 = Vc1(:, length(Vc1));
[~,~,Vc2] = svd(Camera2);
COP2 = Vc2(:, length(Vc2));

end

