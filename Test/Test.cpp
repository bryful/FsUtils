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


    //std::cout << listupAEProcess(isu);
    //std::cout << "Hello World!\n";

    //POINT p = GetMousePos();
    //std::cout << std::to_string(p.x)+"\n";
    //std::cout << std::to_string(p.y) + "\n";
    BeepPlay(argc-1);

}
