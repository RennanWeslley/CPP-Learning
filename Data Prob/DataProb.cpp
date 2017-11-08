#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "Data.h"

#define COL 5

string lineData[] = {" |  Data Type ", " |  Freq.Abs. ", " | Freq.Rel. ", "|  Freq.Rel.(%)", " | Freq.Rel.Ac. |"};

bool search(vector<int>, int);
int numOf(vector<int>, int);
void drawTable(vector<Data>, int, int, int, int, int);

int main() {
    int L = 0;
    
    float sumFreqRel,
          sumFreqRelPer,
          sumFreqRelAc;
        
    sumFreqRel = sumFreqRelPer = sumFreqRelAc = 0;
        
    vector<Data> data;
    vector<int> dataN;
    vector<int> dataName;
    Data *dataT;
    
    /* Recieving user data files */
    for(string s; 1; L++) {
        cout << "Digite o " << (L+1) << "º dado ou \"exit\" para sair: ";
        cin >> s;
        cin.ignore();
        
        if(!s.compare("exit"))
            break;
        
        dataN.push_back(stoi(s));         // stoi() func. needs C11 compiler
        sort(dataN.begin(), dataN.end()); // Sorting the vector dataN
    }
    /* End Of Recieving Data */
    
    /* Setting Name */
    for(int i = 0; i < dataN.size(); i++)
        if(!search(dataName, dataN[i]))
            dataName.push_back(dataN[i]);
    /* End Of Set Name */
    
    /* Setting Atributes */
    for(int i = 0; i < dataName.size(); i++) {
        dataT = new Data();
        dataT->setName(dataName[i]);
        dataT->setFreqAbs(numOf(dataN, dataT->getName()));
        dataT->calcFreqRel(L);
        dataT->calcFreqRelPer(L);
        data.push_back(*dataT);
        
        /* Sum */
        sumFreqRel    += dataT->getFreqRel();
        sumFreqRelPer += dataT->getFreqRelPer();
//         sumFreqRelAc  += dataT->getFreqRelAc();
        /* End Of Sum */
    }
    /* End Of Set Atributes */

    /* Drawing Table */
    drawTable(data, dataName.size(), dataN.size(), sumFreqRel, sumFreqRelPer, sumFreqRelAc);
}

bool search(vector<int> data, int num) {
    for(int i = 0; i < data.size(); i++) {
        if(num == data[i])
            return true;
    }
    
    return false;
}

int numOf(vector<int> data, int num) {
    int j = 0;
    
    for(int i = 0; i < data.size(); i++)
        if(num == data[i])
            j++;
        
    return j;
}

void drawTable(vector<Data> data, int L, int sumFreqAbs, int sumFreqRel, int sumFreqRelPer, int sumFreqAc) {
    stringstream sumAbs,
                 sumRel,
                 sumPer,
                 sumAc;
                 
    sumAbs << setw(3) << sumFreqAbs;
    sumRel << setw(3) << sumFreqRel;
    sumPer << setw(3) << sumFreqRelPer;
    sumAc  << setw(3) << sumFreqAc;
    
    cout << endl;
    for(int i = 0; i < COL; i++)
        cout << lineData[i];

    cout << endl;
    for(int i = 0; i < L; i++) 
        cout << data[i].stringTable() << endl;
    
    cout << "      Total          " << sumAbs.str()
         << "           "           << sumRel.str()
         << "          "            << sumPer.str()
         << "            "           << sumAc.str() 
         << "       "                << endl << endl;
}