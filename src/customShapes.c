#include "customShapes.h"

void DrawRoundedRectangle(int x, int y, int width, int height, int radius, Color color)
{
    // Draw the center of the rectangle (excluding corners)
    DrawRectangle(x + radius, y, width - 2 * radius, height, color);                   // Top side
    DrawRectangle(x + radius, y + height - radius, width - 2 * radius, radius, color); // Bottom side
    DrawRectangle(x, y + radius, radius, height - 2 * radius, color);                  // Left side
    DrawRectangle(x + width - radius, y + radius, radius, height - 2 * radius, color); // Right side

    // Draw the four corners
    DrawCircle(x + radius, y + radius, radius, color);                  // Top-left corner
    DrawCircle(x + width - radius, y + radius, radius, color);          // Top-right corner
    DrawCircle(x + radius, y + height - radius, radius, color);         // Bottom-left corner
    DrawCircle(x + width - radius, y + height - radius, radius, color); // Bottom-right corner
}