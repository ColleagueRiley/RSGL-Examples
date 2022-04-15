
enum etype{PLATFORM, OBJECT};

enum shapes {rect,circle};

struct enitiy{
    etype type;
    shapes shape;
    RSGL::color c;
    RSGL::circle cir;
    RSGL::rect r;
    bool grounded=false;
    void draw();
};


void enitiy::draw(){
    switch(shape){
        case circle: RSGL::drawCircle(cir,c);
        case rect: RSGL::drawRect(r,c);
        default: break;
    }
}

std::vector<enitiy> map;


void checkGravNoThread(){
    for (int y=0; y < map.size(); y++){
        if (map.at(y).type == OBJECT){
            bool collide=false;
            while (!collide){
                for (int x=0; x < map.size(); x++){
                    map.at(y).grounded=false;
                    if (x != y && map.at(x).shape == circle && map.at(y).shape == circle && RSGL::CircleCollide(map.at(x).cir,map.at(y).cir) ||
                        x != y && map.at(x).shape == rect && map.at(y).shape == rect && RSGL::RectCollideRect(map.at(x).r,map.at(y).r) ||
                        x != y && map.at(x).shape == rect && map.at(y).shape == circle && RSGL::CircleCollideRect(map.at(y).cir,map.at(x).r) && RSGL::RectCollideRect({map.at(y).cir.x+5, map.at(y).cir.y+map.at(y).cir.radius-1, map.at(y).cir.radius-10,1}, map.at(x).r) ||
                        x != y  && map.at(x).shape == circle && map.at(y).shape == rect && RSGL::CircleCollideRect(map.at(y).cir,map.at(x).r)){ map.at(y).grounded=true; collide=true; break;}
                }   if (!collide){ map.at(y).grounded=false;
                    switch(map.at(y).shape){
                        case circle: map.at(y).cir.y++;
                        case rect:  map.at(y).r.y++;
                        default: break;
                    } system("sleep 0.2");
                }
            }
        }
    }   
}

void* checkGravThreadFunc(void*){checkGravNoThread(); return NULL;}

void checkGrav(){ pthread_t t; pthread_create(&t,NULL,checkGravThreadFunc,NULL);}

int addToMap(enitiy e){map.insert(map.end(),e); return map.size()-1;}