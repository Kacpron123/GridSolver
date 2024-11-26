#include "Puzzledata.h"
#include "json.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Puzzledata::Puzzledata(int number){
   using json = nlohmann::json;
   string name="./puzzles/puzzle_"+to_string(number)+".json";
   ifstream file(name);
   cout<<name<<endl;
   if(!file.is_open())
      throw std::runtime_error("Unable to open file: " + name);
   json datafile = json::parse(file);
   width=datafile["width"];
   height=datafile["height"];

   for(auto string: datafile["originalColors"])
      colors.push_back(string);   
   for(auto topheader:datafile["topHeader"]){
      vector<vector<int>> innervec;
      for(auto vec: topheader){
            innervec.push_back({(int)vec[0],(int)vec[1]});
      }
      topHeader.push_back(innervec);
   }
   for(auto leftheader:datafile["leftHeader"]){
      vector<vector<int>> innervec;
      for(auto vec: leftheader){
            innervec.push_back({(int)vec[0],(int)vec[1]});
      }
      leftHeader.push_back(innervec);
   }
   solution=vector<vector<int>> (height, vector<int>(width, 0));
}
void Puzzledata::Print(bool spaces){
   int i,j=0; //for spaces
   for(auto &rows:solution){
      i=0;
      for(int &c:rows){
         cout<<c;
         if(spaces && !((i+=spaces)%5)) std::cout<<' ';
         // if(c==-1) std::cout<<'X';
         // else if(c==0) printf("\e[0m\u2588");
         // else printf("\e[2m\u2588");
         //cout<<(c==-1 ? '#' : c);
      }
      std::cout<<endl;
      if(spaces && !((j+=spaces)%5)) std::cout<<endl;
      
   }
}
void Puzzledata::SimpleBoxes(dimension dim,int line){
   int lenght=(dim==col) ? height : width;
   vector<int> temp(lenght,0);
   vector<vector<int>> header = (dim==col) ? topHeader[line] : leftHeader[line];
   
   int start=0,PreviousColor=-2;
   for(auto &vec: header){
      fill(temp.begin()+start,temp.begin()+start+vec[lenght],vec[color]);
      start+=(PreviousColor==vec[color])+vec[lenght]-1;
      PreviousColor=vec[color];
   }
   int i=0;
   for(int &color : temp){
      if(dim==col) solution[i][line]=color;
      else solution[line][i]=color;
      i++;
   }
}
void Puzzledata::Solve(){
   for(int i=0;i<height;i++)
      SimpleBoxes(row,i);
   for(int i=0;i<width;i++)
      SimpleBoxes(col,i);
}