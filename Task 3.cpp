#include<iostream>
#include<string.h>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

float series( vector<float> v1)
{
    float sum=0;
    for(int i=0;i<v1.size();i++)
        sum+=v1[i];
    return sum;
}

float Parallel( vector<float> v1)
{
    float sum=0;
    for(int i=0;i<v1.size();i++)
    {
        if(v1[i]==0) continue;
        sum+=(1/v1[i]);
    }
    return (1/sum);
}

float childval(string x)
{
    int n;
    float val=0;
    string z;
    n=x.length();
    stringstream ss(x);
    vector <float> v1;
    while(ss>>z)
    {
         //if (z=="e") return 0;
         if (z=="S"||z=="s"||z=="P"||z=="p"||z=="e") continue;
         v1.push_back(stof(z));
    }
    if((x[0]=='S'||x[0]=='s')&&x[n-1]=='e') val = series(v1);
    else if((x[0]=='P'||x[0]=='p')&&x[n-1]=='e') val = Parallel(v1);
    return val;
}

string parse(const string x, int& poses, int& pose) {
    size_t founds = x.find("s", poses);
    size_t foundS = x.find("S", poses);
    size_t foundP = x.find("P", poses);
    size_t foundp = x.find("p", poses);
    size_t founde = x.find("e", pose);
    string output;

    if (founds != string::npos) {
        poses = founds;
        pose=founde;
        output = x.substr(poses, pose - poses + 1);
    } else if (foundS != string::npos) {
        poses = foundS;
        pose=founde;
        output = x.substr(poses, pose - poses + 1);
    } else if (foundP != string::npos) {
        poses = foundP;
        pose=founde;
        output = x.substr(poses, pose - poses + 1);
    } else if (foundp != string::npos) {
        poses = foundp;
        pose=founde;
        output = x.substr(poses, pose - poses + 1);
    }
    return output;
}

int main()
{
    int n,i;
    string x;
    getline(cin,x);
    n=x.length();
    vector<float> parentval;
    if ((x[0]=='S'||x[0]=='s'||x[0]=='P'||x[0]=='p') && x[n-1]=='e')
    {
        int poses=1, pose=1;
        bool childflag=0, parentflag = 1;
        string z;
        stringstream ss(x);
        while(ss>>z)
        {
            if(!((z[0]>=65 && z[0]<=90) || (z[0]>=97 && z[0]<=122))&&!childflag)
            {
               parentval.push_back(stof(z));
            }

            else if((z[0]=='S'||z[0]=='s'||z[0]=='P'||z[0]=='p')&&!parentflag)
            {
                parentval.push_back(childval(parse(x, poses, pose)));
                poses++; pose++;
                childflag=1;
            }
            else if(z[0]=='e')
            {
                childflag = 0;
            }
            else if(!childflag&&!parentflag)
            {
                cout<<"Wrong Description";
                return 0;
            }
            if(parentflag) parentflag=0;
        }
    }
    else
    {
        cout<<"Wrong Description";
        return 0;
    }
    if((x[0]=='S'||x[0]=='s')&&parentval.size()>=1)
        cout<< "The total resistance = "<<series(parentval);
    else if((x[0]=='P'||x[0]=='p')&&parentval.size()>=2)
        cout<< "The total resistance = "<<Parallel(parentval);
    else
        cout<< "Incorrect Input";
}
