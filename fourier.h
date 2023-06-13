#include <GLFW/glfw3.h>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <glm/glm.hpp>
#include "Vec2.h"
#include "fouriertransform.h"
#include "PrimitiveFigure.h"

#define TWO_PI 6.2831853

namespace MyApp{
   
GLFWwindow* myWindow;
static double width = 1200;
static double height = 800;

enum MouseState{
      PRESS,
      RELEASE
};

MouseState mouseState = RELEASE;
double updateangle = 0; 

std::vector<Vec2> pointsImage;
std::vector<std::pair<Vec2, int>> coefficientFourier;
std::vector<Vec2> line;

void loop();

void drawFourier();

void mouseEvent(GLFWwindow* window, int button, int action, int mode);
void fillPoints();

void loop(){

   glfwInit();
   myWindow = glfwCreateWindow(width, height, "Fourier", nullptr, nullptr);
   glfwMakeContextCurrent(myWindow);

   glOrtho(0, width, height, 0, -1,1);
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   glfwSwapBuffers(myWindow);

   glfwSetMouseButtonCallback(myWindow, mouseEvent);

   while (!glfwWindowShouldClose(myWindow)){

         if (mouseState == PRESS){
            fillPoints(); 
         }

         if (mouseState == RELEASE){
            drawFourier();
         } 

         glfwPollEvents();
   }

   glfwTerminate();

}

void fillPoints(){

   double mouseX, mouseY;
   glfwGetCursorPos(myWindow, &mouseX, &mouseY);

   Vec2 point(mouseX, mouseY);
   
   if (!pointsImage.empty() && pointsImage.back() == point)
      return;
   
   pointsImage.push_back(point);

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
   PrimitiveFigure::curveLines(pointsImage);
   glfwSwapBuffers(myWindow);
}


void mouseEvent(GLFWwindow* window, int button, int action, int mode){

   if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
      mouseState = PRESS;
      line.clear();
      pointsImage.clear();
      updateangle = 0;
   }

   if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){

      coefficientFourier = fourierTranform(pointsImage);
     
      sort(coefficientFourier.begin(), coefficientFourier.end(), [](const std::pair<Vec2, int>& vec1, const std::pair<Vec2, int>& vec2){
        return vec1.first.length() > vec2.first.length(); 
      });

      mouseState = RELEASE;
   }
}

void drawFourier()
{   

   if(coefficientFourier.size() < 2)
      return;
   
   using namespace PrimitiveFigure;

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClear(GL_COLOR_BUFFER_BIT);
      
   Vec2 vec1(0, 0);  

   for(std::pair<Vec2, int> member : coefficientFourier)
   {
      Vec2 vec2 = member.first.rotate(member.second * updateangle);
      drawCircle(vec2.length(), vec1.x, vec1.y);
      drawLine(vec1.x, vec2.x + vec1.x, vec1.y, vec1.y + vec2.y);
      vec1 += vec2;
      
   }
   
   line.push_back(vec1);

   curveLines(line);

   updateangle += TWO_PI / coefficientFourier.size();;

   if(updateangle > TWO_PI){
      updateangle = 0; 
      line.clear();
   }
     
   glfwSwapBuffers(myWindow);

}

};

