#include <cstdlib>

void fun (float f) {}

int main (int argc, char ** argv)
{
    unsigned char i = -1;
    unsigned char data [16];
    unsigned char c = data [i];

    float f = c / (argc - 1);

    void (* fptr)(int) = reinterpret_cast <void (*)(int)> (& fun);
    fptr (42);

    return EXIT_SUCCESS;
}
