clear all;
clc;
d2=140; d5=113.9; z=1;
the2_tam = -45;
the3_tam = 45;
the2 = the2_tam*pi/180;
the3 = the3_tam*pi/180;
c2=cos(the2);
s2=sin(the2);
c3=cos(the3);
s3=sin(the3);
c23=cos(the2 + the3);
s23=sin(the2 + the3);
P_0_EE = [(d5*c23 + d2*c2); (d5*s23 + d2*s2); z]