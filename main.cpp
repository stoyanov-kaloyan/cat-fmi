#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "./draw/sdlwrapper.h"

struct LineSegment
{
    int x1, y1, x2, y2;
};

std::vector<LineSegment> readLineSegments(const std::string &filePath)
{
    std::ifstream file(filePath);
    std::vector<LineSegment> lineSegments;

    std::string line;
    bool firstLine = true;

    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        std::stringstream ss(line);
        std::string x1, y1, x2, y2;

        std::getline(ss, x1, ',');
        std::getline(ss, y1, ',');
        std::getline(ss, x2, ',');
        std::getline(ss, y2, ',');

        LineSegment segment = {std::stoi(x1), std::stoi(y1), std::stoi(x2), std::stoi(y2)};
        lineSegments.push_back(segment);
    }

    return lineSegments;
}

void drawLineSegments(const std::vector<LineSegment> &lineSegments)
{
    const int translate_x = 200;

    for (const auto &segment : lineSegments)
    {
        sdlw::drawLine(segment.x1 + translate_x, segment.y1, segment.x2 + translate_x, segment.y2);
    }
}

int main()
{
    sdlw::setColor(255, 255, 255);

    std::vector<LineSegment> lineSegments = readLineSegments("line_segments.csv");

    drawLineSegments(lineSegments);

    sdlw::updateGraphics();

    std::cin.get();

    return 0;
}
