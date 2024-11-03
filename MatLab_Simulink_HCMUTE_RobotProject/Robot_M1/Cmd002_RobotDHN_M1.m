clear all;
clc;
%syms x y the2 the3 d2 d5;
x=1.1; y=1.3; d2=1; d5=1; z=1.0;

the3 = basic_atan2( (2*d2*d5), (0) , (x*x + y*y - d2*d2 - d5*d5))
the3_1 = the3(1,1);
the3_2 = the3(2,1);

the2_1 = basic_atan2( (d5*cos(the3_1) + d2), -(d5*sin(the3_1)) , (x));
the2_2 = basic_atan2( (d5*cos(the3_2) + d2), -(d5*sin(the3_2)) , (x));
the2_3 = basic_atan2( (d5*sin(the3_1) ), (d5*cos(the3_1) + d2) , (y));
the2_4 = basic_atan2( (d5*sin(the3_2) ), (d5*cos(the3_2) + d2) , (y));
the2 = [the2_1(1,1); the2_1(2,1); the2_2(1,1); the2_2(2,1); the2_3(1,1); the2_3(2,1); the2_4(1,1); the2_4(2,1)]

n=0;
 for i = 1:2
     for j = 1:8     
         PX = d2*cos(the2(j,1)) + d5*cos(the2(j,1)+the3(i,1));
         PY = d2*sin(the2(j,1)) + d5*sin(the2(j,1)+the3(i,1));
         X_tam = abs((PX - x));
         Y_tam = abs((PY - y));
          if((X_tam<=0.0005)&&(Y_tam<=0.0005))
            n = n+1;
            the(n,1) = (the2(j,1));
            the(n,2) = (the3(i,1));
            
          end
     end
 end
 
 the = the*180/pi;
 the2_tam = [the(1,1); the(2,1)];
 the3_tam = [the(1,2); the(2,2)];
 the2_out = the2_tam;
 the3_out = the3_tam;
 
 