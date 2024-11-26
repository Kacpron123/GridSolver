#ifndef PUZZLEDATA_H
#define PUZZLEDATA_H

#include <vector>
#include <string>



enum dimension{row,col};
enum typ{color,range};

class Puzzledata{
      bool spaces=false;
      /// @brief lenght of puzzle
      int width;
      /// @brief lenght of puzzle
      int height;
      /// @brief list of color in hex
      std::vector<std::string> colors;
      /// @brief top  header of cells with[y][x][color,length]
      std::vector<std::vector<std::vector<int>>> topHeader;
      /// @brief side header of cells with[y][x][color,length]
      std::vector<std::vector<std::vector<int>>> leftHeader;
      /// @brief final solution
      std::vector<std::vector<int>> solution;
   public:
      /// @brief constructor create puzzle from json file 
      /// @param number id of puzzle
      Puzzledata(int number);
      /// @brief print solution
      /// @param spaces make spaces every 5 cell
      void Print(bool spaces=false);
      /// @brief solve puzzle
      void Solve();
      /// @brief simpleboxes technique
      /// @param dim header
      /// @param line in header
      void SimpleBoxes(dimension dim, int line);
};
#endif
