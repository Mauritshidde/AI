#include <vector>
#include <raylib.h>
#include <string>

class MenuButton {
    public:
        MenuButton(Vector2 leftUpperCorner, Vector2 rightUpperCorner, Vector2 rightUnderCorner, Vector2 leftUnderCorner, char const *newMenuBoxText, int newTextSize);
        void Draw();
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
