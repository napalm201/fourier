
#include "Vec2.h"
#include <vector>
#define TWO_PI 6.2831853

std::vector<std::pair<Vec2, int>> fourierTranform(const std::vector<Vec2>& points){

   std::vector<std::pair<Vec2, int>> coeffFourier;
   int period = points.size();

   for(int k = 0; k <  period ; k++){

      Vec2 sumVector(0, 0);

      for(int n = 0; n < period; n++)
      {
            const double angle = (TWO_PI * k * n) / (double) period;
            sumVector += points[n].rotate( -angle);
      }
      
      coeffFourier.push_back(std::pair<Vec2, int>(sumVector / period, k));
   }

   return coeffFourier;
}
