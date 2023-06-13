

class DecorateLines{

  public: 

    DecorateLines(std::vector<Vec2> points):points(points){}
    
    std::vector<Vec2> extendLinePoints(){
    	
    	std::vector<Vec2> correctlyPoints;
   
        int size = points.size() - 1;

        for(int n = 0; n < size; n++){

            Vec2 firstVector = points[n];
            Vec2 secondVector = points[n+1];
            double maxLen = (secondVector - firstVector).length();
            Vec2 deltaNormalizeVector = (secondVector - firstVector).normalize();        
       
            for(double l = 0; l < maxLen; l += 0.5){
               correctlyPoints.push_back(firstVector + deltaNormalizeVector * l);
            }
         }
         
         points = correctlyPoints;
         return points;
    }

  private:
  	std::vector<Vec2> points;
};