clear all;
clc;
%syms l0 l1 l2 
l0=1; l1=1.5; l2=4; 
anp = 90*pi/180;

the2_1=0-anp; the3_1=0; the4_1=0;
c2_1=cos(the2_1); s2_1=sin(the2_1); c3_1=cos(the3_1); s3_1=sin(the3_1); c4_1=cos(the4_1); s4_1=sin(the4_1);
c23_1=cos(the2_1+the3_1); s23_1=sin(the2_1+the3_1);

Px = l0 + l1*c2_1 + l2*c23_1*c4_1;
Py = -l2*s4_1;
Pz = l1*s2_1 + l2*s23_1*c4_1;
Pee1 = [Px; Py; Pz;];

%Pee2     
the3_2=53.9528*pi/180; the4_2=137.3623*pi/180; the5_2=-45.0000*pi/180;
The3=318.5914*pi/180; The4=55.7711*pi/180; The5=-0.0029*pi/180;
c3_2=cos(the3_2); s3_2=sin(the3_2); c4_2=cos(the4_2); s4_2=sin(the4_2); c5_2=cos(the5_2); s5_2=sin(the5_2);
c34_2=cos(the3_2+the4_2); s34_2=sin(the3_2+the4_2);

Px = - l0/2 - (l1*cos(The3 - anp))/2 - l2*((cos(The3 + The4 - anp)*cos(The5))/2 + l2*(3^(1/2)*sin(The5))/2);
Py = (3^(1/2)*l0)/2 + l2*(sin(The5)/2 + (3^(1/2)*cos(The3 + The4 - anp)*cos(The5))/2) + (3^(1/2)*l1*cos(The3 - anp))/2;
Pz = l1*sin(The3 - anp) + l2*sin(The3 + The4 - anp)*cos(The5)
Pee2 = [Px; Py; Pz;]
