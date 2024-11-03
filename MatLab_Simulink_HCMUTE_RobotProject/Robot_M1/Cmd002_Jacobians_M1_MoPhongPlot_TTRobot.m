z1 = high.Data ; 
the2 = theta2.Data ; 
the3 = theta3.Data ;

l1=1;
l2=1;


for i = 1:100
    c2=cos(the2(i));s2=sin(the2(i));
    c3=cos(the3(i));s3=sin(the3(i));
    c23=cos(the2(i)+the3(i));
    s23=sin(the2(i)+the3(i));
    z=z1(i);
    if(z1(i)<0)
        z = 0;
    end
    
    P_0_1 = [0; 0; z];
    P_0_2 = [l1*c2; l1*s2; z];
    P_0_EE= [(l2*c23 + l1*c2); (l2*s23 + l1*s2); z];

    Px = [0; P_0_1(1); P_0_2(1); P_0_EE(1) ];
    Py = [0; P_0_1(2); P_0_2(2); P_0_EE(2) ];
    Pz = [0; P_0_1(3); P_0_2(3); P_0_EE(3) ];
    %plot3(Px,Py,Pz,'-ro','linewidth',2) ;
    plot3(Px,Pz,Py,'-ro','linewidth',2) ;
    axis([-6 6 -5 5 -4 4]) ; grid on 
    pause(0.1)
end 
