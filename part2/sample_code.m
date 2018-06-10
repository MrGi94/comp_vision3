%%
%% load images and match files for the first example
%%
example = 'library';
I1 = imread([example '1.jpg']);
I2 = imread([example '2.jpg']);
C1 = load([example '1_camera.txt']);
C2 = load([example '2_camera.txt']);
matches = load([example '_matches.txt']); 
matchPoints1 = [matches(:,1) matches(:,2)];
matchPoints2 = [matches(:,3) matches(:,4)];
[F, R] = FMatrix(matchPoints1, matchPoints2);
% this is a N x 4 file where the first two numbers of each row
% are coordinates of corners in the first image and the last two
% are coordinates of corresponding corners in the second image: 
% matches(i,1:2) is a point in the first image
% matches(i,3:4) is a corresponding point in the second image
N = size(matches,1);

%%
%% display two images side-by-side with matches
%% this code is to help you visualize the matches, you don't need
%% to use it to produce the results for the assignment
%%
imshow([I1 I2]); hold on;
plot(matches(:,1), matches(:,2), '+r');
plot(matches(:,3)+size(I1,2), matches(:,4), '+r');
line([matches(:,1) matches(:,3) + size(I1,2)]', matches(:,[2 4])', 'Color', 'r');
%pause;

%%
%% display second image with epipolar lines reprojected 
%% from the first image
%%

%% first, fit fundamental matrix to the matches ()
L = [matches(:,1:2) ones(N,1)] * F; % transform points from 
% the first image to get epipolar lines in the second image

% find points on epipolar lines L closest to matches(:,3:4)
L = L ./ repmat(sqrt(L(:,1).^2 + L(:,2).^2), 1, 3); % rescale the line
pt_line_dist = sum(L .* [matches(:,3:4) ones(N,1)],2);
closest_pt = matches(:,3:4) - L(:,1:2) .* repmat(pt_line_dist, 1, 2);

% find endpoints of segment on epipolar line (for display purposes)
pt1 = closest_pt - [L(:,2) -L(:,1)] * 10; % offset from the closest point is 10 pixels
pt2 = closest_pt + [L(:,2) -L(:,1)] * 10;

% display points and segments of corresponding epipolar lines
clf;
imshow(I2); hold on;
plot(matches(:,3), matches(:,4), '+r');
line([matches(:,3) closest_pt(:,1)]', [matches(:,4) closest_pt(:,2)]', 'Color', 'r');
line([pt1(:,1) pt2(:,1)]', [pt1(:,2) pt2(:,2)]', 'Color', 'g');

%% display the triangulation
rec3D = recon_3D(matchPoints1, matchPoints2, C1, C2);

% extract center of projection for each camera
[~,~,Vc1] = svd(C1);
COP1 = homo2cart(Vc1(:, end)');
[~,~,Vc2] = svd(C2);
COP2 = homo2cart(Vc2(:, end)');

% prints the triangulated matching points and the COP for both cameras
figure;
axis equal;
hold on;
plot3(rec3D(:,1), rec3D(:,2), rec3D(:,3), '+k');
plot3(COP1(1), COP1(2), COP1(3), 'o', 'Color', 'r');
plot3(COP2(1), COP2(2), COP2(3), 'o', 'Color', 'b');
grid on;
xlabel('x');
ylabel('y');
zlabel('z');
title('3D Triangulation');
legend('triangulated matching points', 'center camera img1', 'center camera img2');