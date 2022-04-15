#include <RSGL/RSGL.hpp>
#include <pthread.h>

bool running = true;
RSGL::window win("RSGL Gun",{500,500,500,500},{0,0,0});

struct gun{
    int x, y; bool Shoot=false;
    int a, s,i, x2=x, y2=y; int d;
    void shoot(int ammo, int speed, int dir=1); 
    void loop();
}; 

void gun::shoot(int ammo, int speed, int dir){Shoot=true; a=ammo; s=speed; i=0;d=dir;}

void gun::loop(){
    if (Shoot){
        RSGL::rect r;
        if (d == 1 || d == 3) r= {x2,y2,20,10};
        if (d == 2 || d == 4) r= {x2,y2,10,20};
        RSGL::drawRect(r,{255,255,255});
        RSGL::drawRect(r,{255,255,255});
        
        if (i == a){ Shoot =false; i=0;}
        if (d == 1 && x2 >= win.r.width-20
         || d == 2 && y2 <= 20
         || d ==3 && x2 <= 20
         || d == 4 && y2 >= win.r.width-20){ 
            i++; x2=x; y2=y;
        }
        else{
            if (d==1) x2+=s;
            if (d==2) y2-=s;
            if (d==3) x2-=s;
            if (d==4) y2+=s;
        }
    }
}


gun g = {215,180};
int d=1;
int main(){
    while(running){
        win.checkEvents();
        if (win.event.type == RSGL::KeyPressed){
            if (win.event.key == "Left"){ d=3; g.x-=5;}
            if (win.event.key == "Right"){ d=1; g.x+=5;}
            if (win.event.key == "Down") d=4;
            if (win.event.key == "Up") d=2;
        }
        if (win.isPressed("Control_L")) g.shoot(1,20,d);
        g.loop();
        RSGL::drawCircle({g.x+5,g.y+5,30},{255,0,0});
        win.clear();
    }
} 