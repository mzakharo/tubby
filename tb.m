close all;
M =csvread('dataset.csv', 2);
X = M(:,1);
Y = M(:, 2);
Z = M(:, 3);
fitresult = createFit(X,Y, Z)

coef = coeffnames(fitresult);
for k=1:length(coef)
   %curstate=coef{k}
   exp = sprintf('%s = fitresult.%s;',coef{k},coef{k});
   eval(exp)  ;  
end

fitresult( 700, 7.3)
ppm_model(700,  7.3, fitresult)

% maxi = max(M',[],2);
% mini = min(M',[],2);
% proj_long = mini(1):1:maxi(1);
% proj_lat = mini(2):0.1:maxi(2);
%F = scatteredInterpolant(M(:,1), M(:,2), M(:, 3));
%[PROJ_LONG, PROJ_LAT] = ndgrid(proj_long, proj_lat);
%PROJ_EE = F(PROJ_LONG, PROJ_LAT);
%surf(PROJ_LONG, PROJ_LAT, PROJ_EE, 'edgecolor', 'none');
%fitobject = fit(x, M(:, 3), 'poly23')
%plot(M(3,:))