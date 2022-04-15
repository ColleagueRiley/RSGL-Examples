#include <RSGL/RSGL.hpp> // RSGL for gui
#include "../include/platform.hpp"

RSGL::window win("win",{500,500,500,500},{255,255,255});

bool running = true;


int player; int jump=0;
void eventLoop(int event){
    switch (event){
        case RSGL::quit: running=false; break;
        case RSGL::KeyPressed: 
            if (win.event.key == "Right") map.at(player).cir.x+=10;
            if (win.event.key == "Left") map.at(player).cir.x-=10;
            if (win.event.key == "space"){ if(jump < 2){ map.at(player).cir.y-=50; jump++;}}
        default: break;
    } if (jump && map.at(player).grounded) jump=0; 
}

int main(){
    player = addToMap({OBJECT,circle,{255,0,255},{200,20,20}});
    addToMap({PLATFORM,rect,{0,0,0},.r={200,400,20,20}});
    while (running){
        win.checkEvents();
        eventLoop(win.event.type);
        for (int i=0; i < map.size(); i++) map.at(i).draw();
        checkGrav();
        win.clear();
    }
}
