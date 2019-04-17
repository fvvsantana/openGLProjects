#include <iostream>


#include <graphicslib.hpp>
#include <utils.hpp>
#include <tester.hpp>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define ROWS 2
#define COLS 2

int main(int argc, char const *argv[]) {
    graphicslib::Window window(WINDOW_WIDTH, WINDOW_HEIGHT);
    window.createWindow();
    window.run();

    return 0;
}
