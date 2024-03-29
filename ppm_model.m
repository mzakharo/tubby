function ppm = ppm_model(x, y, xm, xs, ym, ys)
    x = (x - xm) / xs;
    y = (y - ym) / ys;
    p00 =  1.692038740410026 ;    
    p10 =  1.346668856458132;   
    p01 =  0.411894450004881 ;    
    p20 =  0.543701463012560 ;   
    p11 =  0.445986985137331;   
    p02 =  0.087408287395104; 
    p30 =  0.129545323180402 ;    
    p21 =  0.194585373805381;    
    p12 =  0.082725684204779 ;  
    p40 =  0.013825395134957 ;   
    p31 =  0.031610487461203; 
    p22 =  0.019475608702437;   
    ppm = p00 + p10*x + p01*y + p20*x^2 + p11*x*y + p02*y^2 + p30*x^3 + p21*x^2*y + p12*x*y^2 + p40*x^4 + p31*x^3*y + p22*x^2*y^2;

end