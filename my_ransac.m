function [result]=my_ransac(feature1,feature2)


%INPUT:the feature point of the both images
%(image1 and target_image2)
%total number of iteration(N) 1000
% we set the distance error is 0.3
%OUTPUT: the matching parameter, which exist both images
%matching parameter(result) depends on the maximum number of inliers.


total_iter=1000;
thresError=0.3;
b_inliner = 0;
mid=4;

for i = 1:total_iter
        A_matrix = [];
        random_idx = randperm(size(feature1,1));        
        random_start = random_idx(1:mid);
        random_end = random_idx(mid+1:end);

        f1 = feature1(random_start,:);
        f2 = feature2(random_start,:);
        f1end = feature1(random_end,:);
        f2end = feature2(random_end,:);
               
        [row,~] = size(f1);       
        for i = 1:row
            zero_matrix = zeros(3, 1);
            Xi = [f1(i,:)'; 1];
            xpos = f2(i, 1);
            ypos = f2(i, 2);
            ki1=cat(2, zero_matrix', Xi', -ypos*Xi');
            ki2= cat(2, Xi', zero_matrix', -xpos*Xi');
            A_matrix = cat(1, A_matrix, ki1);
            A_matrix = cat(1, A_matrix, ki2);
        end
        [~, ~, V] = svd(A_matrix);
        fit = reshape(V(:,end), [3 3])';          
        
        onedim=ones(1, size(f1end, 1));
        l_x_pos = fit*cat(1, f1end',onedim);
        l_x_pos = l_x_pos';
        h_trans = l_x_pos(:,1:2);
        h_trans(:,1)=h_trans(:,1)./l_x_pos(:,3);
        h_trans(:,2)=h_trans(:,2)./l_x_pos(:,3);

        sum_s_error = sum((f2end - h_trans).^2,2);
        best_idx = find(sum_s_error<thresError);
        total_inliner = length(best_idx);
        if b_inliner < total_inliner
            b_inliner = total_inliner;
            b_point = fit;
        end
    end
    result = b_point;
end