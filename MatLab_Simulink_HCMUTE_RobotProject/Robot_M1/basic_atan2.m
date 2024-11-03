function out = basic_atan2(a,b,d) %acos(the)+bsin(the) = d
anp = atan2(b,a);
the_1 = anp + atan2(sqrt(abs(a*a + b*b - d*d)), d);
the_2 = anp + atan2(-sqrt(abs(a*a + b*b - d*d)), d);
out = [the_1; the_2];
end
