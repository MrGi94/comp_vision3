function [ homo ] = cart2homo( cart )
% Converts Cartesian coordinates to homogeneous coordinates
homo = [cart ones(length(cart),1)];
end

