#include <iostream>
#include <cmath>      // For abs(), round(), and sqrt() functions
#include <graphics.h> // For graphics functions
#include <conio.h>    // For getch()
#include <string>     // For color names

using namespace std;

// DDA line drawing function
void dda(int x0, int y0, int x1, int y1, int color)
{
    int dx = x1 - x0; // Change in x
    int dy = y1 - y0; // Change in y
    int steps = max(abs(dx), abs(dy)); // Max of dx and dy determines steps

    float xIncrement = static_cast<float>(dx) / steps; // Increment in x
    float yIncrement = static_cast<float>(dy) / steps; // Increment in y

    float x = x0;
    float y = y0;

    // Draw the line pixel by pixel
    for (int i = 0; i <= steps; i++)
    {
        putpixel(round(x), round(y), color); // Plot the pixel at (x, y) with the given color
        x += xIncrement; // Update x for the next step
        y += yIncrement; // Update y for the next step
    }
}

// Function to initialize graphics mode and handle errors
bool initializeGraphics()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    if (graphresult() != grOk)
    {
        cout << "Error: Graphics initialization failed!" << endl;
        return false;
    }
    return true;
}

// Function to get color input with validation
int getColorInput()
{
    int color;
    do
    {
        cout << "Enter the color code (0-15) for the line: ";
        cin >> color;
        if (color < 0 || color > 15)
        {
            cout << "Invalid color code! Please enter a value between 0 and 15." << endl;
        }
    } while (color < 0 || color > 15);

    return color;
}

// Function to draw coordinate axes
void drawAxes(int width, int height)
{
    // Draw X-axis
    dda(0, height / 2, width, height / 2, WHITE);
    // Draw Y-axis
    dda(width / 2, 0, width / 2, height, WHITE);

    // Label the axes
    setcolor(WHITE);
    outtextxy(width - 10, height / 2 + 5, "X");
    outtextxy(width / 2 + 5, 10, "Y");
}

// Function to calculate and return the length of the line
double calculateLineLength(int x0, int y0, int x1, int y1)
{
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

int main()
{
    // Initialize graphics mode
    if (!initializeGraphics())
    {
        return 1;
    }

    // Get screen dimensions
    int width = getmaxx();
    int height = getmaxy();

    // Draw coordinate axes
    drawAxes(width, height);

    char choice;
    do
    {
        // Get user input for line coordinates
        int x0, y0, x1, y1;
        cout << "Enter the starting coordinates (x0, y0): ";
        cin >> x0 >> y0;
        cout << "Enter the ending coordinates (x1, y1): ";
        cin >> x1 >> y1;

        // Get color input
        int color = getColorInput();

        // Draw the line using DDA algorithm
        dda(x0, y0, x1, y1, color);

        // Calculate and display the length of the line
        double length = calculateLineLength(x0, y0, x1, y1);
        cout << "Length of the line: " << length << endl;

        // Ask user if they want to draw another line
        cout << "Do you want to draw another line? (y/n): ";
        cin >> choice;

        if (choice == 'c' || choice == 'C')
        {
            cleardevice();
            drawAxes(width, height);
            choice = 'y'; // Continue the loop
        }

    } while (choice == 'y' || choice == 'Y' || choice == 'c' || choice == 'C');

    // Wait for key press before closing the graphics window
    cout << "Press any key to exit..." << endl;
    getch();
    closegraph();

    return 0;
}
