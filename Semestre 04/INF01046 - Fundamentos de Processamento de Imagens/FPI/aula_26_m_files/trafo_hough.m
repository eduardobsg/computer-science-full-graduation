function [h, theta, rho] = trafo_hough(f, dtheta, drho) 
 
drho = 1; 
dtheta = 1; 
 
f = double(f); 
[M,N] = size(f);

ntheta = 2 * ceil(90/dtheta) + 1; 
theta = linspace(-90, 89, ntheta); 

D = sqrt((M - 1)^2 + (N - 1)^2); 
q = ceil(D/drho); 
nrho = 2*q - 1; 
rho = linspace(-q*drho, q*drho, nrho); 
 
[x, y, val] = find(f); 
x = x - 1;  y = y - 1; 
 
h = zeros(nrho, ntheta); 

points = length(x);

senos   = sin( theta .* ( pi/180 ));
cosenos = cos( theta .* ( pi/180 ));

for k = 1:points 
  for t = 1:ntheta 
    rhok = x(k)* cosenos(t) + y(k) * senos(t);
    slope = (nrho - 1)/(rho(end) - rho(1)); 
    ro_bin = round(slope*( rhok - rho(1)) + 1); 
    h(ro_bin, t) = h(ro_bin, t) + 1;
  end;  
end 
