#include <vector>
#include <raylib.h>
#include <string>

class MenuButton {
    public:
        MenuButton(Vector2 leftUpperCorner, Vector2 rightUpperCorner, Vector2 rightUnderCorner, Vector2 leftUnderCorner, char const *newMenuBoxText, int newTextSize);
        void Draw();
        bool CheckCollisionRectangle(Vector2 coordM);
        std::vector<Vector2> menuBox;
        char const *menuBoxText;
        int textSize;
};

MenuButton::MenuButton(Vector2 leftUpperCorner, Vector2 rightUpperCorner, Vector2 rightUnderCorner, Vector2 leftUnderCorner, char const *newMenuBoxText, int newTextSize) {
    menuBoxText = newMenuBoxText;
    textSize = newTextSize;
    menuBox.clear();
    menuBox.push_back(leftUpperCorner);
    menuBox.push_back(rightUpperCorner);
    menuBox.push_back(rightUnderCorner);
    menuBox.push_back(leftUnderCorner);
}

void MenuButton::Draw() {
    for (int i=0; i < menuBox.size(); i++) {
        if (i == menuBox.size()-1) {
            DrawLineV(menuBox.at(i), menuBox.at(0), WHITE);
        } else {
            DrawLineV(menuBox.at(i), menuBox.at(i+1), WHITE);
        }
    }
    DrawText(TextFormat(menuBoxText), (menuBox.at(0).x + menuBox.at(1).x)/2-50, (menuBox.at(0).y+menuBox.at(3).y)/2-10, textSize, WHITE);
}

bool MenuButton::CheckCollisionRectangle(Vector2 coordM) {
    Vector2 AM = {coordM.x-menuBox.at(0).x, coordM.y-menuBox.at(0).y};
    Vector2 AB = {menuBox.at(1).x-menuBox.at(0).x, menuBox.at(1).y-menuBox.at(0).y};
    Vector2 AD = {menuBox.at(3).x-menuBox.at(0).x, menuBox.at(3).y-menuBox.at(0).y};

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