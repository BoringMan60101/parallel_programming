#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <omp.h>

// Test function: U_an = x^2 + y^2 + 4t
// Initial condition at zero time monent //
double U_init(double x, double y) { return x*x + y*y; }
// ***************************************************************** //

// Boundary conditions and source term //
double U_minX(double y, double t) { return y*y + 4.0*t; }
double U_maxX(double y, double t) { return 1.0 + y*y + 4.0*t; }
double U_minY(double x, double t) { return x*x + 4.0*t; }
double U_maxY(double x, double t) { return 1.0 + x*x + 4.0*t; }
double Source(double x, double y, double t) { return 0.0; }
// ***************************************************************** //

// Norm is calculated only for internal points (L_1 <= L_2 <= L_inf)
// All functions are being executed in parallel mode
double norm_L_1(double const * U1, double const * U0, const int m);
//double norm_L_2(double const * U1, double const * U0, const int m);
//double norm_L_inf(double const * U1, double const * U0, const int m);
void printDataToFile(double const * U, const int m, const double time);
// ***************************************************************** //


int main(const int argc, const char ** argv) {
    //const double startTime = omp_get_wtime();

    omp_set_nested(true);

    // Initializing:
    // Constants, related to spatial and temporal discretization
    // Parameters for iterative solution with Gauss-Seidel method
    #include "setConstants.CPP"

    // Creating fields:
    // U -- contains field values for all time steps
    // U0 and U1[M] -- auxilary arrays
    #include "createFields.CPP"

    // Initial conditions //
    #pragma omp parallel for
    for(int i = 0; i <= m; i++) // 'Goes' along X direction
        for(int j = 0; j <= m; j++) // 'Goes' along Y direction
            U[0][i*(m+1) + j] = U_init(i*h, j*h);
    printDataToFile(U[0], m, 0.0);


    // Solving for each time step with Gauss-Seidel method //
    for(int t = 1; t <= Nt; t++)
    {
        // Boundary condtions and initial approximation //
        #pragma omp parallel
        {
            #pragma omp for nowait
            for(int i = 0; i <= m; i++)
            {
                int idx1 = i; // x = 0
                U0[idx1] = U1[idx1] = U_minX(i*h, t*dt);

                int idx2 = m*(m+1) + i; // x = 1
                U0[idx2] = U1[idx2] = U_maxX(i*h, t*dt);

                int idx3 = i*(m+1); // y = 0
                U0[idx3] = U1[idx3] = U_minY(i*h, t*dt);

                int idx4 = i*(m+1) + m; // y = 1
                U0[idx4] = U1[idx4] = U_maxY(i*h, t*dt);
            }
            // ***************************************************************** //

            // Initial approximation for solution //
            #pragma omp for
            for(int i = 1; i < m; i++)
                for(int j = 1; j < m; j++)
                {
                    int idx = i*(m+1) + j;
                    U0[idx] = U[t-1][idx];
                }
        } // End parallel region


        // Iterative solution (Gauss-Seidel method) for current time step //
        norm = 2.0 * eps;
        for(int iter = 1; iter <= itersLimit && norm > eps; iter++)
        {
            #pragma omp parallel
            {
                // 'Black' cells
                #pragma omp for
                for(int i = 1; i < m; i++)
                    for(int j = 2 - (i%2); j < m; j += 2)
                    {
                        int idx = i*(m+1) + j;
                        double sum1 = (U0[idx - m - 1] + U0[idx - 1]) * C3;
                        double sum2 = (U0[idx + m + 1] + U0[idx + 1]) * C3;
                        double sum3 = (U[t-1][idx]/dt + Source(i*h, j*h, t*dt))/C2;
                        U1[idx] = sum1 + sum2 + sum3;
                    }

                // 'Red' cells
                #pragma omp for
                for(int i = 1; i < m; i++)
                    for(int j = 1 + (i%2); j < m; j += 2)
                    {
                        int idx = i*(m+1) + j;
                        double sum1 = (U1[idx - m - 1] + U1[idx - 1]) * (C1/C2);
                        double sum2 = (U1[idx + m + 1] + U1[idx + 1]) * (C1/C2);
                        double sum3 = (U[t-1][idx]/dt + Source(i*h, j*h, t*dt))/C2;
                        U1[idx] = sum1 + sum2 + sum3;
                    }


                #pragma omp single
                {
                    norm = norm_L_1(U1, U0, m);
                    if(iter == itersLimit)
                        printf("At time:%lf iterations limit (%d) was reached, final \'norm\':%g\n", t*dt, itersLimit, norm);
                }


                // Updating values in solution vector
                #pragma omp for
                for(int i = 1; i < m; i++)
                    for(int j = 1; j < m; j++)
                    {
                        int idx = i*(m+1) + j;
                        U0[idx] = U1[idx];
                    }

                //#pragma omp single
                    //printDataToFile(U[t], m, t*dt);

            } // End parallel region
        } // End 'Gauss-Seidel' loop for this time step


        // Saving found solution //
        #pragma omp parallel for
        for(int i = 0; i <= m; i++)
            for(int j = 0; j <= m; j++)
            {
                int idx = i*(m+1) + j;
                U[t][idx] = U1[idx];
            }
    } // End time steps loop


    // Write data at last time step
    printDataToFile(U[Nt], m, Nt*dt);

    // Deallocating memory //
    for(int t = 0; t <= Nt; t++)
        delete [] U[t];
    delete [] U;
    delete [] U0;
    delete [] U1;

    //printf("Run time: %lf\n", omp_get_wtime() - startTime);
    return 0;
}


// Norm is calculated only for internal points
double norm_L_1(double const * U1, double const * U0, const int m) {
    double norm = 0.0;
    #pragma omp parallel for
    for(int i = 1; i < m; i++)
        for(int j = 1; j < m; j++)
        {
            int idx = i*(m+1) + j;
            norm += fabs(U1[idx] - U0[idx]);
        }
    return norm;
}
/*
double norm_L_2(double const * U1, double const * U0, const int m) {
    double norm = 0.0;
    #pragma omp parallel for
    for(int i = 1; i < m; i++)
        for(int j = 1; j < m; j++)
        {
            int idx = i*(m+1) + j;
            norm += (U1[idx] - U0[idx]) * (U1[idx] - U0[idx]);
        }
    return sqrt(norm);
}

double norm_L_inf(double const * U1, double const * U0, const int m) {
    double norm = 0.0;
    #pragma omp parallel for
    for(int i = 1; i < m; i++)
        for(int j = 1; j < m; j++)
        {
            int idx = i*(m+1) + j;
            double dif = fabs(U1[idx] - U0[idx]);
            if(dif > norm)
                norm = dif;
        }
    return norm;
}
*/
// ***************************************************************** //


void printDataToFile(double const * U, const int m, const double time) {
    char timeName [32];
    sprintf(timeName, "%lf", time);

    FILE * fp = fopen(timeName, "w");
    if(fp == nullptr)
    {
        fprintf(stderr, "Error with opening file to write data at time: %lf\n", time);
        return;
    }

    const double h = 1.0/m;
    #pragma omp parallel for
    for(int i = 0; i <= m; i++)
        for(int j = 0; j <= m; j++)
            fprintf(fp, "%lf %lf %lf\n", i*h, j*h, U[i*(m+1) + j]);
    fclose(fp);
}
