clear all;
clc;

K1=5; K2=7; D1=40; D2=30; M1=2; M2=3;
A = [0 1 0 0;
    -K2/M2 -D2/M2 K1/M2 D1/M2;
    0 0 0 1
    (K1-K2)/M1 (D1-D2)/M1 -K1/M1 -D1/M1];
B = [0; 0; 0; 1/M1];
C = [1 0 0 0];
     

%Phuong phap' dat. cuc.
E_ol = eig(A); % tinh' cuc. cua~ A (open loop when not control yet)

p1 = -1 - 1*i; %do A 4x4 nen phai~ chon. 4 cuc. 
p2 = -1 + 1*i; %cac' cuc. chon. phai~ nam` ben trai' mat. phang~ phuc'
p3 = -2 - 1*i; 
p4 = -2 + 1*i;
P = [p1; p2; p3; p4];
K = place(A,B,P)

%Phuong phap' LQR
Q = [1 0 0 0;... %Q la` trong. so' the~ hien. muc' uu tien
     0 1 0 0;... %Q la` matrix co' size = A
     0 0 1 0;... %Q la` matrix chi~ duong` cheo' co' so'
     0 0 0 1];
 R = 1;          %R dai. dien. cho muc' tang cua~ "u"
 
 %[K_lqr, P_cl, E_cl] = lqr(A,B,Q,R) %1 trong 2 deu` dc
 K_lqr = lqr(A,B,Q,R)
 
 %Nbar = -inv(C*inv(A-B*K)*B); 1 trong 2 deu dc
 sys_ss = ss(A,B,C,0);
 Nbar = rscale(sys_ss, K_lqr);
 
 