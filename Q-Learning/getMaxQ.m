function q_max = getMaxQ(s, R)
%GETMAXQ returns the maximum Q value for state s based on all possible
%actions
    [~, idx] = ismember(R(R(:,s)~=0,:),R,'rows');
    q_max = max(R(idx,s));
    if isempty(q_max)
        q_max = 0;
    end
end

