clear all;
clc;
l0=70; l1=150; l2=318; round = pi;
size_ngang=25; %l0 cua~ day' duoi'
size_doc=0; %h cua~ day' duoi'
%Diem~ dau` cuoi'
Pee = [60; 66; -280]; 
H = [0; 0; -sqrt((l1+l2)^2-(l0-size_ngang)^2)-size_doc];

% -80<=goc1<=160 ; goc2<0 ; -70<=goc3<=70 
anpp = acos((abs(l0-size_ngang))/(l1+l2)); %z+size_doc #0 
%alpha = pi-anpp;
alpha = 0;
x1=Pee(1,1)+size_ngang;
y1=Pee(2,1);
z1=Pee(3,1)+size_doc; 

x2=size_ngang*cos(2*pi/3)+Pee(1,1);
y2=size_ngang*sin(2*pi/3)+Pee(2,1);
z2=Pee(3,1)+size_doc; 

x3=size_ngang*cos(4*pi/3)+Pee(1,1);
y3=size_ngang*sin(4*pi/3)+Pee(2,1);
z3=Pee(3,1)+size_doc; 

% PN1
the4_1 = Fun001_BasicAtan2( (0), (-l2) , (y1) );

the3_1_1 = Fun001_BasicAtan2( (2*l1*l2*cos(the4_1(1,1))), (0) , (z1^2+(x1-l0)^2-l1^2-(l2*cos(the4_1(1,1)))^2));
the3_1_2 = Fun001_BasicAtan2( (2*l1*l2*cos(the4_1(2,1))), (0) , (z1^2+(x1-l0)^2-l1^2-(l2*cos(the4_1(2,1)))^2));
the3_1 = [the3_1_1(1,1); the3_1_1(2,1); the3_1_2(1,1); the3_1_2(2,1)];

the2_1 = [0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];
for i = 1:2
    for j = 1:4
        n = 4*(i-1)+j;
        m = n+8;
        the2_math = Fun001_BasicAtan2( (l2*sin(the3_1(j,1))*cos(the4_1(i,1))), (l1+l2*cos(the3_1(j,1))*cos(the4_1(i,1))), (z1) ); 
        the2_1(n,1) = the2_math(1,1) + alpha;
        the2_1(m,1) = the2_math(2,1) + alpha;
    end
end

h=0;
 for i = 1:2
     for j = 1:4
         for k = 1:16
            PX = l0 + l1*cos(the2_1(k,1)-alpha) + l2*cos(the2_1(k,1)-alpha+the3_1(j,1))*cos(the4_1(i,1));
            PY = -l2*sin(the4_1(i,1));
            PZ = l1*sin(the2_1(k,1)-alpha) + l2*sin(the2_1(k,1)-alpha+the3_1(j,1))*cos(the4_1(i,1));        
            X_tam = abs(PX - x1);
            Y_tam = abs(PY - y1);
            Z_tam = abs(PZ - z1);
            if(the2_1(k,1)>round)    
                the2_1(k,1) = the2_1(k,1) - 2*pi;
            end
            if(the2_1(k,1)<-round)    
                the2_1(k,1) = the2_1(k,1) + 2*pi;
            end
            if(the3_1(j,1)>round)    
                the3_1(j,1) = the3_1(j,1) - 2*pi;
            end
            if(the3_1(j,1)<-round)    
                the3_1(j,1) = the3_1(j,1) + 2*pi;
            end
            if(the4_1(i,1)>round)    
                the4_1(i,1) = the4_1(i,1) - 2*pi;
            end
            if(the4_1(i,1)<-round)    
                the4_1(i,1) = the4_1(i,1) + 2*pi;
            end
            if((X_tam<=0.0005)&&(Y_tam<=0.0005)&&(Z_tam<=0.0005)&&(the2_1(k,1)>=-4*pi/9)&&(the2_1(k,1)<=8*pi/9)&&(the3_1(j,1)<=0)&&(the4_1(i,1)>=-7*pi/18)&&(the4_1(i,1)<=7*pi/18))
            %if((X_tam<=0.0005)&&(Y_tam<=0.0005)&&(Z_tam<=0.0005))    
                h = h+1;
                the(h,1) = (the2_1(k,1));
                the(h,2) = (the3_1(j,1));
                the(h,3) = (the4_1(i,1));
            end
         end
     end
 end

% PN2
the5_2 = Fun001_BasicAtan2( (0), (l2/(2*sqrt(3))+l2*sqrt(3)/2) , (x2+y2/sqrt(3)));

the4_2_1 = Fun001_BasicAtan2( (2*l1*l2*cos(the5_2(1,1))), (0) , (z2^2+(-l0+l2*sqrt(3)*sin(the5_2(1,1))-2*x2)^2-l1^2-(l2*cos(the5_2(1,1)))^2) );
the4_2_2 = Fun001_BasicAtan2( (2*l1*l2*cos(the5_2(2,1))), (0) , (z2^2+(-l0+l2*sqrt(3)*sin(the5_2(2,1))-2*x2)^2-l1^2-(l2*cos(the5_2(2,1)))^2) );
the4_2 = [the4_2_1(1,1); the4_2_1(2,1); the4_2_2(1,1); the4_2_2(2,1)];

the3_2 = [0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];
for i = 1:2
    for j = 1:4
        n = 4*(i-1)+j;
        m = n+8;
        the3_math = Fun001_BasicAtan2( (l2*cos(the5_2(i,1))*sin(the4_2(j,1))), (l1+l2*cos(the4_2(j,1))*cos(the5_2(i,1))), (z2));
        the3_2(n,1) = the3_math(1,1) + alpha;
        the3_2(m,1) = the3_math(2,1) + alpha;
    end
end

h=0;
 for i = 1:2
     for j = 1:4
         for k = 1:16
            PX = -l0/2-l1/2*cos(the3_2(k,1)-alpha)-l2/2*cos(the3_2(k,1)+the4_2(j,1)-alpha)*cos(the5_2(i,1))+l2*sqrt(3)/2*sin(the5_2(i,1));
            PY = sqrt(3)*l0/2+l2/2*(sin(the5_2(i,1))+sqrt(3)*cos(the3_2(k,1)+the4_2(j,1)-alpha)*cos(the5_2(i,1)))+sqrt(3)/2*l1*cos(the3_2(k,1)-alpha);
            PZ = l1*sin(the3_2(k,1)-alpha)+l2*sin(the3_2(k,1)+the4_2(j,1)-alpha)*cos(the5_2(i,1));           
            X_tam = abs(PX - x2);
            Y_tam = abs(PY - y2);
            Z_tam = abs(PZ - z2);
            if(the3_2(k,1)>=round)    
                the3_2(k,1) = the3_2(k,1) - 2*pi;
            end
            if(the4_2(j,1)>=round)    
                the4_2(j,1) = the4_2(j,1) - 2*pi;
            end
            if(the5_2(i,1)>=round)    
                the5_2(i,1) = the5_2(i,1) - 2*pi;
            end
            if((X_tam<=0.0005)&&(Y_tam<=0.0005)&&(Z_tam<=0.0005)&&(the3_2(k,1)>=-4*pi/9)&&(the3_2(k,1)<=8*pi/9)&&(the4_2(j,1)<=0)&&(the5_2(i,1)>=-7*pi/18)&&(the5_2(i,1)<=7*pi/18)) 
            %if((X_tam<=0.0005)&&(Y_tam<=0.0005)&&(Z_tam<=0.0005))
                h = h+1;
                the(h,4) = (the3_2(k,1));
                the(h,5) = (the4_2(j,1));
                the(h,6) = (the5_2(i,1));
            end
         end
     end
 end

 
 %PN3
the5_3 = Fun001_BasicAtan2( (0), (l2/(2*sqrt(3))+l2*sqrt(3)/2) , (-x3+y3/sqrt(3))) ;

the4_3_1 = Fun001_BasicAtan2( (2*l1*l2*cos(the5_3(1,1))), (0) , (z3^2+(l0+l2*sqrt(3)*sin(the5_3(1,1))+2*x3)^2-l1^2-(l2*cos(the5_3(1,1)))^2) );
the4_3_2 = Fun001_BasicAtan2( (2*l1*l2*cos(the5_3(2,1))), (0) , (z3^2+(l0+l2*sqrt(3)*sin(the5_3(2,1))+2*x3)^2-l1^2-(l2*cos(the5_3(2,1)))^2) );
the4_3 = [the4_3_1(1,1); the4_3_1(2,1); the4_3_2(1,1); the4_3_2(2,1)];

the3_3 = [0;0;0;0;0;0;0;0;0;0;0;0;0;0;0;0];
for i = 1:2
    for j = 1:4
        n = 4*(i-1)+j;
        m = n+8;
        the3_math = Fun001_BasicAtan2( (l2*cos(the5_3(i,1))*sin(the4_3(j,1))), (l1+l2*cos(the4_3(j,1))*cos(the5_3(i,1))), (z3));
        the3_3(n,1) = the3_math(1,1) + alpha;
        the3_3(m,1) = the3_math(2,1) + alpha;
    end
end

l=0;
 for i = 1:2
     for j = 1:4
         for k = 1:16
            PX = -l0/2-l1/2*cos(the3_3(k,1)-alpha)-l2/2*cos(the3_3(k,1)+the4_3(j,1)-alpha)*cos(the5_3(i,1))-l2*sqrt(3)/2*sin(the5_3(i,1));
            PY = -sqrt(3)*l0/2+l2/2*(sin(the5_3(i,1))-sqrt(3)*cos(the3_3(k,1)+the4_3(j,1)-alpha)*cos(the5_3(i,1)))-sqrt(3)/2*l1*cos(the3_3(k,1)-alpha);
            PZ = l1*sin(the3_3(k,1)-alpha)+l2*sin(the3_3(k,1)+the4_3(j,1)-alpha)*cos(the5_3(i,1));           
            X_tam = abs(PX - x3);
            Y_tam = abs(PY - y3);
            Z_tam = abs(PZ - z3);
            if(the3_3(k,1)>=round)    
                the3_3(k,1) = the3_3(k,1) - 2*pi;
            end
            if(the4_3(j,1)>=round)    
                the4_3(j,1) = the4_3(j,1) - 2*pi;
            end
            if(the5_3(i,1)>=round)    
                the5_3(i,1) = the5_3(i,1) - 2*pi;
            end
            if((X_tam<=0.0005)&&(Y_tam<=0.0005)&&(Z_tam<=0.0005)&&(the3_3(k,1)>=-4*pi/9)&&(the3_3(k,1)<=8*pi/9)&&(the4_3(j,1)<=0)&&(the5_3(i,1)>=-7*pi/18)&&(the5_3(i,1)<=7*pi/18)) 
            %if((X_tam<=0.0005)&&(Y_tam<=0.0005)&&(Z_tam<=0.0005))    
                l = l+1;
                the(l,7) = (the3_3(k,1));
                the(l,8) = (the4_3(j,1));
                the(l,9) = (the5_3(i,1));
            end
         end
     end
 end
 
 %the = the*0;
 
%  P0a = [0; 0; 0];
%  P1a = [l0; 0; 0];
%  P2a = [l0+l1*cos(the(1,1)-alpha); 0; l1*sin(the(1,1)-alpha)];
%  P3a = [l0+l1*cos(the(1,1)-alpha)+l2*cos(the(1,1)+the(1,2)-alpha)*cos(the(1,3));...
%         -l2*sin(the(1,3));...
%         l1*sin(the(1,1)-alpha)+l2*sin(the(1,1)+the(1,2)-alpha)*cos(the(1,3))];
%  P4a = [P3a(1,1)-size_ngang; P3a(2,1); P3a(3,1)];
%  P5a = [P3a(1,1)-size_ngang; P3a(2,1); P3a(3,1)-size_doc];    
% 
%  P0b = [0; 0; 0];
%  P1b = [-l0/2; (3^(1/2)*l0)/2; 0];
%  P2b = [-l0/2-l1*cos(the(1,4)-alpha)/2;...
%         sqrt(3)*l0/2+sqrt(3)*l1*cos(the(1,4)-alpha)/2;...
%         l1*sin(the(1,4)-alpha)];
%  P3b = [-l0/2-l1/2*cos(the(1,4)-alpha)-l2/2*cos(the(1,4)+the(1,5)-alpha)*cos(the(1,6))+l2*sqrt(3)/2*sin(the(1,6));...
%         sqrt(3)*l0/2+l2/2*(sin(the(1,6))+sqrt(3)*cos(the(1,4)+the(1,5)-alpha)*cos(the(1,6)))+sqrt(3)/2*l1*cos(the(1,4)-alpha);...
%         l1*sin(the(1,4)-alpha)+l2*sin(the(1,4)+the(1,5)-alpha)*cos(the(1,6))];
%  P4b = [P3b(1,1)-size_ngang*cos(2*pi/3); P3b(2,1)-size_ngang*sin(2*pi/3); P3b(3,1)];
%  P5b = [P4b(1,1); P4b(2,1); P4b(3,1)-size_doc];
%  
%  P0c = [0; 0; 0];
%  P1c = [-l0/2; -(3^(1/2)*l0)/2; 0];
%  P2c = [-l0/2-l1/2*cos(the(1,7)-alpha);...
%         -sqrt(3)*l0/2-sqrt(3)*l1*cos(the(1,7)-alpha)/2;...
%         l1*sin(the(1,7)-alpha)];
%  P3c = [-l0/2-l1/2*cos(the(1,7)-alpha)-l2/2*cos(the(1,7)+the(1,8)-alpha)*cos(the(1,9))-l2*sqrt(3)/2*sin(the(1,9));...
%         -sqrt(3)*l0/2+l2/2*(sin(the(1,9))-sqrt(3)*cos(the(1,7)+the(1,8)-alpha)*cos(the(1,9)))-sqrt(3)/2*l1*cos(the(1,7)-alpha);...
%         l1*sin(the(1,7)-alpha)+l2*sin(the(1,7)+the(1,8)-alpha)*cos(the(1,9))];
%  P4c = [P3c(1,1)-size_ngang*cos(4*pi/3); P3c(2,1)-size_ngang*sin(4*pi/3); P3c(3,1)];              
%  P5c = [P4c(1,1); P4c(2,1); P4c(3,1)-size_doc];
%  
%  Pxa = [P0a(1); P1a(1); P2a(1); P3a(1); P4a(1); P5a(1)];
%  Pya = [P0a(2); P1a(2); P2a(2); P3a(2); P4a(2); P5a(2)];
%  Pza = [P0a(3); P1a(3); P2a(3); P3a(3); P4a(3); P5a(3)];
%  Pxb = [P0b(1); P1b(1); P2b(1); P3b(1); P4b(1); P5b(1)];
%  Pyb = [P0b(2); P1b(2); P2b(2); P3b(2); P4b(2); P5b(2)];
%  Pzb = [P0b(3); P1b(3); P2b(3); P3b(3); P4b(3); P5b(3)];
%  Pxc = [P0c(1); P1c(1); P2c(1); P3c(1); P4c(1); P5c(1)];
%  Pyc = [P0c(2); P1c(2); P2c(2); P3c(2); P4c(2); P5c(2)];
%  Pzc = [P0c(3); P1c(3); P2c(3); P3c(3); P4c(3); P5c(3)];
%  %
% 
%  Pxg = [P3a(1); P3b(1); P3c(1); P3a(1)];
%  Pyg = [P3a(2); P3b(2); P3c(2); P3a(2)];
%  Pzg = [P3a(3); P3b(3); P3c(3); P3a(3)];
%  
%  Pxh0 = [0; 0];
%  Pyh0 = [0; 0];
%  Pzh0 = [100; -450];
%  Pxh1 = [l0; l0];
%  Pyh1 = [0; 0];
%  Pzh1 = [100; -450];
%  Pxh2 = [l0*cos(2*pi/3); l0*cos(2*pi/3)];
%  Pyh2 = [l0*sin(2*pi/3); l0*sin(2*pi/3)];
%  Pzh2 = [100; -450];
%  Pxh3 = [l0*cos(4*pi/3); l0*cos(4*pi/3)];
%  Pyh3 = [l0*sin(4*pi/3); l0*sin(4*pi/3)];
%  Pzh3 = [100; -450];
%  
%  n11 = sqrt(P1a(1,1)^2+P1a(2,1)^2+P1a(3,1)^2);
%  n12 = sqrt(P1b(1,1)^2+P1b(2,1)^2+P1b(3,1)^2);
%  n13 = sqrt(P1c(1,1)^2+P1c(2,1)^2+P1c(3,1)^2);
%  n21 = sqrt((P1a(1,1)-P2a(1,1))^2+(P1a(2,1)-P2a(2,1))^2+(P1a(3,1)-P2a(3,1))^2);
%  n22 = sqrt((P1b(1,1)-P2b(1,1))^2+(P1b(2,1)-P2b(2,1))^2+(P1b(3,1)-P2b(3,1))^2);
%  n23 = sqrt((P1c(1,1)-P2c(1,1))^2+(P1c(2,1)-P2c(2,1))^2+(P1c(3,1)-P2c(3,1))^2);
%  n31 = sqrt((P3a(1,1)-P2a(1,1))^2+(P3a(2,1)-P2a(2,1))^2+(P3a(3,1)-P2a(3,1))^2);
%  n32 = sqrt((P3b(1,1)-P2b(1,1))^2+(P3b(2,1)-P2b(2,1))^2+(P3b(3,1)-P2b(3,1))^2);
%  n33 = sqrt((P3c(1,1)-P2c(1,1))^2+(P3c(2,1)-P2c(2,1))^2+(P3c(3,1)-P2c(3,1))^2);
%  n41 = sqrt((P3a(1,1)-P4a(1,1))^2+(P3a(2,1)-P4a(2,1))^2+(P3a(3,1)-P4a(3,1))^2);
%  n42 = sqrt((P3b(1,1)-P4b(1,1))^2+(P3b(2,1)-P4b(2,1))^2+(P3b(3,1)-P4b(3,1))^2);
%  n43 = sqrt((P3c(1,1)-P4c(1,1))^2+(P3c(2,1)-P4c(2,1))^2+(P3c(3,1)-P4c(3,1))^2);
%  n51 = sqrt((P5a(1,1)-P4a(1,1))^2+(P5a(2,1)-P4a(2,1))^2+(P5a(3,1)-P4a(3,1))^2);
%  n52 = sqrt((P5b(1,1)-P4b(1,1))^2+(P5b(2,1)-P4b(2,1))^2+(P5b(3,1)-P4b(3,1))^2);
%  n53 = sqrt((P5c(1,1)-P4c(1,1))^2+(P5c(2,1)-P4c(2,1))^2+(P5c(3,1)-P4c(3,1))^2);
%  Thongso = [n11 n12 n13;...
%             n21 n22 n23;...
%             n31 n32 n33;...
%             n41 n42 n43;...
%             n51 n52 n53]
% Pnx1 = [P2a(1); P2a(1)];
% Pny1 = [P2a(2); P2a(2)];
% Pnz1 = [100; -450];
% Pnx2 = [P2b(1); P2b(1)];
% Pny2 = [P2b(2); P2b(2)];
% Pnz2 = [100; -450];
% Pnx3 = [P2c(1); P2c(1)];
% Pny3 = [P2c(2); P2c(2)];
% Pnz3 = [100; -450];
%    
% plot3(Pxa,Pya,Pza,'-ro',Pxb,Pyb,Pzb,'-bo',Pxc,Pyc,Pzc,'-go',...
%       Pxg,Pyg,Pzg,'-om',...
%       Pxh0,Pyh0,Pzh0,'-oy',Pxh1,Pyh1,Pzh1,'-oy',Pxh2,Pyh2,Pzh2,'-oy',Pxh3,Pyh3,Pzh3,'-oy',...
%       Pnx1,Pny1,Pnz1,'-oy',Pnx2,Pny2,Pnz2,'-oy',Pnx3,Pny3,Pnz3,'-oy',...
%       'linewidth',1); 
% 
%  axis([-300 300 -300 300 -450 100]) ; grid on;
%  

  the = the*180/pi;

 PWM(1,1) = the(1,1)*(3200/360)*1.6;
 PWM(1,2) = the(1,4)*(3200/360)*1.6;
 PWM(1,3) = the(1,7)*(3200/360)*1.6;
 axis = [x1 y1 z1; x2 y2 z2; x3 y3 z3];
 PWM_Show = PWM/((3200/360)*1.6)
 PWM
 

 
 