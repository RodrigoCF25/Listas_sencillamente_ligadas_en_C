#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>


using namespace std;


typedef struct DNODE* PDNODE;

struct DNODE {
    string sNombre;
    int sFrec;
    PDNODE sNext;
};


class DList_sencilla
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;
    bool aFrec;

public:
    DList_sencilla(bool pFrec = false);
    ~DList_sencilla(void);

    void clean(void);

    void push_front(string pNombre);
    void push_back(string pNombre);
    void push(string pNombre);

    PDNODE top_front(void);
    PDNODE top_back(void);
    PDNODE get();

    void pop_front(void);
    void pop_back(void);
    void del(string pNombre, bool pForce = false);

    bool isEmpty(void);
    void repr(bool pRev = false);
    void read(string pPath, char pMethod = 'b');
    void write(string pPath, bool pRev = false);

private:
    PDNODE find(string pNombre);
    PDNODE search(string pNombre);
    PDNODE search(PDNODE pDNode);
    PDNODE getNewNode(string pNombre);

};

