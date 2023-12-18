#include<iostream>
#include<vector>
using namespace std;

void remove_lr(int x,vector<string> &productions){
    int m=productions[x].size();
    vector<string> alpha,beta;
    for(int j=0;j<m;j++){
        if(productions[x][j]=='>' || productions[x][j]=='|'){
            j++;
            if(productions[x][j]==productions[x][0]){
                int k=j+1;
                while(productions[x][k]!='|' && k<m){
                    k++;
                }
                if(k-j-1>0){
                    alpha.push_back(productions[x].substr(j+1,k-j-1));
                }
            }
            else{
                int k=j;
                while(productions[x][k]!='|' && k<m){
                    k++;
                }
                if(k-j>0){
                    beta.push_back(productions[x].substr(j,k-j));
                }
            }
        }
    }
    if(alpha.size()>0){
        string s1;
        s1=productions[x][0];
        s1+="'->";
        int n=alpha.size();
        for(int i=0;i<n;i++){
            s1.append(alpha[i]);
            s1+=productions[x][0];
            s1+="'|";
        }
        s1+="^";

        string s2=productions[x].substr(0,3);
        n=beta.size();
        for(int i=0;i<n;i++){
            s2.append(beta[i]);
            s2+=productions[x][0];
            s2+="'";
            if(i!=n-1){
                s2+="|";
            }
        }
        //productions.insert(productions.begin()+x+1,s2);
        //productions.insert(productions.begin()+x+1,s1);
        if(n>0){
            productions.push_back(s2);
        }
        productions.push_back(s1);
        productions.erase(productions.begin()+x);
    }
}

int main(){
    vector<string> productions;
    string s;
    cout<<"Enter the grammar (use ^ as null character)\nType 'end' to stop entering productions\n\n";
    while(true){
        cin>>s;
        if(s=="end"){
            break;
        }
        if(s[0]<'A' || s[0]>'Z' || s[1]!='-' || s[2]!='>'){
            cout<<"Invalid grammar";
            return 0;
        }
        productions.push_back(s);
    }
    int n=productions.size();
    for(int i=n-1;i>-1;i--){
        remove_lr(i,productions);
    }
    cout<<"\nGrammar after removing left recursion:\n";
    n=productions.size();
    for(int i=0;i<n;i++){
        int m=productions[i].size();
        for(int j=0;j<m;j++){
            cout<<productions[i][j];
        }
        cout<<"\n";
    }
    return 0;
}
