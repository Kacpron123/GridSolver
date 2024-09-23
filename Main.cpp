/*
GridSolver Kacpron
from griddlers.net site
using wikipedia methods:
https://en.wikipedia.org/wiki/Nonogram#Simple_spaces
*/

#include "json.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
using namespace std;

//using json = nlohmann::json;
//std::ifstream file("./puzzle.json");
//json puzzle = json::parse(file);

enum dimension{row,col};

class puzzledata{
    //for now puzzle id=73863
    bool spaces=false;
    int width;
    int height;
    vector<string> colors;
    vector<vector<vector<int>>> topHeader;
    vector<vector<vector<int>>> leftHeader;
    vector<vector<int>> solution;
    queue <pair<int,int>> last;
    public:
    puzzledata(){
        using json = nlohmann::json;
        //for now testing on puzzle 73863
        std::ifstream file("./puzzle_73863.json");
        json datafile = json::parse(file);
        
        width=datafile["width"];
        height=datafile["height"];
        for(auto string: datafile["originalColors"])
            colors.push_back(string);
        
        for(auto header:datafile["topHeader"]){
            vector<vector<int>> innervec;
            for(auto vec: header){
                innervec.push_back({(int)vec[0],(int)vec[1]});
            }
            topHeader.push_back(innervec);
        }
        for(auto header:datafile["leftHeader"]){
            vector<vector<int>> innervec;
            for(auto vec: header){
                innervec.push_back({(int)vec[0],(int)vec[1]});
            }
            leftHeader.push_back(innervec);
        }
        for(int i=0;i<height;i++)
            solution.push_back(vector<int> (width,0));
    }
    void print(){
        int i=1,j=1;
        for(auto &rows:solution){
            i=0;
            for(int &c:rows){
                if(spaces && !(i++%5)) cout<<' ';
                if(c==-1) cout<<'X';
                else if(c==0) printf("\e[0m0");
                else printf("\e[31m%d",c);
                //cout<<(c==-1 ? '#' : c);
            }
            cout<<endl;
            if(spaces && !(j++%5)) cout<<endl;
            
        }
    }
    
    void simpleboxes(dimension dim,int line){
            int length;
            vector<vector<int>> header;
            if(dim==row){
                length=width;
                header=leftHeader[line];
            }
            else{
                length=height;
                header=topHeader[line];
            }
            int temp[length];
            fill(temp,temp+length,0);
            int j=0;int prevcolor=-1;
            int start=0;
            //fill temp
            for(auto &sets: header){
                start+=(sets[0]==prevcolor);
                fill(temp+start,temp+sets[1]+start,sets[0]);
                start+=sets[1];
                prevcolor=sets[0];
            }
            int gap=length-start;
            int gap2=gap;prevcolor=-1;
            //remove left/top notoverlap
            for(int i=0;i<length;i++){
                if(temp[i]!=prevcolor){
                    prevcolor=temp[i];
                    gap2=gap;
                }
                if(gap2){
                    temp[i]=0;
                    gap2--;
                }
                else{
                    gap2=gap;
                    while(temp[i]==prevcolor)
                        i++;
                }
            }
        if(dim==row){
            for(int i=0;i<length;i++)
                if(temp[i]!=0)
                solution[line][i]=temp[i];
        }
        else{
            for(int i=0;i<length;i++)
                if(temp[i]!=0)
                solution[i][line]=temp[i];
        }
    }
    void glue(dimension dim,int line){
        int length;
        if(dim==row){
            length=width;
            int temp[length];
            for(int i=0;i<length;i++)
                temp[i]=solution[line][i];
        }else{
            length=height;
            int temp[length];
            for(int i=0;i<length;i++)
                temp[i]=solution[i][line];
        }

    }
    void joinandsplit(dimension dim,int line){
    }
    void simplespaces(dimension dim,int line){

    }
    void forcing(dimension dim,int line){

    }
    void mercury(dimension dim,int line){

    }
    void contradictions(){

    }

    void solve(){
        for(int i=0;i<height;i++)
            simpleboxes(row,i);
        for(int i=0;i<width;i++)
            simpleboxes(col,i);
        print();
    }
};
/*



*/
int main(){
    puzzledata puzzle;
    puzzle.solve();
    //puzzle.print();
    cout<<endl;
    return 0;
}
