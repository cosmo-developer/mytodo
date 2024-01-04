#include "TodoMainWindow.hpp"
#include <iostream>
void TodoMainWindow::max400Processor(int width){
    std::cout<<"Window size decrease from threshold"<<std::endl;
    sideMenuContainer->set_size_request(0);
    drawerOpener->set_visible(true);
    drawerCloser->set_visible(false);
}