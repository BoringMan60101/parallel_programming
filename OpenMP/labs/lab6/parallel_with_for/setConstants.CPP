// Initializing constants, related to spatial and temporal discretization //
const int m = argc > 1 ? atoi(argv[1]) : 20;
const int M = (m+1) * (m+1);

const double h = 1.0 / m;

const double T_final = 1.0;

const double dt = 0.5 * (h*h/2.0);

int N1 = (int)(T_final/dt);
int N2 = 0;
if(T_final - dt*N1 < 1e-15)
    N2 = N1 - 1;
if(T_final - dt*N1 > 1e-15)
    N2 = N1 + 1;
else
    N2 = N1;
const int Nt = N2;

if(fabs(T_final - Nt*dt) > 1e-15)
    fprintf(stderr, "Wrong \'Nt\' calculated for \'m\'=%d\n", m);
