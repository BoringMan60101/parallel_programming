// Initializing constants, related to spatial and temporal discretization //
const int m = argc > 1 ? atoi(argv[1]) : 20;
const int M = (m+1) * (m+1);

const double h = 1.0 / m;

const double T_final = 1.0;

//const double dt = 0.5 * (h*h/2.0);
/*
int N1 = (int)(T_final/dt);
int N2 = 0;
if(T_final - dt*N1 < 1e-15)
    N2 = N1 - 1;
if(T_final - dt*N1 > 1e-15)
    N2 = N1 + 1;
else
    N2 = N1;
const int Nt = N2;
printf("There are %d time steps for h=%lf\n", Nt, h); // 'Debug' information
if(fabs(T_final - Nt*dt) > 1e-15)
    fprintf(stderr, "Wrong \'Nt\' calculated for \'m\'=%d\n", m);
*/
const int Nt = 40000;
const double dt = 1.0 / Nt;

// Parameters for iterative solution with Gauss-Seidel method
const int itersLimit = 1000;
const double eps = 1e-10;
double norm = 2.0 * eps; // Actual value of 'norm' is calculated in Gauss-Seidel loop
const double C1 = 1.0/(h*h);
const double C2 = 4.0/(h*h) + 1.0/dt;
const double C3 = C1/C2;
