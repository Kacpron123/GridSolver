#include "Puzzledata.h"
#include "json.hpp"
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

Puzzledata::Puzzledata(int number){
   using json = nlohmann::json;
   string name="puzzles/puzzle_"+to_string(number)+".json";
   std::ifstream _file(name);
   if(!file.is_open())
      throw std::runtime_error("Unable to open file: " + name);
   json datafile = json::parse(name);
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
   solution=vector<vector<int>> matrix(width, vector<int>(height, 0));
}
void Puzzledata::Print(){
   int i=1,j=1;
   for(auto &rows:solution){
      i=0;
      for(int &c:rows){
         if(spaces && !(i++%5)) std::cout<<' ';
         if(c==-1) std::cout<<'X';
         else if(c==0) printf("\e[0m\u2588");
         else printf("\e[2m\u2588");
         //cout<<(c==-1 ? '#' : c);
      }
      std::cout<<endl;
      if(spaces && !(j++%5)) std::cout<<endl;
      
   }
}
 
void Puzzledata::Solve(){

}
void Puzzledata::SimpleBoxes(dimension dim,int line){
    int lenght=(dim==col) ? height : width;
    vector<int> temp(length,0);
    vector<vecor<int>> header = (dim==col) ? topHeader[line] : leftHeader[line];
    int i=0;
    string PreviusColor=-2;
    for(auto vec: header){
        fill(temp.begin()+i,temp.begin()+i+vec[lenght]);
         
    }
}