#include <bits/stdc++.h>
using namespace std;

vector<int>aa;
vector<int>bb;
vector<int>y_true;
vector<double>y_pred;

void sigmoid()
{
    for(int i=0;i<4;i++){
        double d = y_pred[i];
        double sig = (1/(pow(1+exp(-1*d),2)))*1.00;
        y_pred.push_back(sig);
        cout<<sig<<" ";
    }
    for(int i=0;i<4;i++){
        cout<<aa[i]<<" "<<bb[i]<<" "<<y_true[i]<<" "<<y_pred[i]<<endl;
    }
}


int main()
{
    int a,b,x;
    double y, loss, w1=0.1, w2=0.5, bias=1;
    for(int i=0;i<4;i++){
        cin>>a>>b;
        aa.push_back(a);
        bb.push_back(b);

        x = a^b;
        y_true.push_back(x);
    }

    for(int i=0;i<4;i++){
        y = aa[i]*w1 + bb[i]*w2 + b;
        y_pred.push_back(y);
        //cout<<aa[i]<<" "<<bb[i]<<" "<<y_true[i]<<" "<<y*1.00<<endl;
    }
    sigmoid();
}
