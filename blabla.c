#include <stdio.h>
int main(int argc, char const *argv[],char**env)
{
    int i = 0;
    while (env[i])
    {
        printf("%s\n",env[i++]);
    }
    
    return 0;
}
