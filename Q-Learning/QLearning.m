state = (1:12);
goal_state = 4;
gamma = 0.9;
Q = zeros(size(state,2));
P = zeros(size(state,2),2);
mat = load('R.mat');
R = mat.unnamed;

for i = 1:10000
    s = datasample(state, 1);
    while(s~=goal_state)
        % get the row index of valid actions for state s
        [~, idx] = ismember(R(R(:,s)~=0,:),R,'rows');
        
        % pick one random action from the valid actions
        a = datasample(idx,1);
        
        % remove current index from list 
        idx(idx==a)=[];
        if rand<0.1
            % make mistake
            a = datasample(idx,1);
        end
        q_max = getMaxQ(a,Q);
        Q(a,s) = (1-(1/i))*Q(a,s)+1/i*(R(a,s)+gamma*q_max);
        s = a;
    end
    fprintf('%d/10000\n',i);
end
for j = 1:size(Q,2)
    [~, idx] = ismember(max(Q(:,j)),Q(:,j),'rows');
    P(j,1) = idx-1;
    P(j,2) = max(Q(:,j));
end
