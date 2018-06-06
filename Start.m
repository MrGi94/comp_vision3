function Start(image_left,image_right)

run('C:\Users\USER\Desktop\vlf\toolbox\vl_setup');

total_match_point=200;

I1=rgb2gray(imread(image_left));
I2=rgb2gray(imread(image_right));

[Cim1 , y_left , x_left]=harris(I1,1,1000,1,0);
[Cim2 , y_right , x_right]=harris(I2,1,1000,1,0);

ima1_key= cat(2,x_left,y_left,repmat(5,length(x_left),1));
ima2_key= cat(2,x_right,y_right,repmat(5,length(x_right),1));

[wi1,~]=size(ima1_key);
fc1=cat(1,ima1_key',zeros(1,wi1));
%fc = [100;100;10;-pi/8] ;
[f1, des1] = vl_sift(single(I1),'frames',fc1);
des1=double(des1');
f1_pos=double(f1(1:2,:)');

[wi2,~]=size(ima2_key);
fc2=cat(1,ima2_key',zeros(1,wi2));
[f2, des2] = vl_sift(single(I2),'frames',fc2);
des2=double(des2');
f2_pos=double(f2(1:2,:)');
                            %normalized coorelation
d1 = zscore(des1')';        %for zero mean and SD
d2 = zscore(des2')';    
dist = pdist2(d1, d2,'euclidean');
[m, n] = size(dist);
[~, idx] = sort(dist(:));

[row, col] = ind2sub([m, n], idx(1:total_match_point));
row = row';
col = col';

k=0;
