#include <RSGL/RSGL.hpp>
#include <pthread.h>

bool running = true;
RSGL::window win("name",{500,500,500,500},{250,250,250});

struct Player{
    int x,y,size,pos;
    RSGL::color c,c2;
    int y2=-500;
    bool jumping=false,fall=false;
    void draw();
};  

std::vector<int> cords{5,15,30,35};

int bx =500;
void Player::draw(){
    if (y2==-500) y2=y; if (pos == 5) pos=1; 
    else if (y2 != y){  jumping=true; 
        if (y2==y+100 && !RSGL::RectCollideRect({bx,y2,50,50},{x,y,size,size})){pos+=1; fall=true;}
        if (fall){ 
            if (!RSGL::RectCollideRect({bx,y2,50,50},{x,y,size,size}))  y+=4;
            
        }
        if (!fall) y-=4;
        if ( y+40 == y2 && fall) pos+=1;
    }
    else {jumping = false; fall=false;}
    RSGL::drawRect({x,y,size,size},c); RSGL::drawRect({x,y,size,size},{0,0,0},false);
    switch (pos){
        case 1:
            RSGL::drawRect({x+5,y+15,size-40,size-40},c2);
            RSGL::drawRect({x+30,y+15,size-40,size-40},c2);
            RSGL::drawRect({x+5,y+35,size-15,size-40},c2); 

            RSGL::drawRect({x+5,y+15,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+30,y+15,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+5,y+35,size-15,size-40},{0,0,0},false); break;
        case 2:
            RSGL::drawRect({x+35,y+5,size-40,size-40},c2);
            RSGL::drawRect({x+35,y+30,size-40,size-40},c2);
            RSGL::drawRect({x+15,y+5,size-40,size-15},c2);

            RSGL::drawRect({x+35,y+5,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+35,y+30,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+15,y+5,size-40,size-15},{0,0,0},false); break;
        case 3:
            RSGL::drawRect({x+5,y+35,size-40,size-40},c2);
            RSGL::drawRect({x+30,y+35,size-40,size-40},c2);
            RSGL::drawRect({x+5,y+15,size-15,size-40},c2); 

            RSGL::drawRect({x+5,y+35,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+30,y+35,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+5,y+15,size-15,size-40},{0,0,0},false);  break;
        case 4:
            RSGL::drawRect({x+15,y+5,size-40,size-40},c2);
            RSGL::drawRect({x+15,y+30,size-40,size-40},c2);
            RSGL::drawRect({x+35,y+5,size-40,size-15},c2); 

            RSGL::drawRect({x+15,y+5,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+15,y+30,size-40,size-40},{0,0,0},false);
            RSGL::drawRect({x+35,y+5,size-40,size-15},{0,0,0},false); break;
        default: break;
    }
}


Player p = {200,400,50,1,{250,255,0},{0,220,255}};
int main(){
    while(running){
        win.checkEvents();
        switch (win.event.type){
            case RSGL::KeyPressed: if (win.event.key == "space"){ 
                if (!p.jumping ) { p.y -=20;}
                 if (RSGL::RectCollideRect({bx,p.y2,50,50},{p.x,p.y,p.size,p.size})) { p.y -=20; p.fall=false;}
            } break;
        }
        
        p.draw();

        RSGL::drawRect({bx,p.y2+10,50,40},{0,0,0});
        RSGL::drawRect({bx,p.y2,50,10},{0,0,0});
        if (!RSGL::RectCollideRect({bx,p.y2+10,50,40},{p.x,p.y,p.size,p.size})) bx-=5;
        if (bx < 0) bx=500;
        win.clear();
    }
} 