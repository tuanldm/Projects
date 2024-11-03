clc
figure
plot(u1,v);
xlabel('F_tacdong'); ylabel('Speed');
title('lo xo kep');
hold;

P = u1'; T = v';
netA = newff(minmax(u1'), [200 1], {'tansig' 'purelin'}, 'trainlm');

%netA.trainParam.show = 500; %co' cunG~ dc k co' cunG~ k sao
netA.trainParam.lr = 0.01; %toc' do. hoc.
netA.trainParam.epochs = 1000; %so' chu ki`
netA.trainParam.goal = 1e-20; %sai so tich luy~ max mong muon

net1 = train(netA, P, T);
gensim(net1) %in ra khoi' trainnig ra cho xem

a = sim(net1, P);
e = a-v';
figure
plot(u1,a)
bar(e)
hold