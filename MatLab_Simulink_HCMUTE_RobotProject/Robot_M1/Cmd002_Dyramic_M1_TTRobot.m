clear all;
clc;
%Khai bao
syms the1 the2 the3 the1_d the2_d the3_d the1_dd the2_dd the3_dd;
syms l1 l2 z1 z1_d z1_dd;
syms m1 m2 m3 g_trongluc;
c2=cos(the2);
s2=sin(the2);
c3=cos(the3);
s3=sin(the3);
c23=cos(the2 + the3);
s23=sin(the2+the3);

%Tinh Lagrangian
g = [0; 0; -g_trongluc];
g_T = [0 0 -g_trongluc];

P_0_1 = [0; 0; z1];
V_0_1 = (diff(P_0_1,z1))*z1_d; %diff la` dao. ham` (ham` , theo an~); dao. ham` theo an la` mat' an~ nen phai~ nhan rieng them de~ co' an~
V_0_1_T = [V_0_1(1,1) V_0_1(2,1) V_0_1(3,1)];
K1 = 0.5*m1*(V_0_1_T)*V_0_1;
U1 = -m1*g_T*P_0_1;

P_0_2 = [l1*cos(the2); l1*sin(the2); z1];
V_0_2 = (diff(P_0_2,the2))*the2_d; %diff la` dao. ham` (ham` , theo an~); dao. ham` theo an la` mat' an~ nen phai~ nhan rieng them de~ co' an~
V_0_2_T = [V_0_2(1,1) V_0_2(2,1) V_0_2(3,1)];
K2 = 0.5*m2*(V_0_2_T)*V_0_2;
U2 = -m2*g_T*P_0_2;

P_0_EE = [(l2*c23 + l1*c2); (l2*s23 + l1*s2); z1];
V_0_3 = (diff(P_0_EE,the2))*the2_d + (diff(P_0_EE,the3))*the3_d; %diff la` dao. ham` (ham` , theo an~); dao. ham` theo an la` mat' an~ nen phai~ nhan rieng them de~ co' an~
V_0_3_T = [V_0_3(1,1) V_0_3(2,1) V_0_3(3,1)]; 
K3 = 0.5*m3*(V_0_3_T)*V_0_3;
U3 = -m3*g_T*P_0_EE;

L = K1 + K2 + K3 - (U1 + U2 + U3);

dL_dThe3_d = diff(L,the3_d);
d_dt_dL_dThe3_d = diff(dL_dThe3_d, the1)*the1_d + diff(dL_dThe3_d, the2)*the2_d + diff(dL_dThe3_d, the3)*the3_d + diff(dL_dThe3_d, the1_d)*the1_dd + diff(dL_dThe3_d, the2_d)*the2_dd + diff(dL_dThe3_d, the3_d)*the3_dd;
dL_dThe3 = diff(L,the3);
T3 = d_dt_dL_dThe3_d - dL_dThe3;

dL_dThe2_d = diff(L,the2_d);
d_dt_dL_dThe2_d = diff(dL_dThe2_d, the1)*the1_d + diff(dL_dThe2_d, the2)*the2_d + diff(dL_dThe2_d, the3)*the3_d + diff(dL_dThe2_d, the1_d)*the1_dd + diff(dL_dThe2_d, the2_d)*the2_dd + diff(dL_dThe2_d, the3_d)*the3_dd;
dL_dThe2 = diff(L,the2);
T2 = d_dt_dL_dThe2_d - dL_dThe2;

dL_dZ1_d = diff(L, z1_d);
d_dt_dL_dZ1_d = diff(dL_dZ1_d, z1)*z1_d + diff(dL_dZ1_d, z1_d)*z1_dd;
dL_dZ1 = diff(L, z1);
T1 = d_dt_dL_dZ1_d - dL_dZ1;

T = [T1; T2; T3];

%tinh Jacobians: Dao. ham` rieng diem~ dau` cuoi' theo cac' bien' theta
J3_11 = diff(P_0_EE(1,1),z1);
J3_12 = diff(P_0_EE(1,1),the2);
J3_13 = diff(P_0_EE(1,1),the3);
J3_21 = diff(P_0_EE(2,1),z1);
J3_22 = diff(P_0_EE(2,1),the2);
J3_23 = diff(P_0_EE(2,1),the3);
J3_31 = diff(P_0_EE(3,1),z1);
J3_32 = diff(P_0_EE(3,1),the2);
J3_33 = diff(P_0_EE(3,1),the3);
J3 = [J3_11 J3_12 J3_13;...
      J3_21 J3_22 J3_23;...
      J3_31 J3_32 J3_33];
J3_T = [J3(1,1) J3(2,1) J3(3,1);...
        J3(1,2) J3(2,2) J3(3,2);...
        J3(1,3) J3(2,3) J3(3,3)];

J2_11 = diff(P_0_2(1,1),z1);
J2_12 = diff(P_0_2(1,1),the2);
J2_13 = diff(P_0_2(1,1),the3);
J2_21 = diff(P_0_2(2,1),z1);
J2_22 = diff(P_0_2(2,1),the2);
J2_23 = diff(P_0_2(2,1),the3);
J2_31 = diff(P_0_2(3,1),z1);
J2_32 = diff(P_0_2(3,1),the2);
J2_33 = diff(P_0_2(3,1),the3);
J2 = [J2_11 J2_12 J2_13;...
      J2_21 J2_22 J2_23;...
      J2_31 J2_32 J2_33];
J2_T = [J2(1,1) J2(2,1) J2(3,1);...
        J2(1,2) J2(2,2) J2(3,2);...
        J2(1,3) J2(2,3) J2(3,3)];

J1_11 = diff(P_0_1(1,1),z1);
J1_12 = diff(P_0_1(1,1),the2);
J1_13 = diff(P_0_1(1,1),the3);
J1_21 = diff(P_0_1(2,1),z1);
J1_22 = diff(P_0_1(2,1),the2);
J1_23 = diff(P_0_1(2,1),the3);
J1_31 = diff(P_0_1(3,1),z1);
J1_32 = diff(P_0_1(3,1),the2);
J1_33 = diff(P_0_1(3,1),the3);
J1 = [J1_11 J1_12 J1_13;...
      J1_21 J1_22 J1_23;...
      J1_31 J1_32 J1_33];
J1_T = [J1(1,1) J1(2,1) J1(3,1);...
        J1(1,2) J1(2,2) J1(3,2);...
        J1(1,3) J1(2,3) J1(3,3)];


