#include <vector>
#include <raylib.h>
#include <string>

class DrawButton {
    public:
        DrawButton(std::vector<Vector2> newCorners, char const newMenuBoxText[], int newTextSize);
        bool checkCollisionButton(Vector2 coordM);
        void Draw();
        std::vector<Vector2> corners;
        char const *menuBoxText;
        int textSize;

};

DrawButton::DrawButton(std::vector<Vector2> newCorners, char const newMenuBoxText[], int newTextSize) {
    corners = newCorners;
    menuBoxText = newMenuBoxText;
    textSize = newTextSize;
}

bool DrawButton::checkCollisionButton(Vector2 coordM) {
    Vector2 AM = {coordM.x-corners.at(0).x, coordM.y-corners.at(0).y};
    Vector2 AB = {corners.at(1).x-corners.at(0).x, corners.at(1).y-corners.at(0).y};
    Vector2 AD = {corners.at(3).x-corners.at(0).x, corners.at(3).y-corners.at(0).y};

    double AMAB  = AM.x * AB.x + AM.y * AB.y;           // AM * AB
    double ABAB  = AB.x * AB.x + AB.y * AB.y;           // AB * AB
    double AMAD  = AM.x * AD.x + AM.y * AD.y;           // AM * AD
    double ADAD  = AD.x * AD.x + AD.y * AD.y;           // AD * AD

    if (0 < AMAB && AMAB < ABAB) {
        if (0 < AMAD && AMAD < ADAD) {
            return true;
        }
    }
    return false;
}

void DrawButton::Draw() {
    for (int i=0; i < corners.size(); i++) {
        if (i == corners.size()-1) {
            DrawLineV(corners.at(i), corners.at(0), WHITE);
        } else {
            DrawLineV(corners.at(i), corners.at(i+1), WHITE);
        }
    }
    DrawText(TextFormat(menuBoxText), corners.at(0).x + textSize, (corners.at(0).y+corners.at(3).y)/2-textSize, textSize, WHITE);
}

class DrawMenu {
    public:
        DrawMenu(std::vector<Vector2> newMenuCorners = {{0,0}});
        void addButton(std::vector<Vector2> newCorners, char const newMenuBoxText[], int newTextSize);
        void Draw();

        std::vector<DrawButton> buttons;
        std::vector<Vector2> menuCorners;
};

DrawMenu::DrawMenu(std::vector<Vector2> newMenuCorners) {
    menuCorners =  newMenuCorners;
}

void DrawMenu::addButton(std::vector<Vector2> corners, char const boxText[], int textSize) {
    DrawButton newButton = DrawButton(corners, boxText, textSize);
    buttons.push_back(newButton);
}

void DrawMenu::Draw() {
    for (int i=0; i < menuCorners.size(); i++) {
        if (i == menuCorners.size()-1) {
            DrawLineV(menuCorners.at(i), menuCorners.at(0), WHITE);
        } else {
            DrawLineV(menuCorners.at(i), menuCorners.at(i+1), WHITE);
        }
    }
    for (int i=0; i < buttons.size(); i++) {
        buttons.at(i).Draw();
    }
}