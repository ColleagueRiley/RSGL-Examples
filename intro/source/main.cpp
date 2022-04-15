#include <RSGL/RSGL.hpp>
RSGL::window win("RSGL Uno",{500,500,500,500},{255,0,0});
bool running=true;


void splashScreen(std::string file="res/logo.png",std::string font="res/SansPosterBold.ttf",int t=100,RSGL::window d=RSGL::root){
    bool running=true;
    RSGL::color c = d.color; if (t < 100) t=100;
    int cl=0;
    while (running){
        win.checkEvents();  win.setColor({0,0,0}); cl++;
        if (cl==t) running=false;
        switch(win.event.type){
            case RSGL::quit: running=false; win.close(); break;
            default: break;
        }
        RSGL::drawImage(file,{win.r.width/6,win.r.length/6,win.r.width/1.5,win.r.length/1.5});
        RSGL::drawText("Powered With",{win.r.width/6,win.r.length/9,win.r.width/20},font.data(),{255,0,0});
        win.clear();
    } win.setColor(c);
}


int main(){
    splashScreen("res/logo.png");
    while (running){
        win.checkEvents(); 
        switch(win.event.type){
            case RSGL::quit: running=false;
            default: break;
        }

        win.clear();
    }   win.close();
}