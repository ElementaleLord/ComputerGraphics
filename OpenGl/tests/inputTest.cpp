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
const std::map<std::string, color> colors= {
    {"black",   {  0,   0,   0}},
    {"white",   {255, 255, 255}},
    {"red",     {255,   0,   0}},
    {"green",   {  0, 255,   0}},
    {"blue",    {  0,   0, 255}},
    {"yellow",  {255, 255,   0}},
    {"cyan",    {  0, 255, 255}},
    {"magenta", {255,   0, 255}},
    {"orange",  {255, 128,   0}},
    {"lime",    {128, 255,   0}},
    {"purple",  {128,   0, 255}},
};
const std::map<int, std::string> mouseKeys= {
    {0, "leftClick"     },
    {1, "middleClick"   },
    {2, "rightClick"    },
    {3, "scrollUp"      },
    {4, "scrollDown"    },
};
const std::map<int, std::string> modKeys= {
    {0, "none"              },
    {1, "shift"             },
    {2, "ctrl"              },
    {3, "shift+ ctrl"       },
    {4, "alt"               },
    {5, "alt+ shift"        },
    {6, "alt+ ctrl"         },
    {7, "alt+ ctrl+ shift"  },
};

void rgbTrig(std::vector<point> verts, std::string c1, std::string c2, std::string c3){
    glBegin(GL_TRIANGLES);

    glColor3f(colors.at(c1).r, colors.at(c1). g, colors.at(c1). b);
    glVertex2f(verts[0].x,  verts[0].y);
    glColor3f(colors.at(c2).r, colors.at(c2). g, colors.at(c2). b);
    glVertex2f(verts[1].x,  verts[1].y);
    glColor3f(colors.at(c3).r, colors.at(c3). g, colors.at(c3). b);
    glVertex2f(verts[2].x,  verts[2].y);

    glEnd();
}

void drawPoint(point org, std::string c1){
    glBegin(GL_POINTS);

    glColor3f(colors.at(c1).r, colors.at(c1). g, colors.at(c1). b);
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
    std::cout << "Key= " << key << std::endl;
    std::cout << "MouseX= " << mouseX << std::endl;
    std::cout << "MouseY= " << mouseY << std::endl;
    std::cout << "Modifier= " << modKeys.at(glutGetModifiers()) << std::endl;
    std::cout << std::endl;
}
void handleMouse(int clickType, int isClicked, int mouseX, int mouseY){
    std::cout << "ClickType= " << mouseKeys.at(clickType) << std::endl;
    std::cout << "IsClicked= " << isClicked << std::endl;
    std::cout << "MouseX= " << mouseX << std::endl;
    std::cout << "MouseY= " << mouseY << std::endl;
    std::cout << "Modifier= " << modKeys.at(glutGetModifiers()) << std::endl;
    std::cout << std::endl;
    
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
