function Start(image_left,image_right)


%INPUT: two images which we want to marge
%set all the Parameter
%harris corner detector is used to detect the corner
%the extracting patches size radius 1 to 3
%vl_SIFT is used to the key point
%to compute the euclidean distance I use here Pdist2
%We considerd here 400 match points
%To estimate the affine transformation used RANSAC 

%INSTRUCTION: Start('library1.jpg','library2.jpg');

run('C:\Users\USER\Desktop\vlf\toolbox\vl_setup');

total_match_point=400;
sigma=1;
thresh=1000;
radius=1;
disp=0;
radius_s=5;
Ia=imread(image_left);
Ib=imread(image_right);
I1=rgb2gray(Ia);
I2=rgb2gray(Ib);

[~, y_left , x_left]=harris(I1,sigma,thresh,radius,disp);
[~, y_right , x_right]=harris(I2,sigma,thresh,radius,disp);
key1=repmat(radius_s,length(x_left),1);
key2=repmat(radius_s,length(x_right),1);
ima1_key= cat(2,x_left,y_left,key1);
ima2_key= cat(2,x_right,y_right,key2);

[wi1,~]=size(ima1_key);
fc1=cat(1,ima1_key',zeros(1,wi1));
[f1, des1] = vl_sift(single(I1),'frames',fc1);
figure(1),imshow(I1);
title('KEYPOINTS of first image','Color', 'b');
perm = randperm(size(f1,2)) ;
sel = perm(1:50) ;
h1 = vl_plotframe(f1(:,sel)) ;
h2 = vl_plotframe(f1(:,sel)) ;
set(h1,'color','k','linewidth',3) ;
set(h2,'color','y','linewidth',2) ;
h3 = vl_plotsiftdescriptor(des1(:,sel),f1(:,sel)) ;
set(h3,'color','g') ;
des1=double(des1');
f1_pos=double(f1(1:2,:)');

[wi2,~]=size(ima2_key);
fc2=cat(1,ima2_key',zeros(1,wi2));
[f2, des2] = vl_sift(single(I2),'frames',fc2);
figure(2),imshow(I2);
title('KEYPOINTS of target image','Color', 'b');
perm = randperm(size(f2,2)) ;
sel = perm(1:50) ;
h1 = vl_plotframe(f2(:,sel)) ;
h2 = vl_plotframe(f2(:,sel)) ;
set(h1,'color','k','linewidth',3) ;
set(h2,'color','y','linewidth',2) ;
h3 = vl_plotsiftdescriptor(des2(:,sel),f2(:,sel)) ;
set(h3,'color','g') ;
des2=double(des2');
f2_pos=double(f2(1:2,:)');                                                   

[matches, scores] = vl_ubcmatch(des1', des2') ;

[drop, perm] = sort(scores, 'descend') ;
matches = matches(:, perm) ;
scores  = scores(perm) ;

figure(3) ; clf ;
imagesc(cat(2, Ia, Ib)) ;
title('Both images','Color', 'b');
axis image off ;

figure(4) ; clf ;
imagesc(cat(2, Ia, Ib)) ;

xa = f1(1,matches(1,:)) ;
xb = f2(1,matches(2,:)) + size(Ia,2) ;
ya = f1(2,matches(1,:)) ;
yb = f2(2,matches(2,:)) ;

hold on ;
h = line([xa ; xb], [ya ; yb]);
set(h,'linewidth', 1, 'color', 'b');
title('Matching Points','Color', 'g');
vl_plotframe(f1(:,matches(1,:))) ;
f2(1,:) = f2(1,:) + size(Ia,2) ;
vl_plotframe(f2(:,matches(2,:))) ;
axis image off ;

dist = pdist2(zscore(des1')',zscore(des2')','euclidean');   %for zero mean and SD
[m, n] = size(dist);
dist = reshape(dist, 1, []);
[~, idx] = sort(dist);
[row, col] = ind2sub([m, n], idx(1:total_match_point));

match=my_ransac(f1_pos(row',:),f2_pos(col',:));
result_img = im_stitch(image_left,image_right, match);
figure(5),imshow(result_img);
title('Finally........both images are STITCHING','Color', 'b');

