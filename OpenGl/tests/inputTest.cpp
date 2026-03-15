#include <GL/glut.h> // Includes glu.h and gl.h
#include <iostream>
#include <map>
#include <vector>

struct point{
    GLfloat x, y;
    point(GLfloat x, GLfloat y){
        this->x= x; this-> y= y;
    }
};
struct coord{
    GLfloat x, y, z;
    coord(GLfloat x, GLfloat y, GLfloat z){
        this->x= x; this-> y= y; this->z= z;
    }
};
struct color{
    GLfloat r, g, b;
    color(GLint r, GLint g, GLint b){
        this->r= r/255.0; this-> g= g/ 255.0; this->b= b/255.0;
    }
};
const std::map<std::string, std::vector<GLfloat>> colors= {
    {"black",   {0.0, 0.0, 0.0}},
    {"white",   {1.0, 1.0, 1.0}},
    {"red",     {1.0, 0.0, 0.0}},
    {"green",   {0.0, 1.0, 0.0}},
    {"blue",    {0.0, 0.0, 1.0}},
    {"yellow",  {1.0, 1.0, 0.0}},
    {"cyan",    {0.0, 1.0, 1.0}},
    {"magenta", {1.0, 0.0, 1.0}},
    {"orange",  {1.0, 0.5, 0.0}},
    {"lime",    {0.5, 1.0, 0.0}},
    {"purple",  {0.5, 0.0, 1.0}},
};
const std::map<int, std::string> keys= {
    {0, "leftClick"     },
    {1, "middleClick"   },
    {2, "rightClick"    },
    {3, "scrollUp"      },
    {4, "scrollDown"    },
};

void rgbTrig(std::vector<point> verts, std::string c1, std::string c2, std::string c3){
    glBegin(GL_TRIANGLES);

    glColor3fv(colors.at(c1).data());
    glVertex2f(verts[0].x,  verts[0].y);
    glColor3fv(colors.at(c2).data());
    glVertex2f(verts[1].x,  verts[1].y);
    glColor3fv(colors.at(c3).data());
    glVertex2f(verts[2].x,  verts[2].y);

    glEnd();
}

void drawPoint(point org, std::string c1){
    glBegin(GL_POINTS);

    glColor3fv(colors.at(c1).data());
    glVertex2f(org.x,  org.y);

    glEnd();
}
std::vector<point> verts={
    {-0.8, -0.8},
    { 0.8, -0.8},
    { 0.0,  0.9},
};

// Function to draw the scene
void display() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    rgbTrig(verts, "red", "green", "blue");

    glFlush();
}

void handleKeyboard(unsigned char key, int mouseX, int mouseY){
    std::cout << "key= " << key << " ,mouseX= " << mouseX << " ,mouseY= " << mouseY << std::endl;
}
void handleMouse(int clickType, int isClicked, int mouseX, int mouseY){
    std::cout << "clickType= " << keys.at(clickType);
    std::cout << " ,isHeld= " << isClicked;
    std::cout << " ,MouseX= " << mouseX;
    std::cout << " ,mouseY= " << mouseY << std::endl;
    drawPoint({(GLfloat) mouseX, (GLfloat) mouseY}, "white");
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);                    // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Use single color buffer and RGB color mode
    glutInitWindowSize(500, 500);             // Set the window size
    glutInitWindowPosition(100, 100);         // Set the window position
    glutCreateWindow("GL RGB Triangle");      // Create window with a title
    glutDisplayFunc(display);                 // Register the display function
    glutKeyboardFunc(handleKeyboard);         // Handle keyboard input
    glutMouseFunc(handleMouse);               // Handle mouse input
    glutMainLoop();                           // Enter the event-processing loop

    return 0;
}
