function [ cart ] = homo2cart( homo )
% Converts Cartesian coordinates to homogeneous coordinates
cart = bsxfun(@rdivide, homo, homo(:, end));
cart(:,4) = [];
end

