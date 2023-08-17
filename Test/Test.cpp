#include "..\Utils\Util.h"
#include "..\Utils\AEProcess.h"
#include <iostream>


int main(int argc, char* argv[])
{
    //listupAE();
    BOOL isu = false;
    if (argc > 1)
    {
        isu = true;
    }


    std::cout << listupAEProcess(isu);
    //std::cout << "Hello World!\n";


}
