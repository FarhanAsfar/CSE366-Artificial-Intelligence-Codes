#include<bits/stdc++.h>
#include<stdio.h>
#include<cstdlib>
#include<vector>

using namespace std;
string bin;
int point;
vector<string>binry;

struct chromosome
{
    int a, b;
    double fitness ;

} temp, dvalue[6], par[6];


int f(int a, int b){
    return 2*a*a + 3*b - 38 ;
}
void calculateFitness()
{
    for(int i = 0 ; i < 6 ; i++){
        int fVal = abs(f(dvalue[i].a, dvalue[i].b)) ;
        dvalue[i].fitness = 1.00/fVal ;

    }
}
void copyToPar(int x, int y){
    par[y].a = dvalue[x].a ;
    par[y].b = dvalue[y].b ;

}
void chooseParent(){
    for(int i = 0 ; i < 6 ; i++){
        for(int j = 0 ; j < 6 ; j++){
            if(dvalue[i].fitness < dvalue[j].fitness){
                temp = dvalue[i] ;
                dvalue[i] = dvalue[j] ;
                dvalue[j] = temp ;
            }
        }
    }

    int cur = 0 ;
    for(int i = 0 ; i < 6 ; i++){
        int randVal = rand() % 9 ;
        if(randVal == 0 || randVal == 6 || randVal == 7){
         copyToPar(0, i) ;
        }
        else if(randVal == 1 || randVal == 8)
            copyToPar(1, i) ;
        else if(randVal == 2)
            copyToPar(2, i) ;
        else if(randVal == 3)
            copyToPar(3, i) ;
        else if(randVal == 4)
            copyToPar(4, i) ;
        else if(randVal == 5)
            copyToPar(5, i) ;
    }
}
void crossOver(){
    for(int i=0;i<6;i++){
        int a = par[i].a; //join binary form of 'a' and 'b'
        int b = par[i].b;

        const int bit = 4;
        std::string binaryA = std::bitset<bit>(a).to_string();
        std::string binaryB = std::bitset<bit>(b).to_string();

        bin = binaryA+binaryB;
        binry.push_back(bin);
    }
}
void mutation(){
    string s;
    for(int i=0;i<6;i++){
        s = binry[i];
        point = rand()%8;
        for(int i=0;i<s.length();i++){
            if(s[i]==0){
                s[i]==1;
            }else{
                s[i]==0;
            }
        }
    }
    int value = 0;
    int indexCounter = 0;
    for(int i=s.length()-1;i>=0;i--){

    if(s[i]=='1'){
        value += pow(2, indexCounter);
    }
    indexCounter++;
}


}
int main()
{
   int i, j ;
   for(i = 0 ; i < 6 ; i++){
    int x = rand() % 10 ;
    int y = rand() % 10 ;
    dvalue[i].a = x ;
    dvalue[i].b = y ;
    dvalue[i].fitness = 0 ;
   }

   for(i = 0 ; i < 4 ; i++){
    printf("Iteration: %d\n", i) ;
    for(j = 0 ; j < 6 ; j++){
        if(f(dvalue[j].a , dvalue[j].b) == 0){
            printf("Solution %d %d\n", dvalue[j].a, dvalue[j].b) ;
            return 0;
        }
    calculateFitness() ;
    chooseParent() ;
    crossOver() ;
    mutation() ;
    }
   }

}
