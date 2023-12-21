#include <cstdio>
#include <cstdlib>

int main(const int argc, const char **argv)
{
    if(argc != 4)
    {
        fprintf(stderr, "Wrong arguments given\n");
        fprintf(stderr, "Give two float numbers and operator\n");
        return 1;
    }

    switch(argv[2][0])
    {
        case '/':
        {
            fprintf(stdout, "%lf\n", atof(argv[1]) / atof(argv[3]));
            break;
        }
        case '*':
        {
            fprintf(stdout, "%lf\n", atof(argv[1]) * atof(argv[3]));
            break;
        }
        case '+':
        {
            fprintf(stdout, "%lf\n", atof(argv[1]) + atof(argv[3]));
            break;
        }
        case '-':
        {
            fprintf(stdout, "%lf\n", atof(argv[1]) - atof(argv[3]));
            break;
        }
        defualt:
            fprintf(stdout, "Wrong arithmetic operator given. Supported: +, -, *, / \n");
    }

    return 0;
}
