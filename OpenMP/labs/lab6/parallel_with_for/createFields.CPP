//double U[Nt+1][M], U0[M], U1[M];

double ** U = new double * [Nt + 1];
if(U == nullptr)
{
    fprintf(stderr, "Error with memory allocation\n");
    exit(EXIT_FAILURE);
}
for(int t = 0; t <= Nt; t++)
{
    U[t] = new double [M];
    if(U[t] == nullptr)
    {
        fprintf(stderr, "Error with memory allocation\n");
        exit(EXIT_FAILURE);
    }
}

double * U0 = new double [M];
double * U1 = new double [M];
if(U0 == nullptr || U1 == nullptr)
{
    fprintf(stderr, "Error with memory allocation\n");
    exit(EXIT_FAILURE);
}
