#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "DList_sencilla.h"

using namespace std;

int main()
{
    DList_sencilla list = DList_sencilla(true);
    
    /*
    list.push_front("Ro");
    list.push_front("Da");
    list.push_front("Lety");
    list.push_front("Armando");
    list.push_front("Layla");
    list.push_front("Ro");
    list.push_front("Lety");
    */

    list.read("D:/Quinto semestre/Nombres.txt",'p');

    list.repr();
    
    list.write("D:/Quinto semestre/Nombres.txt");
    
}

