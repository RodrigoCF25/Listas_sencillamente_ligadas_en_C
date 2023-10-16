#include "DList_sencilla.h"



DList_sencilla::DList_sencilla(bool pFrec)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFrec = pFrec;
} // Constructor

DList_sencilla::~DList_sencilla(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DList_sencilla::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DList_sencilla::push_front(string pNombre)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else {
        bool lDo = true;
        if (aFrec) {
            if (pNombre == aHead->sNombre) {
                (aHead->sFrec)++;
                lDo = false;
            }
            else {
                PDNODE lItem = find(pNombre);
                if (lItem != NULL) 
                {
                    (lItem->sFrec)++;
                    lDo = false;
                }
            }
        }
        if (lDo) {
            PDNODE lTemp = getNewNode(pNombre);
            lTemp->sNext = aHead;
            aHead = lTemp;
        }
    }
} // push_front

void DList_sencilla::push_back(string pNombre)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else {
        bool lDo = true;
        if (aFrec) {
            if (pNombre == aTail->sNombre) {
                (aTail->sFrec)++;
                lDo = false;
            }
            else {
                PDNODE lItem = find(pNombre);
                if (lItem != NULL) {
                    (lItem->sFrec)++;
                    lDo = false;
                }
            }
        }
        if (lDo) {
            PDNODE lTemp = getNewNode(pNombre);
            aTail->sNext = lTemp;
            aTail = lTemp;
        }
    }
} // push_back

void DList_sencilla::push(string pNombre)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else {
        if (pNombre <= aHead->sNombre)
            push_front(pNombre);
        else if (pNombre >= aTail->sNombre)
            push_back(pNombre);
        else {
            PDNODE lItem = search(pNombre);
            if (lItem) {
                if (aFrec && (lItem->sNombre == pNombre)) {
                    (lItem->sFrec)++;
                }
                else {
                    PDNODE lTemp = getNewNode(pNombre);
                    lTemp->sNext = lItem->sNext;
                    lItem->sNext = lTemp;
                }
            }
        }
    }
} // push

PDNODE DList_sencilla::top_front(void)
{
    if (aHead) {
        return aHead;
    }
    return NULL;
} // top_front

PDNODE DList_sencilla::top_back(void)
{
    if (aHead) {
        return aTail;
    }
    return NULL;
} // top_back

PDNODE DList_sencilla::get()
{
    PDNODE lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL)
            aCurr = aHead;
        else
            aCurr = aCurr->sNext;
        lTemp = aCurr;
    }

    return lTemp;
} // get

void DList_sencilla::pop_front(void)
{
    bool lDo = true;

    if (aHead) {
        if (aFrec) {
            (aHead->sFrec)--;
            if (aHead->sFrec > 0)
                lDo = false;
        }
    }
    else
        lDo = false;
    if (lDo) {
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;
        if (aHead) {
            aCurr = (lEqual ? aHead : aCurr);
        }
        else {
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DList_sencilla::pop_back(void)
{
    bool lDo = true;

    if (aHead) {
        if (aFrec) {
            (aTail->sFrec)--;
            if (aTail->sFrec > 0)
                lDo = false;
        }
    }
    else
        lDo = false;
    if (lDo) {
        PDNODE lTemp = search(aTail->sNombre);
        if (lTemp)
        {
            bool lEqual = (aTail == aCurr);
            delete aTail;
            aTail = lTemp;

            if (aTail) {
                aTail->sNext = NULL;
                aCurr = (lEqual ? aTail : aCurr);
            }
            else {
                aHead = NULL;
                aCurr = NULL;
            }
        }
    }
} // pop_back

void DList_sencilla::del(string pNombre, bool pForce)
{
    if (aHead) {
        if (aHead->sNombre == pNombre)
        {
            pop_front();
        }
        else if (aTail->sNombre == pNombre)
        {
            pop_back();
        }
        else
        {
            PDNODE lTemp = find(pNombre);
            PDNODE lItem = search(pNombre);
            if (lTemp && lItem)
            {
                if (!aFrec)
                    lTemp->sFrec = 0;
                else
                    if (!pForce)
                        (lTemp->sFrec)--;
                    else
                        lTemp->sFrec = 0;
                if (lTemp->sFrec == 0)
                {
                    if (aCurr == lTemp)
                    {
                        aCurr = lTemp->sNext;
                    }
                    lItem->sNext = lTemp->sNext;
                    delete lTemp;
                }
            }
        }
    }
} // del

bool DList_sencilla::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DList_sencilla::repr(bool pRev)
{
    if (aHead) {
        if (pRev == false)
        {
            PDNODE lTemp = aHead;
            while (lTemp) {
                cout << " -> ";
                cout << lTemp->sNombre;
                if (aFrec)
                    cout << " #" << lTemp->sFrec;
                lTemp = lTemp->sNext;
            }
            cout << " ->|| " << endl;
        }
        else
        {
            PDNODE lTemp = aTail;
            while (lTemp)
            {
                cout << " -> ";
                cout << lTemp->sNombre;
                if (aFrec)
                    cout << " #" << lTemp->sFrec;
                lTemp = search(lTemp);
            }
            cout << " ->|| " << endl;
        }
    }
} // repr

void DList_sencilla::read(string pPath, char pMethod)
{
    auto lStart = chrono::high_resolution_clock::now();
    string lLine = "";
    ifstream lFile(pPath);

    while (getline(lFile, lLine)) {
        switch (pMethod) {
        case 'b':
            push_back(lLine);
            break;
        case 'f':
            push_front(lLine);
            break;
        default:
            push(lLine);
            break;
        }
    }

    lFile.close();

    auto lElapsed = chrono::high_resolution_clock::now() - lStart;
    long long lMS = chrono::duration_cast<chrono::microseconds>
        (lElapsed).count();
    cout << lMS << " ms" << endl;
} // read

void DList_sencilla::write(string pPath, bool pRev)
{
    if (aHead) {
        ofstream lFile(pPath);
        if (lFile.is_open()) {
            if (pRev == false)
            {
                PDNODE lTemp = aHead;
                while (lTemp) {
                    for (int i = 0; i < lTemp->sFrec; i++)
                    {
                        lFile << lTemp->sNombre << endl;
                    }
                    lTemp = lTemp->sNext;
                }
            }
            else
            {
                PDNODE lTemp = aTail;
                while (lTemp)
                {
                    for (int i = 0; i < lTemp->sFrec; i++)
                    {
                        lFile << lTemp->sNombre << endl;
                    }
                    lTemp = search(lTemp);
                }
            }
            lFile.close();
        }
    }
} // write

PDNODE DList_sencilla::find(string pNombre)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pNombre == lTemp->sNombre)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PDNODE DList_sencilla::search(string pNombre) //para meter ordenadamnte, nada más
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if ((pNombre <= lTemp->sNext->sNombre))
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DList_sencilla::search(PDNODE pNode) // para la impresión en reversa
{
    PDNODE lTemp = NULL;
    lTemp = aHead;
    while (lTemp)
    {
        if (lTemp->sNext == pNode)
        {
            return lTemp;
        }
        lTemp = lTemp->sNext;
    }
    return NULL;
}



PDNODE DList_sencilla::getNewNode(string pNombre)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sNombre = pNombre;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
    }

    return lTemp;
} // getNewNode
