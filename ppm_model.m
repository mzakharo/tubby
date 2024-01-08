function ppm = ppm_model(x, y, f)
       p00 =         1.7  ;%(1.698, 1.701)
       p10 =       1.331  ;%(1.329, 1.333)
       p01 =       0.386  ;%(0.3836, 0.3883)
       p20 =      0.5251  ;%(0.5226, 0.5276)
       p11 =      0.4133  ;%(0.4107, 0.4158)
       p02 =     0.07483 ; %(0.07276, 0.07691)
       p30 =      0.1372 ; %(0.1357, 0.1387)
       p21 =      0.2071 ; %(0.205, 0.2092)
       p12 =     0.09467 ; %(0.09231, 0.09703)
       p03 =     0.01276 ; %(0.009873, 0.01565)
       p40 =     0.02283 ; %(0.02128, 0.02437)
       p31 =     0.05666 ; %(0.05433, 0.059)
       p22 =     0.04778 ; %(0.04587, 0.04968)
       p13 =     0.01679 ; %(0.01557, 0.01801)
       p04 =    0.002251 ; %(0.001498, 0.003004)
       p50 =    0.001673 ; %(0.001271, 0.002075)
       p41 =    0.006438 ; %(0.00578, 0.007096)
       p32 =     0.00833 ; %(0.007609, 0.009052)
       p23 =    0.004907 ; %(0.004137, 0.005676)
       p14 =    0.001765 ; %(0.0009246, 0.002605)
       p05 =   0.0004527 ;% (-0.0004026, 0.001308)
    x = (x - 768.6) / 97.75;
    y = (y - 7.251) / 0.4607;
    ppm = p00 + p10*x + p01*y + p20*x^2 + p11*x*y + p02*y^2 + p30*x^3  + p21*x^2*y + p12*x*y^2 + p03*y^3 + p40*x^4 + p31*x^3*y  + p22*x^2*y^2 + p13*x*y^3 + p04*y^4 + p50*x^5 + p41*x^4*y + p32*x^3*y^2 + p23*x^2*y^3 + p14*x*y^4 + p05*y^5;
end