#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include <json-c/json.h>
#include <ctype.h>
#include <time.h>

//Set up the game screen
const int screenWidth = 1500;
const int screenHeight = 1000;

//Set up the path of saving file
const char *savedfilename = "saving/saveddata.json";
const char *rawfilename = "saving/rawdata.json";

//Set up the game credit contents
const char *credits[] = {
        "Game Developed by:",
        "Andrew Yii (ME)",
        "",
        "Programmer:",
        "Andrew Yii (ME)",
        "",
        "Art and Design:",
        "Andrew Yii (ME)",
        "",
        "Music and Sound Design:",
        "Original Soundtrack by Free Online Music Sources",
        "Andrew Yii (ME)",
        "",
        "Special Thanks To:",
        "My Programming Lecturer, Miss Carmen",
        "Free Itch.io Asset Packs Creators",
        "Original Soundtrack by Free Online Music Sources",
        "Raylib and Json-C Library Developer",
        "Family and Friends",
        "",
        "Additional Resources Provided by:",
        "Itch.io Asset Packs",
        "Free Online Music Sources",
        "",
        "Quality Assurance:",
        "Andrew Yii (ME)",
        "My Lecturer, Miss Carmen",
        "My friends",
        "",
        "Game Testers:",
        "Andrew Yii (ME)",
        "My Friends",
        "",
        "With Gratitude:",
        "To all the fans and lecturers who supported us.",
        "Thank you for making this journey worthwhile!",
        "Grateful for this course's chance to explore custom programming",
        NULL
    };


//Custom Struct for the game mode to control the display of screen content
typedef enum{

    MENU,
    LOADING,
    SETTING,
    INSTRUCTION,
    PLAYING,
    ENDING

}GameMode;

//Custom Struct for the display of different chatting content
typedef struct {

    int id;          
    char content[256];
    int whosay;         
    bool showoption;
    bool accept; 
    bool caninput;

} Chat;


//Custom Struct for the control the selected slot to determine the action of player
typedef enum{

    slot0,
    slot1,
    slot2,
    slot3,
    slot4,
    slot5

}slot;


//Custom Struct for the initialise all the things, and easier for passing the variable
typedef struct {

    //General Set Up
    bool closebutton_hover;
    bool button_hover;
    bool button1_hover;
    slot slot;
    GameMode mode;
    Color bgcolor;
    Font myfont;
    Font titlefont;
    Font creditfont;
    Vector2 mouseposition;
    Texture2D normal_cursor;
    Rectangle normal_cursorSrc;
    Rectangle normal_cursorDest;
    Vector2 origin_normal_cursor;
    Texture2D hover_cursor;
    Rectangle hover_cursorSrc;
    Rectangle hover_cursorDest;
    Vector2 origin_hover_cursor;
    float time;
    float yOffset;
    Texture2D menu_sound;
    Rectangle menu_soundSrc;
    Rectangle menu_sound2Src;
    Rectangle menu_soundDest;
    Rectangle menu_sound2Dest;
    Vector2 origin_menu_sound;
    int frequency;


    //Menu Set Up
    Texture2D menuframes[32];
    char menu_picture_filename[32];
    Rectangle menuframeSrc;
    Rectangle menuframeDest;
    Vector2 origin_menuframe;
    Texture2D button;
    Rectangle buttonSrc;
    Rectangle buttonDest;
    Rectangle button2Dest;
    Vector2 origin_button;
    Texture2D buttonhover;
    Rectangle buttonhoverSrc;
    Rectangle buttonhoverDest;
    Rectangle buttonhover2Dest;
    Vector2 origin_buttonhover;


    //After Starting Game Set Up
    bool settingbuttonhover;
    Rectangle settinghoverbuttonSrc;
    Texture2D settingbutton;
    Rectangle settingbuttonSrc;
    Rectangle settingbuttonDest;
    Vector2 origin_settingbutton;
    Texture2D grass;
    Texture2D player;
    Texture2D fence;
    Texture2D house;
    Texture2D door;
    Texture2D furniture;
    Texture2D path;
    Texture2D dig_land;
    Texture2D player_action;
    Texture2D wheat;
    Texture2D watered_land;
    Texture2D tree;
    Rectangle playerSrc;
    Rectangle playerDest;
    Vector2 origin_player;
    float playerSpeed;
    bool musicPaused;
    Music bg_music;
    Sound dig_sound;
    Sound seedling_sound;
    Sound watering_sound;
    Sound harvesting_sound;
    Camera2D view;
    Vector2 offset;
    Vector2 target;
    bool playerMoving;
    int array_land[5][6];
    int array_seed[5][6];
    int array_water[5][6];
    int array_harvested[5][6];
    float array_growth [5][6];
    float array_watercontent [5][6];
    int harvestedwheat;
    int harvestedwheat_x;
    int harvestedwheat_y;
    int playerDir;
    bool playerUp, playerDown, playerRight, playerLeft;
    int playerframe;
    int frameCount;
    bool stay;
    Rectangle grassSrc;
    Rectangle grassDest;
    Vector2 origin_grass;
    float min_x;
    float max_x;
    float min_y;
    float max_y;
    Rectangle fenceySrc;
    Rectangle fencey1Dest;
    Vector2 origin_fencey;
    Rectangle fencexSrc;
    Rectangle fencex1Dest;
    Rectangle fencex2Dest;
    Vector2 origin_fencex;
    Rectangle fencey2Dest;
    Rectangle housewallxSrc;
    Rectangle housewallxtopDest;
    Vector2 origin_housewallx;
    Rectangle housewallyleftbeginSrc;
    Rectangle housewallyleftbeginDest;
    Vector2 origin_housewally;
    Rectangle housewallymiddleSrc;
    Rectangle housewallymiddleleftDest;
    Rectangle housewallyleftendSrc;
    Rectangle housewallyleftendDest;
    Rectangle housewallxbottomDest;
    Rectangle housewallyrightbeginSrc;
    Rectangle housewallyrightbeginDest;
    Rectangle housewallymiddlerightDest;
    Rectangle housewallyrightendSrc;
    Rectangle housewallyrightendDest;
    Rectangle houstilesSrc;
    Rectangle housetilesDest;
    Vector2 origin_houstiles;
    Rectangle bedSrc;
    Rectangle bedDest;
    Vector2 origin_bed;
    Rectangle matSrc;
    Rectangle matDest;
    Vector2 origin_mat;
    Rectangle pictureSrc;
    Rectangle pictureDest;
    Vector2 origin_picture;
    Rectangle cupboardSrc;
    Rectangle cupboardDest;
    Vector2 origin_cupboard;
    Rectangle clockSrc;
    Rectangle clockDest;
    Vector2 origin_clock;
    Rectangle tableSrc;
    Rectangle tableDest;
    Vector2 origin_table;
    Rectangle chairSrc;
    Rectangle chairDest;
    Vector2 origin_chair;
    Rectangle potSrc;
    Rectangle potDest;
    Vector2 origin_pot;
    Rectangle windowSrc;
    Rectangle windowLeftDest;
    Vector2 origin_window;
    Rectangle windowRightDest;
    Rectangle doorSrc;
    Rectangle doorDest;
    Vector2 origin_door;
    Rectangle pathySrc;
    Rectangle pathyDest;
    Vector2 origin_pathy;
    Rectangle farmingareaSrc;
    Rectangle farmingareaDest;
    Vector2 origin_farmingarea;
    Rectangle dig_landSrc;
    Rectangle dig_landDest;
    Vector2 origin_dig_land;
    Rectangle dig_actionSrc;
    Rectangle dig_actionDest;
    Vector2 origin_digaction;
    Rectangle wheatseedSrc;
    Rectangle wheatseedDest;
    Vector2 origin_wheat_seed;
    Rectangle wateredLandSrc;
    Rectangle wateredLandDest;
    Vector2 origin_wateredLand;
    Rectangle water_actionSrc;
    Rectangle water_actionDest;
    Vector2 origin_wateraction;
    Rectangle youngwheatSrc;
    Rectangle youngwheatDest;
    Vector2 origin_youngwheat;
    Rectangle young1wheatSrc;
    Rectangle young1wheatDest;
    Vector2 origin_young1wheat;
    Rectangle young2wheatSrc;
    Rectangle young2wheatDest;
    Vector2 origin_young2wheat;
    Rectangle wheatSrc;
    Rectangle wheatDest;
    Vector2 origin_wheat;
    Rectangle harvest_actionSrc;
    Rectangle harvest_actionDest;
    Vector2 origin_harvestaction;
    Rectangle treeSrc;
    Rectangle treeDest;
    Vector2 origin_tree;
    Texture2D menu_tools;
    Rectangle menu_toolsSrc;
    Rectangle menu_toolsDest;
    Vector2 origin_menu_tools;
    Texture2D menu_icons;
    Rectangle menu_icon1Src;
    Rectangle menu_icon1Dest;
    Rectangle menu_icon2Src;
    Rectangle menu_icon2Dest;
    Rectangle menu_icon3Dest;
    Rectangle menu_icon4Src;
    Rectangle menu_icon4Dest;
    Rectangle menu_icon5Src;
    Rectangle menu_icon5Dest;
    Rectangle menu_icon6Dest;
    Vector2 origin_menu_icon;
    Texture2D chat_icon;
    Rectangle chat_iconSrc;
    Rectangle chat_iconDest;
    Vector2 origin_chat_icon;
    Texture2D wheat_icon;
    Rectangle wheat_iconSrc;
    Rectangle wheat_iconDest;
    Vector2 origin_wheat_icon;
    Texture2D menu_toolshover;
    Rectangle menu_toolshoverSrc;
    Rectangle menu_toolshoverDest;
    Vector2 origin_menu_toolshover;
    bool canspeak;
    bool candig;
    bool canseed;
    bool canwater;
    bool canharvest;
    bool canother;
    bool show_can_farm;
    Texture2D signal;
    Rectangle can_farm_signalSrc;
    Rectangle can_farm_signalDest;
    Vector2 origin_can_farm_signal;
    Texture2D displaymoney;
    Rectangle displaymoneySrc;
    Rectangle displaymoneyDest;
    Vector2 origin_displaymoney;
    int money;
    int money_x;
    int money_y;
    Texture2D seller;
    Rectangle sellerSrc;
    Rectangle sellerDest;
    Vector2 origin_seller;
    int sellerFrame;

    //chatbox of seller
    Texture2D chatbox;
    Rectangle chatboxSrc;
    Rectangle chatboxDest;
    Vector2 origin_chatbox;
    bool showchatbox;
    bool startchat;
    Texture2D dialogbox;
    Rectangle dialogboxSrc;
    Rectangle dialogboxDest;
    Vector2 origin_dialogbox;
    Texture2D seller_emo;
    Rectangle seller_emoSrc;
    Rectangle seller_emoDest;
    Vector2 origin_seller_emo;
    Texture2D character_emo;
    Rectangle character_emoSrc;
    Rectangle character_emoDest;
    Chat chats[20];
    int currentChat;
    int nowargueprice;
    int nowwantsellitems;
    int max_priceallowed;
    bool liar;
    Texture2D developer;
    Rectangle developerSrc;
    Rectangle developerDest;
    int win;

    //Setting Menu
    Texture2D settingmenu;
    Rectangle settingmenuSrc;
    Rectangle settingmenuDest;
    Vector2 origin_settingmenu;
    Texture2D settingmenubackground;
    Rectangle settingmenubackgroundSrc;
    Rectangle settingmenubackgroundDest;
    Vector2 origin_settingmenubackground;
    Texture2D closesettingbutton;
    Rectangle closesettingbuttonSrc;
    Rectangle closesettingbutton1Src;
    Rectangle closesettingbuttonDest;
    Vector2 origin_closesettingbutton;
    Rectangle button3Dest;
    Rectangle button4Dest;
    Rectangle button5Dest;
    Texture2D settinggoodbyepicture;
    Rectangle settinggoodbyepictureSrc;
    Rectangle settinggoodbyepictureDest;
    Vector2 origin_settinggoodbyepicture;
    Texture2D savebackground;
    Rectangle savebackgroundSrc;
    Rectangle savebackgroundDest;
    Vector2 origin_savebackground;
    bool buttonhover3;
    bool buttonhover4;
    bool buttonhover5;
    bool showpop;

    //Loading Menu
    Texture2D loadingbackground;
    Rectangle loadingbackgroundSrc;
    Rectangle loadingbackgroundDest;
    Vector2 origin_loadingbackground;

    //how to play menu
    Texture2D loadingmenu;
    Rectangle loadingmenuSrc;
    Rectangle loadingmenuDest;
    Vector2 origin_loadingmenu;

    char loading_picture_filename[52];
    Texture2D loadinganimationframes[52];
    Rectangle loadinganimationSrc;
    Rectangle loadinganimationDest;
    Vector2 origin_loadinganimation;
    Rectangle closesettingbutton2Dest;
    Texture2D loadingbutton;
    Rectangle loadingbuttonSrc;
    Rectangle loadingbutton2Src;
    Rectangle loadingbuttonDest;
    Rectangle loadingbutton2Dest;
    Rectangle loadingbutton3Dest;
    Rectangle loadingbutton4Dest;
    Vector2 origin_loadingbutton;
    bool new_game;
    bool load_game;

    //Ending
    char endingframes_filename[52];
    Texture2D endingframes[127];
    Rectangle endingframesSrc;
    Rectangle endingframesDest;
    Vector2  origin_endingframes;

} GameState;

//To Style the raylib gui for the input
void SetupCustomTheme() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x4CAF50FF);   
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x388E3CFF);  
    GuiSetStyle(BUTTON, BASE_COLOR_PRESSED, 0x2E7D32FF);        
}

//Update the chatbox content between seller and player
void UpdateDialog(GameState *state, int situation) {
    //Default the chatbox not yet appear
    state->chats[state->currentChat].accept = false;
    if (state->startchat) {
        switch (situation)
        {
        case 1:
            //During option case, to handle accept case
            if (IsKeyPressed(KEY_Y) && state->chats[state->currentChat].showoption) {
                state->chats[state->currentChat].accept = true;
                state->currentChat = 10;  
            } 
            //During option case, to handle reject case
            else if (IsKeyPressed(KEY_N) && state->chats[state->currentChat].showoption) {
                state->chats[state->currentChat].accept = false;
                state->currentChat++; 
            } 
            break;
        
        default:
            //Normal case/ No option case chatbox press c to proceed to the following chat content
            if (IsKeyPressed(KEY_C)){
                state->currentChat++;
                }
            break;
        }

        //In case the the input of player exceed the limit or requirement random set/produced  
        if(state->liar){
            if (state->currentChat > 13) {  
                state->startchat = false;
                state->currentChat = 0;
                state->liar =false;   
            }
        }
        //In normal case where the input does not exceed the requirement set
        else{
            if (state->currentChat > 12) {  
                state->startchat = false;
                state->currentChat = 0;   
            }
        }
    }
}

//Load all the file and Initialise the screen
void Initialise(GameState *state) {

    InitWindow(screenWidth, screenHeight, "2D Farmer Simulator");

    SetTargetFPS(60);

    state->frequency =0;

    state->liar =false;

    state->win = 0;

    state ->mode = MENU;

    state->startchat = false;

    state->show_can_farm = false;

    state->new_game = false;

    state->load_game = false;

    state->showpop = false;

    state ->closebutton_hover = false;

    state ->settingbuttonhover = false;

    state->button_hover = false;

    state->buttonhover3= false;

    state->buttonhover4= false;

    state->buttonhover5= false;

    state->bgcolor = (Color){147, 211, 196, 255};

    state->myfont = LoadFont("font/myfont.ttf");

    state->titlefont = LoadFont("font/titlefont.ttf");

    state->creditfont = LoadFont("font/creditfont.ttf");

    state->normal_cursor = LoadTexture("picture/cursor/normalcursor.png");

    state->hover_cursor = LoadTexture("picture/cursor/hovercursor.png");

    //It is gif and be cut into a lot of frame, so need to use for loop to load all of them
    for (int i = 0; i < 32; i++) {

        sprintf(state->menu_picture_filename, "picture/moving_menu_picture/frame%d.png", i);
        
        state->menuframes[i] = LoadTexture(state->menu_picture_filename);
    }

    state->menu_sound = LoadTexture("picture/general_button_set_up/Menu_Sound.png");
    state->button = LoadTexture("picture/general_button_set_up/button.png");
    state->buttonhover = LoadTexture("picture/general_button_set_up/button_hover.png");
    state->settingbutton = LoadTexture("picture/setting/setting_button.png");
    state->settingmenu = LoadTexture("picture/setting/setting_menu.png");
    state->settingmenubackground = LoadTexture("picture/setting/settingbackground.png");
    state->closesettingbutton = LoadTexture("picture/setting/closesetting_button.png");
    state->settinggoodbyepicture = LoadTexture("picture/setting/settingggodbye.png");
    state->savebackground = LoadTexture("picture/setting/savebackground.png");
    state->loadingbackground = LoadTexture("picture/loading/background_loading.png");
    state->loadingmenu = LoadTexture("picture/instruction/loading_menu.png");
    state->loadingbutton = LoadTexture("picture/loading/loadingbutton.png");
    state->grass = LoadTexture("picture/environment_set_up/Grass.png");
    state->player = LoadTexture("picture/player/player.png");
    state->fence = LoadTexture("picture/environment_set_up/Fences.png");
    state->house = LoadTexture("picture/house_set_up/House.png");
    state->furniture = LoadTexture("picture/house_set_up/Furniture.png");
    state->door = LoadTexture("picture/house_set_up/Doors.png");
    state->path = LoadTexture("picture/environment_set_up/Paths.png");
    state->dig_land = LoadTexture("picture/gardening/Land.png");
    state->player_action = LoadTexture("picture/player/Player_Action.png");
    state->wheat = LoadTexture("picture/gardening/Basic_Plants.png");
    state->watered_land = LoadTexture("picture/gardening/WateredLand.png");
    state->tree = LoadTexture("picture/environment_set_up/Biofield.png");
    state->menu_tools = LoadTexture("picture/gaming_menu/objectholdingslot.png");
    state->menu_icons = LoadTexture("picture/gaming_menu/tools_icon.png");
    state->chat_icon = LoadTexture("picture/gaming_menu/chat_icon.png");
    state->wheat_icon = LoadTexture("picture/gaming_menu/wheat_icon.png");
    state->menu_toolshover = LoadTexture("picture/gaming_menu/holdingsymbol.png");
    state->signal = LoadTexture("picture/money_display/signal.png");
    state->displaymoney = LoadTexture("picture/money_display/money_display.png");
    state->seller = LoadTexture("picture/business_chat/seller.png");
    state->chatbox = LoadTexture("picture/business_chat/chatbox.png");
    state->dialogbox = LoadTexture("picture/business_chat/dialogbox.png");
    state->seller_emo = LoadTexture("picture/business_chat/seller_emote.png");
    state->character_emo = LoadTexture("picture/business_chat/character_emote.png");
    state->developer = LoadTexture("picture/business_chat/developer.png");

    for (int i = 0; i < 53; i++) {

        sprintf(state->loading_picture_filename, "picture/loading/animationonloading/frame%d.png", i);
        
        state->loadinganimationframes[i] = LoadTexture(state->loading_picture_filename);
    }

    for (int i = 0; i < 127; i++) {

        sprintf(state->endingframes_filename, "picture/ending_frame/frame%d.png", i);
        
        state->endingframes[i] = LoadTexture(state->endingframes_filename);
    }


    //Player's Location + Moving Set Up
    state->playerSrc = (Rectangle){0, 0, 48, 48};
    state->playerDest = (Rectangle){300, 400, 200, 200};
    state->origin_player = (Vector2){state->playerDest.width, state->playerDest.height};
    state->playerSpeed = 3;

    //Sound Set Up
    state->musicPaused = false;
    InitAudioDevice();
    state->bg_music = LoadMusicStream("sound/bgmusic.mp3");
    state->dig_sound = LoadSound("sound/dig.mp3");
    state->seedling_sound = LoadSound("sound/seedling.mp3");
    state->watering_sound = LoadSound("sound/watering.mp3");
    state->harvesting_sound = LoadSound("sound/harvesting.mp3");
    PlayMusicStream(state->bg_music);
    SetMusicVolume(state->bg_music, 0.2f);
    SetSoundVolume(state->dig_sound,4.0f);
    SetSoundVolume(state->seedling_sound,4.0f);
    SetSoundVolume(state->watering_sound,4.0f);
    SetSoundVolume(state->harvesting_sound,4.0f);

    //Camera Set Up To Make Sure it will follow the character
    state->offset = (Vector2){(float)screenWidth / 2, (float)screenHeight / 2};
    state->target = (Vector2){(float)state->playerDest.x - (state->playerDest.width / 2), 
                              (float)state->playerDest.y - (state->playerDest.height / 2)};
    state->view = (Camera2D){state->offset, state->target, 0, 1};


    //Cursor for the Menu
    state->normal_cursorSrc=(Rectangle){0,0,16,16};
    state->normal_cursorDest=(Rectangle){-5000,-5000,40,40};
    state->origin_normal_cursor=(Vector2){state->normal_cursorDest.width / 2, state->normal_cursorDest.height / 2};
    state->hover_cursorSrc=(Rectangle){0,0,16,16};
    state->hover_cursorDest=(Rectangle){-5000,-5000,40,40};
    state->origin_hover_cursor=(Vector2){state->hover_cursorDest.width / 2, state->hover_cursorDest.height / 2};

    state->menuframeSrc=(Rectangle){0,0,1080,1080};
    state->menuframeDest=(Rectangle){750,500,1500,1000};
    state->origin_menuframe=(Vector2){state->menuframeDest.width / 2, state->menuframeDest.height / 2};

    state->buttonhoverSrc=(Rectangle){0,0,93,31};
    state->buttonhoverDest=(Rectangle){750,640,480,160};
    state->buttonhover2Dest=(Rectangle){750,840,480,160};
    state->origin_buttonhover=(Vector2){state->buttonhoverDest.width / 2, state->buttonhoverDest.height / 2};

    state->buttonSrc=(Rectangle){0,0,96,32};
    state->buttonDest=(Rectangle){750,650,480,160};
    state->button2Dest=(Rectangle){750,850,480,160};
    state->origin_button=(Vector2){state->buttonDest.width / 2, state->buttonDest.height / 2};

    state->menu_soundSrc=(Rectangle){0,0,25,35};
    state->menu_sound2Src=(Rectangle){35,0,25,35};
    state->menu_soundDest=(Rectangle){60,60,100,140};
    state->menu_sound2Dest=(Rectangle){70,70,100,140};
    state->origin_menu_sound=(Vector2){state->menu_soundDest.width / 2, state->menu_soundDest.height / 2};

    //Game Graphic Set Up
    state->settingbuttonSrc = (Rectangle){0,0,30,28};
    state->settingbuttonDest = (Rectangle){-490,-130,135,126};
    state->origin_settingbutton = (Vector2){state->settingbuttonDest.width / 2, state->settingbuttonDest.height / 2};
    state->settinghoverbuttonSrc = (Rectangle){34,0,26,28};

    state->grassSrc = (Rectangle){0, 80, 96, 32};
    state->grassDest = (Rectangle){0, 0, 8000, 8000};
    state->origin_grass = (Vector2){state->grassDest.width / 2, state->grassDest.height / 2};
    state->min_x = state->grassDest.x;
    state->max_x = (state->grassDest.x + state->grassDest.width) / 4 - 10;
    state->min_y = state->grassDest.y;
    state->max_y = (state->grassDest.y + state->grassDest.height) / 4 - 50;

    state->fenceySrc = (Rectangle){0, 0, 15, 45};
    state->fencey1Dest = (Rectangle){-150, -10, 100, 200}; 
    state->origin_fencey = (Vector2){state->fencey1Dest.width / 2, state->fencey1Dest.height / 2};

    state->fencexSrc = (Rectangle){20, 48, 40, 17};
    state->fencex1Dest = (Rectangle){-38, -125, 270, 80}; 
    state->fencex2Dest = (Rectangle){-38, 1920, 270, 80}; 
    state->origin_fencex = (Vector2){state->fencex1Dest.width / 2, state->fencex1Dest.height / 2};
    state->fencey2Dest = (Rectangle){1925, -10, 100, 200}; 

    state->housewallxSrc = (Rectangle){16, 0, 16, 16};
    state->housewallxtopDest = (Rectangle){100, 100, 100, 75}; 
    state->origin_housewallx = (Vector2){state->housewallxtopDest.width / 2, state->housewallxtopDest.height / 2};

    state->housewallyleftbeginSrc = (Rectangle){11, 0, 5, 32};
    state->housewallyleftbeginDest = (Rectangle){38, 100, 25, 75}; 
    state->origin_housewally = (Vector2){state->housewallyleftbeginDest.width / 2, state->housewallyleftbeginDest.height / 2};

    state->housewallymiddleSrc = (Rectangle){11, 5, 5, 27};
    state->housewallymiddleleftDest = (Rectangle){38, 113, 25, 75}; 

    state->housewallyleftendSrc = (Rectangle){11, 32, 5, 16};
    state->housewallyleftendDest = (Rectangle){38, 488, 25, 75}; 

    state->housewallxbottomDest = (Rectangle){100, 488, 100, 75}; 

    state->housewallyrightbeginSrc = (Rectangle){32, 0, 5, 32};
    state->housewallyrightbeginDest = (Rectangle){562, 100, 25, 75}; 

    state->housewallymiddlerightDest = (Rectangle){562, 113, 25, 75}; 
    state->housewallyrightendSrc = (Rectangle){32, 32, 5, 16};
    state->housewallyrightendDest = (Rectangle){562, 488, 25, 75}; 

    state->houstilesSrc = (Rectangle){16,16,16,16};
    state->housetilesDest = (Rectangle){100,175,100,75};
    state->origin_houstiles = (Vector2){state->housetilesDest.width/2,state->housetilesDest.height/2};

    state->bedSrc = (Rectangle){0,26,15,22};
    state->bedDest = (Rectangle){120,200,77,121};
    state->origin_bed = (Vector2){state->bedDest.width/2,state->bedDest.height/2};

    state->matSrc = (Rectangle){51,82,25,13};
    state->matDest = (Rectangle){290,430,150,78};
    state->origin_mat = (Vector2){state->matDest.width/2,state->matDest.height/2};

    state->pictureSrc = (Rectangle){35,5,12,8};
    state->pictureDest = (Rectangle){200,105,72,48};
    state->origin_picture = (Vector2){state->pictureDest.width/2,state->pictureDest.height/2};

    state->cupboardSrc = (Rectangle){49,32,14,16};
    state->cupboardDest = (Rectangle){500,155,70,80};
    state->origin_cupboard = (Vector2){state->cupboardDest.width/2,state->cupboardDest.height/2};

    state->clockSrc = (Rectangle){98,50,13,13};
    state->clockDest = (Rectangle){400,105,50,50};
    state->origin_clock = (Vector2){state->clockDest.width/2,state->clockDest.height/2};

    state->tableSrc = (Rectangle){49,49,14,14};
    state->tableDest = (Rectangle){400,300,100,100};
    state->origin_table = (Vector2){state->tableDest.width/2,state->tableDest.height/2};

    state->chairSrc = (Rectangle){83,33,10,13};
    state->chairDest = (Rectangle){485,300,60,78};
    state->origin_chair = (Vector2){state->chairDest.width/2,state->chairDest.height/2};

    state->potSrc = (Rectangle){51,0,11,15};
    state->potDest = (Rectangle){375,275,44,60};
    state->origin_pot = (Vector2){state->potDest.width/2,state->potDest.height/2};

    state->windowSrc = (Rectangle){48,32,16,16};
    state->windowLeftDest = (Rectangle){200,488,100,75};
    state->origin_window = (Vector2){state->windowLeftDest.width/2,state->windowLeftDest.height/2};


    state->windowRightDest = (Rectangle){400,488,100,75};

    state->doorSrc = (Rectangle){0,16,16,16};
    state->doorDest = (Rectangle){300,488,100,75};
    state->origin_door = (Vector2){state->doorDest.width/2,state->doorDest.height/2};

    state->pathySrc = (Rectangle){0,0,15,43};
    state->pathyDest = (Rectangle){300,600,113,168};
    state->origin_pathy = (Vector2){state->pathyDest.width/2,state->pathyDest.height/2};

    state->farmingareaSrc = (Rectangle){0,0,48,48};
    state->farmingareaDest = (Rectangle){1250,500,1200,1000};
    state->origin_farmingarea= (Vector2){state->farmingareaDest.width/2,state->farmingareaDest.height/2};

    state->dig_landSrc = (Rectangle){52,52,8,8};
    state->dig_landDest = (Rectangle){900 ,200 ,75,75};
    state->origin_dig_land= (Vector2){state->dig_landDest.width/2,state->dig_landDest.height/2};

    state->wheatseedSrc = (Rectangle){17,0, 13 , 15};
    state->wheatseedDest = (Rectangle){900 ,185 ,50,50};
    state->origin_wheat_seed = (Vector2){state->wheatseedDest.width/2,state->wheatseedDest.height/2};

    state->youngwheatSrc = (Rectangle){33,0, 15 , 15};
    state->youngwheatDest = (Rectangle){900 ,185 ,50,50};
    state->origin_youngwheat = (Vector2){state->youngwheatDest.width/2,state->youngwheatDest.height/2};

    state->young1wheatSrc = (Rectangle){49,0, 15 , 15};
    state->young1wheatDest = (Rectangle){900 ,185 ,50,50};
    state->origin_young1wheat = (Vector2){state->young1wheatDest.width/2,state->young1wheatDest.height/2};

    state->young2wheatSrc = (Rectangle){65,0, 15 , 15};
    state->young2wheatDest = (Rectangle){900 ,185 ,50,50};
    state->origin_young2wheat = (Vector2){state->young2wheatDest.width/2,state->young2wheatDest.height/2};

    state->harvestedwheat = 0;
    state->harvestedwheat_x = 810;
    state->harvestedwheat_y = -150;

    state->wheatSrc = (Rectangle){81,0, 14 , 15};
    state->wheatDest = (Rectangle){760 ,-125 ,75,75};
    state->origin_wheat = (Vector2){state->wheatDest.width/2,state->wheatDest.height/2};

    //array initialise to 0 for gardening,harvesting,digging
    memset(state->array_land, 0, sizeof(state->array_land));
    memset(state->array_seed, 0, sizeof(state->array_seed));
    memset(state->array_water, 0, sizeof(state->array_water));
    memset(state->array_harvested, 0, sizeof(state->array_harvested));
    memset(state->array_growth, 0, sizeof(state->array_growth));
    memset(state->array_watercontent, 0, sizeof(state->array_watercontent));

    state->dig_actionSrc = (Rectangle){0,0,48,48};
    state->dig_actionDest = (Rectangle){500 ,200 ,200,200};
    state->origin_digaction= (Vector2){state->dig_actionDest.width/2,state->dig_actionDest.height/2};

    state->water_actionSrc = (Rectangle){0,0,48,48};
    state->water_actionDest = (Rectangle){500 ,200 ,200,200};
    state->origin_wateraction= (Vector2){state->water_actionDest.width/2,state->water_actionDest.height/2};

    state->harvest_actionSrc = (Rectangle){0,0,48,48};
    state->harvest_actionDest = (Rectangle){500 ,200 ,200,200};
    state->origin_harvestaction= (Vector2){state->harvest_actionDest.width/2,state->harvest_actionDest.height/2};

    state->wateredLandSrc = (Rectangle){52,52,8,8};
    state->wateredLandDest = (Rectangle){900 ,200 ,75,75};
    state->origin_wateredLand= (Vector2){state->wateredLandDest.width/2,state->wateredLandDest.height/2};

    state->treeSrc = (Rectangle){20,0,24,32};
    state->treeDest = (Rectangle){-25,-40,180,200};
    state->origin_tree = (Vector2){state->treeDest.width/2,state->treeDest.height/2};

    state->menu_toolsSrc = (Rectangle){0,0, 304,71};
    state->menu_toolsDest = (Rectangle){200,733, 608,142};
    state->origin_menu_tools = (Vector2){state->menu_toolsDest.width/2,state->menu_toolsDest.height/2};

    state->menu_icon1Src = (Rectangle){0,0, 22,22};
    state->menu_icon1Dest = (Rectangle){-43,710, 110,110};
    state->origin_menu_icon = (Vector2){state->menu_icon1Dest.width/2,state->menu_icon1Dest.height/2};
    
    state->menu_icon2Src = (Rectangle){32,0, 22,22};
    state->menu_icon2Dest = (Rectangle){54,710, 110,110};
    state->menu_icon3Dest = (Rectangle){151,710, 110,110};
    state->menu_icon4Src = (Rectangle){65,0, 22,22};
    state->menu_icon4Dest = (Rectangle){252,710, 110,110};
    state->menu_icon5Src = (Rectangle){0,32, 22,22};
    state->menu_icon5Dest = (Rectangle){342,710, 110,110};
    state->menu_icon6Dest = (Rectangle){439,710, 110,110};

    state->chat_iconSrc = (Rectangle){0,0, 16,17};
    state->chat_iconDest = (Rectangle){-40,713, 72,76.5};
    state->origin_chat_icon = (Vector2){state->chat_iconDest.width/2,state->chat_iconDest.height/2};
    state->wheat_iconSrc = (Rectangle){0,0, 16,16};
    state->wheat_iconDest = (Rectangle){152,711, 60,60};
    state->origin_wheat_icon = (Vector2){state->wheat_iconDest.width/2,state->wheat_iconDest.height/2};
    state->menu_toolshoverSrc = (Rectangle){0,0, 30,30};
    state->menu_toolshoverDest = (Rectangle){-43,718, 120,120};
    state->origin_menu_toolshover= (Vector2){state->menu_toolshoverDest.width/2,state->menu_toolshoverDest.height/2};

    state->can_farm_signalSrc = (Rectangle){0,0,15,15};
    state->can_farm_signalDest = (Rectangle){650,-70,120,120};
    state->origin_can_farm_signal = (Vector2){state->can_farm_signalDest.width/2,state->can_farm_signalDest.height};

    state->displaymoneySrc = (Rectangle){0,0,39,17};
    state->displaymoneyDest = (Rectangle){830,30,234,102};
    state->origin_displaymoney = (Vector2){state->displaymoneyDest.width/2,state->displaymoneyDest.height};

    state->money = 0;
    state->money_x = 810;
    state->money_y = -35;

    state-> sellerSrc = (Rectangle){48,0, 48,64};
    state-> sellerDest = (Rectangle){550,580, 66,88};
    state-> origin_seller =(Vector2){state->sellerDest.width/2,state->sellerDest.height} ;

    state-> chatboxSrc = (Rectangle){0,0, 48,48};
    state-> chatboxDest = (Rectangle){610,550,85,85};
    state-> origin_chatbox =(Vector2){state->chatboxDest.width/2,state->chatboxDest.height} ;

    state-> dialogboxSrc = (Rectangle){0,0, 240,64};
    state-> dialogboxDest = (Rectangle){200,820,1600,426};
    state-> origin_dialogbox =(Vector2){state->dialogboxDest.width/2,state->dialogboxDest.height} ;

    state-> seller_emoSrc = (Rectangle){0,0,125,160};
    state-> seller_emoDest = (Rectangle){-385,720,187.5,240};
    state-> origin_seller_emo = (Vector2){state->seller_emoDest.width/2,state->seller_emoDest.height};

    state-> character_emoSrc = (Rectangle){0,0,32,32};
    state-> character_emoDest = (Rectangle){state->seller_emoDest.x,state->seller_emoDest.y,state->seller_emoDest.width,state->seller_emoDest.width};

    state-> developerSrc = (Rectangle){0,0,430,430};
    state-> developerDest = (Rectangle){state->seller_emoDest.x,state->seller_emoDest.y,state->seller_emoDest.width,state->seller_emoDest.width};


    //Chat content
    state->chats[1] = (Chat){0, "Morning,Catie! Ready to sell?", 0, false, false,false};
    state->chats[2] = (Chat){0, "Sure,Lenni! I have some wheat to sell.", 1, false, false,false};
    state->chats[3] = (Chat){1, "How about 5 coins per bushel?", 0, true, false,false};
    state->chats[4] = (Chat){1, "Nah, I want more than that!", 1, false, false,false}; 
    state->chats[5] = (Chat){2, "What about 7 coins? Sound fair?", 0, true, false, false};
    state->chats[6] = (Chat){2, "Can you do better? I'm thinking......", 1, false, false,true};
    state->chats[7] = (Chat){3, "Let's settle at 9 coins, deal?", 0, true, false, false};
    state->chats[8] = (Chat){3, "I want a higher price! I'm thinking......", 1, false,false, true};
    state->chats[9] = (Chat){4, "Deal! How many bushels?", 0, false,false, false};
    state->chats[10] = (Chat){4, "I'd like to sell a few bushels.", 1, false, false, true};
    state->chats[11] = (Chat){5, "Great deal! Goodbye!", 0, false,false, false};
    state->chats[12] = (Chat){5, "See you next time!", 1, false,false,false};
    state->chats[13] = (Chat){6, "Liar,this isn't a fair deal, I'm out!", 0, false,false, false};

    //setting menu
    state->settingmenuSrc = (Rectangle){0,0, 120 , 140};
    state->settingmenuDest = (Rectangle){760 ,460 ,900,1050};
    state->origin_settingmenu = (Vector2){state->settingmenuDest.width/2,state->settingmenuDest.height/2};
    state->settingmenubackgroundSrc = (Rectangle){0,0, 640 , 360};
    state->settingmenubackgroundDest = (Rectangle){140 ,300 ,3000,1500};
    state->origin_settingmenubackground = (Vector2){state->settingmenubackgroundDest.width/2,state->settingmenubackgroundDest.height/2};
    state->closesettingbuttonSrc = (Rectangle){0,0, 20 , 28};
    state->closesettingbutton1Src = (Rectangle){34,0, 18 , 28};
    state->closesettingbuttonDest = (Rectangle){1040 ,130 ,100,140};
    state->origin_closesettingbutton = (Vector2){state->closesettingbuttonDest.width/2,state->closesettingbuttonDest.height/2};
    state->button3Dest = (Rectangle){750,350,480,160};
    state->button4Dest = (Rectangle){750,550,480,160};
    state->button5Dest = (Rectangle){750,750,480,160};
    state->settinggoodbyepictureSrc = (Rectangle){0,0, 428 , 583};
    state->settinggoodbyepictureDest = (Rectangle){450 ,330 ,675,922};
    state->origin_settinggoodbyepicture = (Vector2){state->settinggoodbyepictureDest.width/2,state->settinggoodbyepictureDest.height/2};
    state->savebackgroundSrc = (Rectangle){0,0, 1201 , 621};
    state->savebackgroundDest = (Rectangle){0 ,300 ,3002,1552};
    state->origin_savebackground = (Vector2){state->savebackgroundDest.width/2,state->savebackgroundDest.height/2};

    //loading menu
    state->loadingbackgroundSrc = (Rectangle){280,0, 1000 , 720};
    state->loadingbackgroundDest = (Rectangle){760,500, 1600 , 1152};
    state->origin_loadingbackground = (Vector2){state->loadingbackgroundDest.width/2,state->loadingbackgroundDest.height/2};
    state->loadingmenuSrc = (Rectangle){0,0, 120 , 140};
    state->loadingmenuDest = (Rectangle){1115 ,560 ,900,1050};
    state->origin_loadingmenu = (Vector2){state->loadingbackgroundDest.width/2,state->loadingbackgroundDest.height/2};
    state->closesettingbutton2Dest = (Rectangle){1410 ,80 ,100,140};
    state->loadinganimationSrc=(Rectangle){3,5,590,328};
    state->loadinganimationDest=(Rectangle){375,530,1100,650};
    state->origin_loadinganimation=(Vector2){state->loadinganimationDest.width / 2, state->loadinganimationDest.height / 2};
    state->loadingbuttonSrc = (Rectangle){0,0,30,27};
    state->loadingbutton2Src = (Rectangle){65,0,30,27};
    state->loadingbuttonDest = (Rectangle){1115,260,120,108};
    state->loadingbutton2Dest = (Rectangle){1130,260,120,108};
    state->loadingbutton3Dest = (Rectangle){1115,400,120,108};
    state->loadingbutton4Dest = (Rectangle){1130,400,120,108};
    state->origin_loadingbutton = (Vector2){state->loadingbuttonDest.width / 2, state->loadingbuttonDest.height / 2};

    //ending
    state->endingframesSrc = (Rectangle){161,14, 1598 , 1057};
    state->endingframesDest = (Rectangle){1120,350, 500 , 500};
    state->origin_endingframes = (Vector2){state->endingframesDest.width / 2, state->endingframesDest.height / 2};
}

//move all the fixed thing on the screen according to the player moving at y-axis
void moveAllY(GameState *state, int delta) {
    state->playerDest.y += delta;
    state->harvestedwheat_y += delta;
    state->wheatDest.y += delta;
    state->settingbuttonDest.y += delta;
    state->menu_toolsDest.y += delta;
    state->menu_icon1Dest.y += delta;
    state->menu_icon2Dest.y += delta;
    state->menu_icon3Dest.y += delta;
    state->menu_icon4Dest.y += delta;
    state->menu_icon5Dest.y += delta;
    state->menu_icon6Dest.y += delta;
    state->chat_iconDest.y += delta;
    state->wheat_iconDest.y += delta;
    state->menu_toolshoverDest.y += delta;
    state->can_farm_signalDest.y += delta;
    state->displaymoneyDest.y += delta;
    state->money_y += delta;
    state->dialogboxDest.y += delta;
    state->seller_emoDest.y += delta;
}

//move all the fixed thing on the screen according to the player moving at x-axis
void moveAllX(GameState *state, int delta) {
    state->playerDest.x += delta;
    state->harvestedwheat_x += delta;
    state->wheatDest.x += delta;
    state->settingbuttonDest.x += delta;
    state->menu_toolsDest.x += delta;
    state->menu_icon1Dest.x += delta;
    state->menu_icon2Dest.x += delta;
    state->menu_icon3Dest.x += delta;
    state->menu_icon4Dest.x += delta;
    state->menu_icon5Dest.x += delta;
    state->menu_icon6Dest.x += delta;
    state->chat_iconDest.x += delta;
    state->wheat_iconDest.x += delta;
    state->menu_toolshoverDest.x += delta;
    state->can_farm_signalDest.x += delta;
    state->displaymoneyDest.x += delta;
    state->money_x += delta;
    state->dialogboxDest.x += delta;
    state->seller_emoDest.x += delta;
}

//Check Collision......
void checkCollisionWithInsideRoomWall(GameState *state, Rectangle wall) {

     if ((wall.x-10 <= state->playerDest.x && state->playerDest.x <= wall.x + 100) &&
        (wall.y <= state->playerDest.y && state->playerDest.y <= wall.y + 3)) 
        {
            moveAllY(state, -10);
    }

    if ((wall.x + 40 <= state->playerDest.x && state->playerDest.x <= wall.x + wall.width *2+30) &&
        (wall.y +  wall.height <= state->playerDest.y && state->playerDest.y <= wall.y + wall.height + 40)) {

            moveAllY(state,10);
    }

    if ((wall.x + 30 <= state->playerDest.x && state->playerDest.x <= wall.x + wall.width + 50) &&
        (wall.y <= state->playerDest.y && state->playerDest.y <= wall.y + wall.height)) {

            moveAllX(state,-10);
    }

    if ((wall.x + wall.width + 60 <= state->playerDest.x && state->playerDest.x <= wall.x + wall.width + 110) &&
        (wall.y <= state->playerDest.y && state->playerDest.y <= wall.y + wall.height + 20)) {
            moveAllX(state,10);
    }
}

//Check Collision......
void checkCollisionWithOutsideRoomWall(GameState *state, Rectangle wall) {

    if ((wall.x +61 <= state->playerDest.x && state->playerDest.x <= wall.x + wall.width +57) &&
        (wall.y -30 <= state->playerDest.y && state->playerDest.y <= wall.y - 20)) 
        {
            moveAllY(state,-10);

    }

    if ((wall.x +61 <= state->playerDest.x && state->playerDest.x <= wall.x + wall.width +57 ) &&
        (wall.y + wall.height   <= state->playerDest.y && state->playerDest.y <= wall.y + + wall.height +35)) {

            moveAllY(state,10);
    
    }

    if ((wall.x +43 <= state->playerDest.x && state->playerDest.x <= wall.x +60) &&
        (wall.y -10 <= state->playerDest.y && state->playerDest.y <= wall.y + wall.height +10)) {

            moveAllX(state,-10);

    }

    if ((wall.x + wall.width+47 <= state->playerDest.x && state->playerDest.x <= wall.x + wall.width + 100) &&
        (wall.y -10 <= state->playerDest.y && state->playerDest.y <= wall.y + wall.height +10 )) {

            moveAllX(state,10);

    }
}

//Check Collision......
void CollisionObject(GameState *state) {

    checkCollisionWithInsideRoomWall(state, state->bedDest);

    checkCollisionWithInsideRoomWall(state, state->cupboardDest);

    checkCollisionWithInsideRoomWall(state, state->tableDest);

    checkCollisionWithInsideRoomWall(state, state->chairDest);

    checkCollisionWithOutsideRoomWall(state, state->treeDest);

    checkCollisionWithOutsideRoomWall(state, state->sellerDest);

}

//Animation on the door
void AnimationOnDoor(GameState *state){

    if (state->playerDest.y < state->doorDest.y && 300 <= state->playerDest.x && state->playerDest.x<= 420){

        state->doorSrc.y = state->doorSrc.height ;

    } 

    else{
        if(state->doorDest.y + 10  < state->playerDest.y && state->playerDest.y >  state->doorDest.y + 5 && state->playerDir == 0 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

            state->doorSrc.y = state->doorSrc.height * 3;

        }

        if(state->doorDest.y + 15  < state->playerDest.y && state->playerDest.y >  state->doorDest.y + 10 && state->playerDir == 0 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

            state->doorSrc.y = state->doorSrc.height * 2;

        }

        if(state->doorDest.y  + 20 < state->playerDest.y && state->playerDest.y >  state->doorDest.y + 15 && state->playerDir == 0 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

            state->doorSrc.y = state->doorSrc.height * 0;

            }

        if (state->playerDest.y > state->doorDest.y  + state->doorDest.height + 30 && state->playerDir == 0 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

        state->doorSrc.y = state->doorSrc.height ;

        } 

        else{
            if(state->doorDest.y + 55 + state->doorDest.height < state->playerDest.y && state->playerDest.y <  state->doorDest.y + 50 + state->doorDest.height && state->playerDir == 1 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

                state->doorSrc.y = state->doorSrc.height * 3;

            }

            if(state->doorDest.y + 50 + state->doorDest.height > state->playerDest.y && state->playerDest.y <  state->doorDest.y + 45 + state->doorDest.height&& state->playerDir == 1 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

                state->doorSrc.y = state->doorSrc.height * 2;

            }

            if(state->doorDest.y  + state->doorDest.height + 45 > state->playerDest.y && state->playerDest.y <  state->doorDest.y + 40 + state->doorDest.height && state->playerDir == 1 && 300 <= state->playerDest.x && state->playerDest.x<= 420){

                state->doorSrc.y = state->doorSrc.height * 0;

                }
        }
    }
    }

//Check Collision...... due to this construction using for loop
void checkCollisionwallxtop(GameState *state) {
    
    if ((90 <= state->playerDest.x && state->playerDest.x <= state->housewallxtopDest.x + 100) &&
        (state->housewallxtopDest.y <= state->playerDest.y && state->playerDest.y <= state->housewallxtopDest.y + 3)) 
        {

        state->playerDest.y = state->housewallxtopDest.y - 1;
        state->harvestedwheat_y -=  3;
        state->wheatDest.y -=  3 ;
        state->settingbuttonDest.y -= 3;
        state->menu_toolsDest.y -=3;
        state->menu_icon1Dest.y -=3;
        state->menu_icon2Dest.y -=3;
        state->menu_icon3Dest.y -=3;
        state->menu_icon4Dest.y -=3;
        state->menu_icon5Dest.y -=3;
        state->menu_icon6Dest.y -=3;
        state->chat_iconDest.y -=3;
        state->wheat_iconDest.y -=3;
        state->menu_toolshoverDest.y -=3;
        state->can_farm_signalDest.y -=3;
        state->displaymoneyDest.y -=3;
        state->money_y -=3;
        state->dialogboxDest.y -=3;
        state->seller_emoDest.y -=3;

    }

    if ((100 <= state->playerDest.x && state->playerDest.x <= state->housewallxtopDest.x + 100) &&
        (state->housewallxtopDest.y + state->housewallxtopDest.height <= state->playerDest.y && state->playerDest.y <= state->housewallxtopDest.y + state->housewallxtopDest.height + 50)) {

        moveAllY(state,15);
    }
}

//Check Collision...... due to this construction using for loop
void checkCollisionwallyleft(GameState *state) {

    if ((state->housewallyleftbeginDest.x + 30 <= state->playerDest.x && state->playerDest.x <= state->housewallyleftbeginDest.x + state->housewallyleftbeginDest.width + 50) &&
        (state->housewallyleftbeginDest.y <= state->playerDest.y && state->playerDest.y <= state->housewallyleftendDest.y + state->housewallyleftendDest.height + state->housewallxbottomDest.height / 2)) {

        
            moveAllX(state,-15);
    }

    if ((state->housewallyleftbeginDest.x + state->housewallyleftbeginDest.width + 60 <= state->playerDest.x && state->playerDest.x <= state->housewallyleftbeginDest.x + state->housewallyleftbeginDest.width + 120) &&
        (state->housewallyleftbeginDest.y <= state->playerDest.y && state->playerDest.y <= state->housewallyleftendDest.y + state->housewallyleftendDest.height)) {

            moveAllX(state,15);
    }
}

//Check Collision...... due to this construction using for loop
void checkCollisionwallyright(GameState *state) {

    if ((state->housewallyrightbeginDest.x + 40 <= state->playerDest.x && state->playerDest.x <= state->housewallyrightbeginDest.x + state->housewallyrightbeginDest.width + 60) &&
        (state->housewallyrightbeginDest.y <= state->playerDest.y && state->playerDest.y <= state->housewallyrightendDest.y + state->housewallyrightendDest.height + state->housewallxbottomDest.height / 2)) {

            moveAllX(state,-15);
    }

    if ((state->housewallyrightbeginDest.x + state->housewallyrightbeginDest.width + 60 <= state->playerDest.x && state->playerDest.x <= state->housewallyrightbeginDest.x + state->housewallyrightbeginDest.width + 120) &&
        (state->housewallyrightbeginDest.y <= state->playerDest.y && state->playerDest.y <= state->housewallyrightendDest.y + state->housewallyrightendDest.height)) {

            moveAllX(state,15);
    }
}

//Check Collision...... due to this construction using for loop
void checkCollisionwallxbottom(GameState *state) {
    
    if ((90 <= state->playerDest.x && state->playerDest.x <= state->housewallxbottomDest.x + 100) &&
        (state->housewallxbottomDest.y <= state->playerDest.y && state->playerDest.y <= state->housewallxbottomDest.y + 3)) 
        {

        if(!(380 <=state->playerDest.x && state->playerDest.x<=420)){

        state->playerDest.y = state->housewallxbottomDest.y - 1;
        state->harvestedwheat_y -= 3;
        state->wheatDest.y -=  3 ;
        state->settingbuttonDest.y -= 3;
        state->menu_toolsDest.y -=3;
        state->menu_icon1Dest.y -=3;
        state->menu_icon2Dest.y -=3;
        state->menu_icon3Dest.y -=3;
        state->menu_icon4Dest.y -=3;
        state->menu_icon5Dest.y -=3;
        state->menu_icon6Dest.y -=3;
        state->chat_iconDest.y -=3;
        state->wheat_iconDest.y -=3;
        state->menu_toolshoverDest.y -=3;
        state->can_farm_signalDest.y -=3;
        state->displaymoneyDest.y -=3;
        state->money_y -=3;
        state->dialogboxDest.y -=3;
        state->seller_emoDest.y -=3;    

        }
    }

    if ((100 <= state->playerDest.x && state->playerDest.x <= state->housewallxbottomDest.x + 100) &&
        (state->housewallxbottomDest.y + state->housewallxbottomDest.height <= state->playerDest.y && state->playerDest.y <= state->housewallxbottomDest.y + state->housewallxbottomDest.height + 50)) {
        
        if(!(380<=state->playerDest.x && state->playerDest.x<=420)){

            moveAllY(state,15);
        }
    }
}

//fix maximum and minimum position for the player
float clamp(float value, float min, float max) {

    if (value < min) {

        return min;

    }

    if (value > max) {
        
        return max;

    }

    return value;
}

//Chating function of the player basically just using distance and detect key press to execute........
void Chatting(GameState *state){
    state->showchatbox = true;
    if(530<=state->playerDest.x && state->playerDest.x <= 760 && 620<=state->playerDest.y &&state->playerDest.y <=730){
        state->showchatbox = false;
    }
    if(IsKeyPressed(KEY_C)&& (state->canspeak)&& !(state->startchat)){
        if(575<=state->playerDest.x && state->playerDest.x <= 595 && 615<=state->playerDest.y &&state->playerDest.y <=650 && state->playerDir == 3){
            state->startchat = true;
            state->sellerSrc.y= 62;
        }
        if(635<=state->playerDest.x && state->playerDest.x <= 660 && 700<=state->playerDest.y &&state->playerDest.y <=715 && state->playerDir == 1){
            state->startchat = true;
            state->sellerSrc.y= 0;
        }
        if(720<=state->playerDest.x && state->playerDest.x <= 735 && 615<=state->playerDest.y &&state->playerDest.y <=650 && state->playerDir == 2){
            state->startchat = true;
            state->sellerSrc.y= 122;
        }
    }
}

//Structure playing menu of game
void ConstructScene(GameState *state) {

    DrawTexturePro(state->grass, state->grassSrc, state->grassDest, state->origin_grass, 0, WHITE);

    for (state->fencey1Dest.y = -10; state->fencey1Dest.y < 1990; state->fencey1Dest.y += 200) {

        DrawTexturePro(state->fence, state->fenceySrc, state->fencey1Dest, state->origin_fencey, 0, WHITE);

    }

    for (state->fencex1Dest.x = -38; state->fencex1Dest.x < 1962; state->fencex1Dest.x += 265) {

        DrawTexturePro(state->fence, state->fencexSrc, state->fencex1Dest, state->origin_fencex, 0, WHITE);

    }

    for (state->fencex2Dest.x = -38; state->fencex2Dest.x < 1962; state->fencex2Dest.x += 265) {

        DrawTexturePro(state->fence, state->fencexSrc, state->fencex2Dest, state->origin_fencex, 0, WHITE);

    }

    for (state->fencey2Dest.y = -10; state->fencey2Dest.y < 1990; state->fencey2Dest.y += 200) {

        DrawTexturePro(state->fence, state->fenceySrc, state->fencey2Dest, state->origin_fencey, 0, WHITE);

    }

    for (state->housewallxtopDest.x = 100; state->housewallxtopDest.x <= 500; state->housewallxtopDest.x += 100) {

        DrawTexturePro(state->house, state->housewallxSrc, state->housewallxtopDest, state->origin_housewallx, 0, WHITE);

    }

    DrawTexturePro(state->house, state->housewallyleftbeginSrc, state->housewallyleftbeginDest, state->origin_housewally, 0, WHITE);

    DrawTexturePro(state->furniture, state->pictureSrc, state->pictureDest, state->origin_picture, 0, WHITE);

    DrawTexturePro(state->furniture, state->clockSrc, state->clockDest, state->origin_clock, 0, WHITE);

    for (state->housetilesDest.y = 175 ; state->housetilesDest.y <= 475; state->housetilesDest.y += 75){

            for(state->housetilesDest.x = 100; state-> housetilesDest.x <= 500; state->housetilesDest.x += 100){
                
                DrawTexturePro(state->house, state->houstilesSrc, state->housetilesDest, state->origin_houstiles, 0, WHITE);
        }

    }
    for (state->housewallymiddleleftDest.y = 113; state->housewallymiddleleftDest.y <= 413; state->housewallymiddleleftDest.y += 75) {

        DrawTexturePro(state->house, state->housewallymiddleSrc, state->housewallymiddleleftDest, state->origin_housewally, 0, WHITE);

    }

    DrawTexturePro(state->house, state->housewallyleftendSrc, state->housewallyleftendDest, state->origin_housewally, 0, WHITE);

    DrawTexturePro(state->furniture, state->matSrc, state->matDest, state->origin_mat, 0, WHITE);
        
    for (state->housewallxbottomDest.x = 100; state->housewallxbottomDest.x <= 500; state->housewallxbottomDest.x += 100) {

        if (200 <= state->housewallxbottomDest.x && state->housewallxbottomDest.x <= 400) {

            if(state->housewallxbottomDest.x == 200){

                DrawTexturePro(state->house, state->windowSrc, state->windowLeftDest, state->origin_window, 0, WHITE);


            }

            else if (state->housewallxbottomDest.x == 400){

                DrawTexturePro(state->house, state->windowSrc, state->windowRightDest, state->origin_window, 0, WHITE);

            }

        }
        else{

            DrawTexturePro(state->house, state->housewallxSrc, state->housewallxbottomDest, state->origin_housewallx, 0, WHITE);

            }
    }

    DrawTexturePro(state->house, state->housewallyrightbeginSrc, state->housewallyrightbeginDest, state->origin_housewally, 0, WHITE);

    for (state->housewallymiddlerightDest.y = 113; state->housewallymiddlerightDest.y <= 413; state->housewallymiddlerightDest.y += 75) {

        DrawTexturePro(state->house, state->housewallymiddleSrc, state->housewallymiddlerightDest, state->origin_housewally, 0, WHITE);

    }

    DrawTexturePro(state->house, state->housewallyrightendSrc, state->housewallyrightendDest, state->origin_housewally, 0, WHITE);

    DrawTexturePro(state->furniture, state->bedSrc, state->bedDest, state->origin_bed, 0, WHITE);

    DrawTexturePro(state->furniture, state->cupboardSrc, state->cupboardDest, state->origin_cupboard, 0, WHITE);

    DrawTexturePro(state->furniture, state->chairSrc, state->chairDest, state->origin_chair, 0, WHITE);

    DrawTexturePro(state->furniture, state->tableSrc, state->tableDest, state->origin_table, 0, WHITE);

    DrawTexturePro(state->furniture, state->potSrc, state->potDest, state->origin_pot, 0, WHITE);

    DrawTexturePro(state->door, state->doorSrc, state->doorDest, state->origin_door, 0, WHITE);

    DrawTexturePro(state->path, state->pathySrc, state->pathyDest, state->origin_pathy, 0, WHITE);

    DrawTexturePro(state->grass, state->farmingareaSrc, state->farmingareaDest, state->origin_farmingarea, 0, WHITE);

    //Draw the digged land after the action is executed
    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if(state->array_land[i][j] == 1){

                Rectangle newDest;

                newDest.x = state->dig_landDest.x+150*j;

                newDest.y = state->dig_landDest.y+150*i;

                newDest.width = state->dig_landDest.width;
                    
                newDest.height = state->dig_landDest.height;

                DrawTexturePro(state->dig_land, state->dig_landSrc, newDest, state->origin_dig_land, 0, WHITE);

            }
        }

    }

    //Draw the waterred land after the action is executed
    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if(state->array_land[i][j] == 1 && state->array_seed[i][j] ==1 && state->array_water[i][j] ==1){

                Rectangle newDest2;

                newDest2.x = state->wateredLandDest.x+150*j;

                newDest2.y = state->wateredLandDest.y+150*i;

                newDest2.width = state->wateredLandDest.width;
                    
                newDest2.height = state->wateredLandDest.height;

                DrawTexturePro(state->watered_land,state->wateredLandSrc,newDest2,state->origin_wateredLand,0, WHITE);

            }
        }

    }

    //Draw the seeded land after the action is executed   
    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if(state->array_land[i][j] == 1 && state->array_seed[i][j] ==1){

                Rectangle newDest1;

                newDest1.x = state->wheatseedDest.x+150*j;

                newDest1.y = state->wheatseedDest.y+150*i;

                newDest1.width = state->wheatseedDest.width;
                    
                newDest1.height = state->wheatseedDest.height;

                DrawTexturePro(state->wheat,state->wheatseedSrc,newDest1,state->origin_wheat_seed,0, WHITE);

            }
        }

    }

    //Draw the first phase growth of seed after period.......   
    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if(state->array_land[i][j] == 1 && state->array_seed[i][j] ==1 && state->array_growth[i][j]>=50 && state->array_growth[i][j] < 100){

                Rectangle newDest2;

                newDest2.x = state->youngwheatDest.x+150*j;

                newDest2.y = state->youngwheatDest.y+150*i;

                newDest2.width = state->youngwheatDest.width;
                    
                newDest2.height = state->youngwheatDest.height;

                DrawTexturePro(state->wheat,state->youngwheatSrc,newDest2,state->origin_youngwheat,0, WHITE);

            }
        }

    }

    //Draw the second phase growth of seed after period.......   
    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if(state->array_land[i][j] == 1 && state->array_seed[i][j] ==1 && state->array_growth[i][j]>=100 && state->array_growth[i][j] < 150){

                Rectangle newDest3;

                newDest3.x = state->young1wheatDest.x+150*j;

                newDest3.y = state->young1wheatDest.y+150*i;

                newDest3.width = state->young1wheatDest.width;
                    
                newDest3.height = state->young1wheatDest.height;

                DrawTexturePro(state->wheat,state->young1wheatSrc,newDest3,state->origin_young1wheat,0, WHITE);

            }
        }

    }

    //Draw the third phase growth of seed after period.......   
    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if(state->array_land[i][j] == 1 && state->array_seed[i][j] ==1 && state->array_growth[i][j]>=150){

                Rectangle newDest4;

                newDest4.x = state->young2wheatDest.x+150*j;

                newDest4.y = state->young2wheatDest.y+150*i;

                newDest4.width = state->young2wheatDest.width;
                    
                newDest4.height = state->young2wheatDest.height;

                DrawTexturePro(state->wheat,state->young2wheatSrc,newDest4,state->origin_young2wheat,0, WHITE);

                state->array_harvested[i][j] = 1 ;

            }
        }

    }

    //making the chatbox is floating 
    state->chatboxDest.y += sin((float)GetTime() * 4.0f) * 0.075f;

    if(state->showchatbox){

        DrawTexturePro(state->chatbox, state->chatboxSrc, state->chatboxDest, state->origin_chatbox, 0, WHITE);

    }

    DrawTexturePro(state->seller, state->sellerSrc, state->sellerDest, state->origin_seller, 0, WHITE);

    DrawTexturePro(state->player, state->playerSrc, state->playerDest, state->origin_player, 0, WHITE);

    if(state->show_can_farm){

        DrawTexturePro(state->signal, state->can_farm_signalSrc, state->can_farm_signalDest, state->origin_can_farm_signal, 0, WHITE);

    }

    DrawTexturePro(state->displaymoney, state->displaymoneySrc, state->displaymoneyDest, state->origin_displaymoney, 0, WHITE);

    DrawText(TextFormat("%d",state->money), state->money_x,state->money_y , 50, BLACK);

    DrawTexturePro(state->tree, state->treeSrc, state->treeDest, state->origin_tree, 0, WHITE);

    DrawTexturePro(state->wheat, state->wheatSrc, state->wheatDest, state->origin_wheat, 0, WHITE);

    DrawText(TextFormat("%d",state->harvestedwheat), state->harvestedwheat_x,state->harvestedwheat_y , 75, BLACK);

    DrawTexturePro(state->menu_tools, state->menu_toolsSrc, state->menu_toolsDest, state->origin_menu_tools, 0, WHITE);

    DrawTexturePro(state->menu_icons, state->menu_icon1Src, state->menu_icon1Dest, state->origin_menu_icon, 0, WHITE);

    DrawTexturePro(state->menu_icons, state->menu_icon2Src, state->menu_icon2Dest, state->origin_menu_icon, 0, WHITE);

    DrawTexturePro(state->menu_icons, state->menu_icon1Src, state->menu_icon3Dest, state->origin_menu_icon, 0, WHITE);

    DrawTexturePro(state->menu_icons, state->menu_icon4Src, state->menu_icon4Dest, state->origin_menu_icon, 0, WHITE);

    DrawTexturePro(state->menu_icons, state->menu_icon5Src, state->menu_icon5Dest, state->origin_menu_icon, 0, WHITE);

    DrawTexturePro(state->menu_icons, state->menu_icon1Src, state->menu_icon6Dest, state->origin_menu_icon, 0, WHITE);

    DrawTexturePro(state->chat_icon, state->chat_iconSrc, state->chat_iconDest, state->origin_chat_icon, 0, WHITE);

    DrawTexturePro(state->wheat_icon, state->wheat_iconSrc, state->wheat_iconDest, state->origin_wheat_icon, 0, WHITE);

    DrawTexturePro(state->menu_toolshover, state->menu_toolshoverSrc, state->menu_toolshoverDest, state->origin_menu_toolshover, 0, WHITE);

    if(!(state->settingbuttonhover)){

        DrawTexturePro(state->settingbutton, state->settingbuttonSrc, state->settingbuttonDest, state->origin_settingbutton, 0, WHITE);

    }
    else{

        DrawTexturePro(state->settingbutton, state->settinghoverbuttonSrc, state->settingbuttonDest, state->origin_settingbutton, 0, WHITE);

    }

    if(state->mouseposition.x>=13 && state->mouseposition.x <= 105 && state->mouseposition.y >= 12 && state->mouseposition.y <= 115){

        state->settingbuttonhover = true;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !(state->startchat)){

            state->mode = SETTING;

        }

    }

    else{

        state->settingbuttonhover = false;

    }

    state -> character_emoDest = (Rectangle){state->seller_emoDest.x-15,state->seller_emoDest.y+10,state->seller_emoDest.width+20,state->seller_emoDest.width+20};

    state -> developerDest = (Rectangle){state->seller_emoDest.x-15,state->seller_emoDest.y+10,state->seller_emoDest.width+20,state->seller_emoDest.width+40};
    
    if(!(state->startchat)){

        //make the maximum amount accepted by the seller keep changing
        state->max_priceallowed = rand() % 50 + 5;

    }

    //to make the game credit only appear once
    if(state->win == 0 && state->money >=1000){
        state->startchat = true;
    }

    if(state->startchat){

        //for showing maximum accept amount by the seller
        printf("\n%d",state->max_priceallowed);

        DrawTexturePro(state->dialogbox, state->dialogboxSrc, state->dialogboxDest, state->origin_dialogbox, 0, WHITE);

        //something before the game credit.......
        if(state->win == 0 && state->money >=1000){

            DrawTexturePro(state->developer, state->developerSrc, state->developerDest, state->origin_seller_emo, 0, WHITE);

            DrawTextEx(state->myfont, "I am the game developer. Congratulation to earn adequate money", (Vector2){state->dialogboxDest.x - 320, state->dialogboxDest.y - 250}, 25, 2, BLACK);

            DrawTextEx(state->myfont, "You have already finished the game!", (Vector2){state->dialogboxDest.x - 320, state->dialogboxDest.y - 200}, 25, 2, BLACK);

            DrawTextEx(state->myfont, "PRESS ENTER to Proceed", (Vector2){state->dialogboxDest.x + 300, state->dialogboxDest.y - 150}, 20, 2, BLACK);

            if(IsKeyPressed(KEY_ENTER)){

                state->mode = ENDING;

            }

        }

        else{
            Chat current_chat = state->chats[state->currentChat];

            if(current_chat.whosay ==1){
                DrawTexturePro(state->character_emo, state->character_emoSrc, state->character_emoDest, state->origin_seller_emo, 0, WHITE);
            }
            else if (current_chat.whosay ==0){
                DrawTexturePro(state->seller_emo, state->seller_emoSrc, state->seller_emoDest, state->origin_seller_emo, 0, WHITE);
            }


            DrawTextEx(state->myfont, current_chat.content, (Vector2){state->dialogboxDest.x - 320,state->dialogboxDest.y - 250 }, 25, 2, BLACK);

            if (current_chat.showoption) {
                if(state->currentChat == 3){
                    state->nowargueprice = 5;
                }
                else if(state->currentChat == 5){
                    state->nowargueprice = 7;
                }
                else if(state->currentChat == 7){
                    state->nowargueprice = 9;
                }
                DrawTextEx(state->myfont, "Press Y to Accept", (Vector2){state->dialogboxDest.x - 320, state->dialogboxDest.y - 200}, 25, 2, BLACK);
                DrawTextEx(state->myfont, "Press N to Reject", (Vector2){state->dialogboxDest.x - 320, state->dialogboxDest.y - 150}, 25, 2, BLACK);
                UpdateDialog(state, 1);
            }else if (current_chat.caninput) {

                SetupCustomTheme();

                static char text[2] = "0"; 
                static int numberOfItems = 0;

                if(state->currentChat==10){

                    DrawTextEx(state->myfont, "Burshels", (Vector2){state->dialogboxDest.x - 200, state->dialogboxDest.y - 160}, 25, 2, BLACK);

                    DrawTextEx(state->myfont, "Input must be Integer and between 0 to 99", (Vector2){state->dialogboxDest.x - 200, state->dialogboxDest.y - 130}, 15, 2, BLACK);

                    if (GuiTextBox((Rectangle){ state->dialogboxDest.x -300, state->dialogboxDest.y -200, 80, 80 }, text, 50, true)) {
                        int len = strlen(text);
                        bool validInput = true;

                        //detect the length of word due to limit maximum 99 for input
                        for (int i = 0; i < len; i++) {
                            if (!isdigit(text[i]) || len > 2) {  
                                text[i] = '\0';
                                break;
                            }
                        }

                        if (validInput && len > 0) {
                            //convert string to integer
                            numberOfItems = atoi(text);
                            state->nowwantsellitems = numberOfItems;
                            if(state->harvestedwheat < state->nowwantsellitems){
                                state->liar =true;
                                state->currentChat=13;
                            }
                            else{
                                state->currentChat++;
                                state-> harvestedwheat -= state->nowwantsellitems;
                                state->money += state->nowargueprice * state->nowwantsellitems;
                            }
                        } else {
                            numberOfItems = 0; // Set to 0 if input is invalid
                            text[0] = '\0'; // Clear the text box if invalid input
                        }
                    }

                    GuiButton((Rectangle){state->dialogboxDest.x + 590, state->dialogboxDest.y - 170, 100, 60}, "Deal");
                }

                else{
                    DrawTextEx(state->myfont, "Coins", (Vector2){state->dialogboxDest.x - 200, state->dialogboxDest.y - 160}, 25, 2, BLACK);

                    DrawTextEx(state->myfont, "Input must be Integer and between 0 to 99", (Vector2){state->dialogboxDest.x - 200, state->dialogboxDest.y - 130}, 15, 2, BLACK);

                    if (GuiTextBox((Rectangle){ state->dialogboxDest.x -300, state->dialogboxDest.y -200, 80, 80 }, text, 50, true)) {
                        int len = strlen(text);
                        bool validInput = true;

                        for (int i = 0; i < len; i++) {
                            if (!isdigit(text[i]) || len > 2) {
                                validInput = false;  // Mark input as invalid
                                break;
                            }
                        }

                        if (validInput && len > 0) {
                            numberOfItems = atoi(text);
                            state->nowargueprice = numberOfItems;
                            if(state->nowargueprice  > state->max_priceallowed){
                                state->liar =true;
                                state->currentChat=13;
                            }
                            else{
                                state->currentChat++;
                            }
                        } else {
                            numberOfItems = 0; 
                            text[0] = '\0'; 
                        }
                    }

                    GuiButton((Rectangle){state->dialogboxDest.x + 590, state->dialogboxDest.y - 170, 100, 60}, "Argue");

                }

            } else {
                DrawTextEx(state->myfont, "PRESS C to continue the chat", (Vector2){state->dialogboxDest.x + 300, state->dialogboxDest.y - 150}, 20, 2, BLACK);
                UpdateDialog(state, 0);
            }
        }
   }

}

//Structure main menu of the game
void DrawMenu(GameState *state){

    static int currentFrame = 0;    
    static float MenuframeTime = 0.1f; 
    static float elapsedTime = 0.0f;    


    elapsedTime += GetFrameTime();

    if (elapsedTime >= MenuframeTime) {

        currentFrame = (currentFrame + 1) % 32; 

        elapsedTime = 0.0f;

    }

    DrawTexturePro(state->menuframes[currentFrame], state->menuframeSrc, state->menuframeDest,state->origin_menuframe,0, WHITE);


    if(!(state->button_hover)){

        DrawTexturePro(state->button, state->buttonSrc, state->buttonDest,state->origin_button,0, WHITE);

    }
    else{

        DrawTexturePro(state->buttonhover, state->buttonhoverSrc, state->buttonhoverDest,state->origin_buttonhover,0, WHITE);

    }


    if(!(state->button1_hover)){

        DrawTexturePro(state->button, state->buttonSrc, state->button2Dest,state->origin_button,0, WHITE);
        
    }
    else{

        DrawTexturePro(state->buttonhover, state->buttonhoverSrc, state->buttonhover2Dest,state->origin_buttonhover,0, WHITE);

    }


    if (state->musicPaused){

        DrawTexturePro(state->menu_sound, state->menu_sound2Src, state->menu_sound2Dest,state->origin_menu_sound,0, WHITE);

    }

    else{

        DrawTexturePro(state->menu_sound, state->menu_soundSrc, state->menu_soundDest,state->origin_menu_sound,0, WHITE);

    }

    DrawTextEx(state->myfont, "Start", (Vector2){ state->buttonDest.x-125, state->buttonDest.y-40 }, 76, 2, BLACK);

    DrawTextEx(state->myfont, "Exit", (Vector2){ state->button2Dest.x-95, state->button2Dest.y-40 }, 76, 2, BLACK);

    state->time = (float)GetTime();

    state->yOffset = sin(state->time * 2.0f) * 20;

    DrawTextEx(state->titlefont, "2D Farmer", (Vector2){ state->button2Dest.x-275, state->button2Dest.y-750+state->yOffset }, 100, 2, BLACK);

    DrawTextEx(state->titlefont, "Simulator", (Vector2){ state->button2Dest.x-275, state->button2Dest.y-600+state->yOffset }, 100, 2, BLACK);

    if((state->mouseposition.x >=540 && state->mouseposition.x<=985 && state->mouseposition.y >=593 && state->mouseposition.y <= 710)||(state->mouseposition.x >=540 && state->mouseposition.x<=985 && state->mouseposition.y >=799 && state->mouseposition.y <= 920)||(state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130)){

        DrawTexturePro(state->hover_cursor, state->hover_cursorSrc, state->hover_cursorDest, state->origin_hover_cursor, 0, WHITE);

    }

    else{

        if(state->mouseposition.x >=25 && state->mouseposition.x<=1475 && state->mouseposition.y >=25 && state->mouseposition.y <= 975){

            DrawTexturePro(state->normal_cursor, state->normal_cursorSrc, state->normal_cursorDest, state->origin_normal_cursor, 0, WHITE);

        }

    }

    if(state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130){

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& !(state->musicPaused)){

            state->musicPaused = true;

        }

        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& state->musicPaused){
             state->musicPaused = false;
        }

    }

    if(state->mouseposition.x >=540 && state->mouseposition.x<=985 && state->mouseposition.y >=593 && state->mouseposition.y <= 710){

        state->button_hover = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

           state->mode = LOADING;
        }

    }

    else{

        state->button_hover = false;

    }


    if(state->mouseposition.x >=540 && state->mouseposition.x<=985 && state->mouseposition.y >=799 && state->mouseposition.y <= 920){

        state->button1_hover = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            CloseWindow();

        }

    }

    else{

        state->button1_hover = false;

    }

}

//save game data
float save_game(float value1,float value2,float value3,float value4,float value5, float value6, float value7, float value8, float value9,int value10[5][6],int value11[5][6],int value12[5][6],int value13[5][6],float value14[5][6],float value15[5][6],float value16, float value17,float value18, float value19,float value20, float value21,float value22, float value23,float value24, float value25,float value26, float value27,float value28, float value29,float value30, float value31,float value32,float value33,float value34,float value35,float value36, float value37,float value38, float value39,int value40,int value41, int value42 ,float value43,float value44,float value45,float value46,int value47) {

    json_object *savedata = json_object_new_object();

    json_object *positionxplayer = json_object_new_double(value1);
    json_object *positionyplayer = json_object_new_double(value2);
    json_object *numberharvestedwheat = json_object_new_double(value3);
    json_object *numberharvestedwheat_x = json_object_new_double(value4);
    json_object *numberharvestedwheat_y = json_object_new_double(value5);
    json_object *harvestedwheaticon_x = json_object_new_double(value6);
    json_object *harvestedwheaticon_y = json_object_new_double(value7);
    json_object *settingicon_x = json_object_new_double(value8);
    json_object *settingicon_y = json_object_new_double(value9);
    json_object *menutools_x = json_object_new_double(value16);
    json_object *menutools_y = json_object_new_double(value17);
    json_object *menuicon1_x = json_object_new_double(value18);
    json_object *menuicon1_y = json_object_new_double(value19);
    json_object *menuicon2_x = json_object_new_double(value20);
    json_object *menuicon2_y = json_object_new_double(value21);
    json_object *menuicon3_x = json_object_new_double(value22);
    json_object *menuicon3_y = json_object_new_double(value23);
    json_object *menuicon4_x = json_object_new_double(value24);
    json_object *menuicon4_y = json_object_new_double(value25);
    json_object *menuicon5_x = json_object_new_double(value26);
    json_object *menuicon5_y = json_object_new_double(value27);
    json_object *menuicon6_x = json_object_new_double(value28);
    json_object *menuicon6_y = json_object_new_double(value29);
    json_object *chat_icon_x = json_object_new_double(value30);
    json_object *chat_icon_y = json_object_new_double(value31);
    json_object *wheat_icon_x = json_object_new_double(value32);
    json_object *wheat_icon_y = json_object_new_double(value33);
    json_object *menutoolshiver_x = json_object_new_double(value34);
    json_object *menutoolshiver_y = json_object_new_double(value35);
    json_object *signalfarm_x = json_object_new_double(value36);
    json_object *signalfarm_y= json_object_new_double(value37);
    json_object *moneydisplay_x = json_object_new_double(value38);
    json_object *moneydisplay_y= json_object_new_double(value39);
    json_object *money_coin= json_object_new_int(value40);
    json_object *money_coin_x= json_object_new_int(value41);
    json_object *money_coin_y=json_object_new_int(value42);
    json_object *dialogbox_x= json_object_new_double(value43);
    json_object *dialogbox_y=json_object_new_double(value44);
    json_object *emote_x= json_object_new_double(value45);
    json_object *emote_y=json_object_new_double(value46);
    json_object *win_situation=json_object_new_int(value47);

    json_object_object_add(savedata, "X position of Player:", positionxplayer);
    json_object_object_add(savedata, "Y position of Player:", positionyplayer);
    json_object_object_add(savedata, "Number of harvested wheat:", numberharvestedwheat);
    json_object_object_add(savedata, "X position of number of harvested wheat:", numberharvestedwheat_x);
    json_object_object_add(savedata, "Y position of number of harvested wheat:", numberharvestedwheat_y);
    json_object_object_add(savedata, "X position of harvested wheat:", harvestedwheaticon_x);
    json_object_object_add(savedata, "Y position of harvested wheat:", harvestedwheaticon_y);
    json_object_object_add(savedata, "X position of setting button:", settingicon_x );
    json_object_object_add(savedata, "Y position of setting button:", settingicon_y );
    json_object_object_add(savedata, "X position of menu tools:", menutools_x );
    json_object_object_add(savedata, "Y position of menu tools:", menutools_y );
    json_object_object_add(savedata, "X position of menu icon1:", menuicon1_x );
    json_object_object_add(savedata, "Y position of menu icon1:", menuicon1_y );
    json_object_object_add(savedata, "X position of menu icon2:", menuicon2_x );
    json_object_object_add(savedata, "Y position of menu icon2:", menuicon2_y );
    json_object_object_add(savedata, "X position of menu icon3:", menuicon3_x );
    json_object_object_add(savedata, "Y position of menu icon3:", menuicon3_y );
    json_object_object_add(savedata, "X position of menu icon4:", menuicon4_x );
    json_object_object_add(savedata, "Y position of menu icon4:", menuicon4_y );
    json_object_object_add(savedata, "X position of menu icon5:", menuicon5_x );
    json_object_object_add(savedata, "Y position of menu icon5:", menuicon5_y );
    json_object_object_add(savedata, "X position of menu icon6:", menuicon6_x );
    json_object_object_add(savedata, "Y position of menu icon6:", menuicon6_y );
    json_object_object_add(savedata, "X position of chat icon:", chat_icon_x );
    json_object_object_add(savedata, "Y position of chat icon:", chat_icon_y );
    json_object_object_add(savedata, "X position of wheat icon:", wheat_icon_x );
    json_object_object_add(savedata, "Y position of wheat icon:", wheat_icon_y );
    json_object_object_add(savedata, "X position of menu tools hover:", menutoolshiver_x );
    json_object_object_add(savedata, "Y position of menu tools hover:", menutoolshiver_y );
    json_object_object_add(savedata, "X position of menu farm signal:", signalfarm_x );
    json_object_object_add(savedata, "Y position of menu farm signal:", signalfarm_y );
    json_object_object_add(savedata, "X position of menu display money:", moneydisplay_x );
    json_object_object_add(savedata, "Y position of menu display money:", moneydisplay_y );
    json_object_object_add(savedata, "Money:", money_coin);
    json_object_object_add(savedata, "X position of money coin:", money_coin_x );
    json_object_object_add(savedata, "Y position of money coin:", money_coin_y );
    json_object_object_add(savedata, "X position of dialog box:", dialogbox_x );
    json_object_object_add(savedata, "Y position of dialog box:", dialogbox_y );
    json_object_object_add(savedata, "X position of dialog emote:", emote_x );
    json_object_object_add(savedata, "Y position of dialog emote:", emote_y );
    json_object_object_add(savedata, "Win:", win_situation);

    json_object *digarray = json_object_new_array();
    json_object *seedarray = json_object_new_array();
    json_object *waterarray = json_object_new_array();
    json_object *harvestarray = json_object_new_array();
    json_object *growtharray = json_object_new_array();
    json_object *waterratearray = json_object_new_array();

    for (int i = 0; i < 5; i++) {

        json_object *rowdigarray = json_object_new_array();
        json_object *rowseedarray = json_object_new_array();
        json_object *rowwaterarray = json_object_new_array();
        json_object *rowharvestarray = json_object_new_array();
        json_object *rowgrowtharray = json_object_new_array();
        json_object *rowwaterratearray = json_object_new_array();

        for (int j = 0; j < 6; j++) {

            json_object *valuedig = json_object_new_int(value10[i][j]);
            json_object *valueseed = json_object_new_int(value11[i][j]);
            json_object *valuewater = json_object_new_int(value12[i][j]);
            json_object *valueharvest = json_object_new_int(value13[i][j]);
            json_object *valuegrowth = json_object_new_double(value14[i][j]);
            json_object *valuewaterrate = json_object_new_double(value15[i][j]);

            json_object_array_add(rowdigarray, valuedig);
            json_object_array_add(rowseedarray, valueseed); 
            json_object_array_add(rowwaterarray, valuewater); 
            json_object_array_add(rowharvestarray, valueharvest); 
            json_object_array_add(rowgrowtharray, valuegrowth); 
            json_object_array_add(rowwaterratearray, valuewaterrate);  
        }

        json_object_array_add(digarray, rowdigarray);
        json_object_array_add(seedarray, rowseedarray);
        json_object_array_add(waterarray, rowwaterarray);
        json_object_array_add(harvestarray, rowharvestarray);
        json_object_array_add(growtharray, rowgrowtharray);
        json_object_array_add(waterratearray, rowwaterratearray);

    }

    json_object_object_add(savedata, "Dig Data", digarray);
    json_object_object_add(savedata, "Seed Data", seedarray);
    json_object_object_add(savedata, "Water Data", waterarray);
    json_object_object_add(savedata, "Harvest Data", harvestarray);
    json_object_object_add(savedata, "Growth Data", growtharray);
    json_object_object_add(savedata, "Water Rate Data", waterratearray);


    FILE *file = fopen(savedfilename, "w");

    if (file == NULL) {

        fprintf(stderr, "Error opening file for writing\n");

        json_object_put(savedata); 

        return 0;
    }

    fprintf(file, "{\n");
    fprintf(file, "  \"X position of Player\": %.2f,\n", value1);
    fprintf(file, "  \"Y position of Player\": %.2f,\n", value2);
    fprintf(file, "  \"Number of harvested wheat\": %.2f,\n", value3);
    fprintf(file, "  \"X position of number of harvested wheat\": %.2f,\n", value4);
    fprintf(file, "  \"Y position of number of harvested wheat\": %.2f,\n", value5);
    fprintf(file, "  \"X position of harvested wheat\": %.2f,\n", value6);
    fprintf(file, "  \"Y position of harvested wheat\": %.2f,\n", value7);
    fprintf(file, "  \"X position of setting button\": %.2f,\n", value8);
    fprintf(file, "  \"Y position of setting button\": %.2f,\n", value9);
    fprintf(file, "  \"X position of menu tools\": %.2f,\n", value16);
    fprintf(file, "  \"Y position of menu tools\": %.2f,\n", value17);
    fprintf(file, "  \"X position of menu icon1\": %.2f,\n", value18);
    fprintf(file, "  \"Y position of menu icon1\": %.2f,\n", value19);
    fprintf(file, "  \"X position of menu icon2\": %.2f,\n", value20);
    fprintf(file, "  \"Y position of menu icon2\": %.2f,\n", value21);
    fprintf(file, "  \"X position of menu icon3\": %.2f,\n", value22);
    fprintf(file, "  \"Y position of menu icon3\": %.2f,\n", value23);
    fprintf(file, "  \"X position of menu icon4\": %.2f,\n", value24);
    fprintf(file, "  \"Y position of menu icon4\": %.2f,\n", value25);
    fprintf(file, "  \"X position of menu icon5\": %.2f,\n", value26);
    fprintf(file, "  \"Y position of menu icon5\": %.2f,\n", value27);
    fprintf(file, "  \"X position of menu icon6\": %.2f,\n", value28);
    fprintf(file, "  \"Y position of menu icon6\": %.2f,\n", value29);
    fprintf(file, "  \"X position of chat icon\": %.2f,\n", value30);
    fprintf(file, "  \"Y position of chat icon\": %.2f,\n", value31);
    fprintf(file, "  \"X position of wheat icon\": %.2f,\n", value32);
    fprintf(file, "  \"Y position of wheat icon\": %.2f,\n", value33);
    fprintf(file, "  \"X position of menu tools hover\": %.2f,\n", value34);
    fprintf(file, "  \"Y position of menu tools hover\": %.2f,\n", value35);
    fprintf(file, "  \"X position of menu farm signal\": %.2f,\n", value36);
    fprintf(file, "  \"Y position of menu farm signal\": %.2f,\n", value37);
    fprintf(file, "  \"X position of menu display money\": %.2f,\n", value38);
    fprintf(file, "  \"Y position of menu display money\": %.2f,\n", value39);
    fprintf(file, "  \"Money\": %d,\n", value40);
    fprintf(file, "  \"X position of money coin\": %d,\n", value41);
    fprintf(file, "  \"Y position of money coin\": %d,\n", value42);
    fprintf(file, "  \"X position of dialog box\": %.2f,\n", value43);
    fprintf(file, "  \"Y position of dialog box\": %.2f,\n", value44);
    fprintf(file, "  \"X position of dialog emote\": %.2f,\n", value45);
    fprintf(file, "  \"Y position of dialog emote\": %.2f,\n", value46);
    fprintf(file, "  \"Win\": %d,\n", value47);


    // Dig Array
    fprintf(file, "  \"Dig Array\": [\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "    [");
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%i", value10[i][j]);
            if (j < 5) fprintf(file, ", ");
        }
        fprintf(file, "]");
        if (i < 4) fprintf(file, ",\n"); 
    }
    fprintf(file, "\n  ],\n");

    // Seed Array
    fprintf(file, "  \"Seed Array\": [\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "    [");
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%i", value11[i][j]);
            if (j < 5) fprintf(file, ", ");
        }
        fprintf(file, "]");
        if (i < 4) fprintf(file, ",\n");
    }
    fprintf(file, "\n  ],\n");

    // Water Array
    fprintf(file, "  \"Water Array\": [\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "    [");
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%i", value12[i][j]);
            if (j < 5) fprintf(file, ", ");
        }
        fprintf(file, "]");
        if (i < 4) fprintf(file, ",\n");
    }
    fprintf(file, "\n  ],\n");

    // Harvest Array
    fprintf(file, "  \"Harvest Array\": [\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "    [");
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%i", value13[i][j]);
            if (j < 5) fprintf(file, ", ");
        }
        fprintf(file, "]");
        if (i < 4) fprintf(file, ",\n");
    }
    fprintf(file, "\n  ],\n");

    // Growth Rate Array
    fprintf(file, "  \"Growth Rate Array\": [\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "    [");
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%.2f", value14[i][j]);
            if (j < 5) fprintf(file, ", ");
        }
        fprintf(file, "]");
        if (i < 4) fprintf(file, ",\n");
    }
    fprintf(file, "\n  ],\n");

    // Water Rate Array
    fprintf(file, "  \"Water Rate Array\": [\n");
    for (int i = 0; i < 5; i++) {
        fprintf(file, "    [");
        for (int j = 0; j < 6; j++) {
            fprintf(file, "%.2f", value15[i][j]);
            if (j < 5) fprintf(file, ", ");
        }
        fprintf(file, "]");
        if (i < 4) fprintf(file, ",\n");
    }
    fprintf(file, "\n  ]\n"); 

    fprintf(file, "}\n"); 

    fclose(file);


    json_object_put(savedata);


    return 1;
}

//Structure setting menu
void DrawSettingMenu(GameState *state){

    DrawTexturePro(state->settingmenubackground, state->settingmenubackgroundSrc, state->settingmenubackgroundDest, state->origin_settingmenubackground, 0, WHITE);

    DrawTexturePro(state->settingmenu, state->settingmenuSrc, state->settingmenuDest, state->origin_settingmenu, 0, WHITE);

    if(!(state->closebutton_hover)){

        DrawTexturePro(state->closesettingbutton, state->closesettingbuttonSrc, state->closesettingbuttonDest, state->origin_closesettingbutton, 0, WHITE);

    }
    else{

        DrawTexturePro(state->closesettingbutton, state->closesettingbutton1Src, state->closesettingbuttonDest, state->origin_closesettingbutton, 0, WHITE);
    }



    if(!(state->buttonhover3)){
        DrawTexturePro(state->button, state->buttonSrc, state->button3Dest,state->origin_button,0, WHITE);
    }
    else{
        DrawTexturePro(state->button, state->buttonhoverSrc, state->button3Dest,state->origin_button,0, WHITE);
    }

    if(!(state->buttonhover4)){
        DrawTexturePro(state->button, state->buttonSrc, state->button4Dest,state->origin_button,0, WHITE);
    }
    else{
        DrawTexturePro(state->button, state->buttonhoverSrc, state->button4Dest,state->origin_button,0, WHITE);
    }

    if(!(state->buttonhover5)){

        DrawTexturePro(state->button, state->buttonSrc, state->button5Dest,state->origin_button,0, WHITE);

    }
    else{

        DrawTexturePro(state->button, state->buttonhoverSrc, state->button5Dest,state->origin_button,0, WHITE);

    }

    DrawTextEx(state->myfont, "How To Play", (Vector2){ state->button3Dest.x-180, state->button3Dest.y-30 }, 50, 2, BLACK);

    DrawTextEx(state->myfont, "Save Game", (Vector2){ state->button4Dest.x-180, state->button4Dest.y-30 }, 50, 2, BLACK);
    
    DrawTextEx(state->myfont, "Back To Main", (Vector2){ state->button5Dest.x-180, state->button5Dest.y-30 }, 50, 2, BLACK);

    if(state->showpop){

        
        DrawTexturePro(state->savebackground, state->savebackgroundSrc, state->savebackgroundDest,state->origin_savebackground,0, WHITE);

        DrawTexturePro(state->settinggoodbyepicture, state->settinggoodbyepictureSrc, state->settinggoodbyepictureDest,state->origin_settinggoodbyepicture,0, WHITE);

        DrawText("See You ", 830, 240, 130, RAYWHITE);
        DrawText("Next Time!", 780, 440, 130, RAYWHITE);
        DrawText("Successfully saved  game", 280, 700, 80, RAYWHITE);
        DrawText("Press SPACE to", 440, 800, 80, RAYWHITE);
        DrawText("close this message.", 420, 900, 80, RAYWHITE);

        if (IsKeyPressed(KEY_SPACE)){

            state->showpop = false;

        }
        
    }

    if (state->musicPaused){

        DrawTexturePro(state->menu_sound, state->menu_sound2Src, state->menu_sound2Dest,state->origin_menu_sound,0, WHITE);

    }

    else{

        DrawTexturePro(state->menu_sound, state->menu_soundSrc, state->menu_soundDest,state->origin_menu_sound,0, WHITE);

    }

    if((state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130)||((state->mouseposition.x >=1012 && state->mouseposition.x<=1097 && state->mouseposition.y >=102 && state->mouseposition.y <= 200)||(state->mouseposition.x >=537 && state->mouseposition.x<=989 && state->mouseposition.y >=295 && state->mouseposition.y <= 423)||(state->mouseposition.x >=537 && state->mouseposition.x<=989 && state->mouseposition.y >=494 && state->mouseposition.y <= 624)||(state->mouseposition.x >=537 && state->mouseposition.x<=989 && state->mouseposition.y >=695 && state->mouseposition.y <= 824))&&!(state->showpop)){

        DrawTexturePro(state->hover_cursor, state->hover_cursorSrc, state->hover_cursorDest, state->origin_hover_cursor, 0, WHITE);

    }

    else{

        if(state->mouseposition.x >=25 && state->mouseposition.x<=1475 && state->mouseposition.y >=25 && state->mouseposition.y <= 975){

            DrawTexturePro(state->normal_cursor, state->normal_cursorSrc, state->normal_cursorDest, state->origin_normal_cursor, 0, WHITE);

        }
    }

    if(state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130){

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& !(state->musicPaused)){

            state->musicPaused = true;

        }

        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state->musicPaused){

            state->musicPaused = false;

        }

    }

    if(state->mouseposition.x >=537 && state->mouseposition.x<=989 && state->mouseposition.y >=295 && state->mouseposition.y <= 423){

        state->buttonhover3 = true;

            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state->mode=INSTRUCTION;

        }

    }
    else{

        state->buttonhover3 = false;

    }

    if(state->mouseposition.x >=537 && state->mouseposition.x<=989 && state->mouseposition.y >=494 && state->mouseposition.y <= 624){

        state->buttonhover4 = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            save_game(state->playerDest.x,state->playerDest.y,state->harvestedwheat,state->harvestedwheat_x,state->harvestedwheat_y,state->wheatDest.x,state->wheatDest.y,state->settingbuttonDest.x,state->settingbuttonDest.y,state->array_land,state->array_seed,state->array_water,state->array_harvested,state->array_growth,state->array_watercontent,state->menu_toolsDest.x,state->menu_toolsDest.y,state->menu_icon1Dest.x,state->menu_icon1Dest.y,state->menu_icon2Dest.x,state->menu_icon2Dest.y,state->menu_icon3Dest.x,state->menu_icon3Dest.y,state->menu_icon4Dest.x,state->menu_icon4Dest.y,state->menu_icon5Dest.x,state->menu_icon5Dest.y,state->menu_icon6Dest.x,state->menu_icon6Dest.y,state->chat_iconDest.x,state->chat_iconDest.y,state->wheat_iconDest.x,state->wheat_iconDest.y,state->menu_toolshoverDest.x,state->menu_toolshoverDest.y,state->can_farm_signalDest.x,state->can_farm_signalDest.y,state->displaymoneyDest.x,state->displaymoneyDest.y,state->money,state->money_x,state->money_y,state->dialogboxDest.x,state->dialogboxDest.y,state->seller_emoDest.x,state->seller_emoDest.y,state->win);

            if(save_game(state->playerDest.x,state->playerDest.y,state->harvestedwheat,state->harvestedwheat_x,state->harvestedwheat_y,state->wheatDest.x,state->wheatDest.y,state->settingbuttonDest.x,state->settingbuttonDest.y,state->array_land,state->array_seed,state->array_water,state->array_harvested,state->array_growth,state->array_watercontent,state->menu_toolsDest.x,state->menu_toolsDest.y,state->menu_icon1Dest.x,state->menu_icon1Dest.y,state->menu_icon2Dest.x,state->menu_icon2Dest.y,state->menu_icon3Dest.x,state->menu_icon3Dest.y,state->menu_icon4Dest.x,state->menu_icon4Dest.y,state->menu_icon5Dest.x,state->menu_icon5Dest.y,state->menu_icon6Dest.x,state->menu_icon6Dest.y,state->chat_iconDest.x,state->chat_iconDest.y,state->wheat_iconDest.x,state->wheat_iconDest.y,state->menu_toolshoverDest.x,state->menu_toolshoverDest.y,state->can_farm_signalDest.x,state->can_farm_signalDest.y,state->displaymoneyDest.x,state->displaymoneyDest.y,state->money,state->money_x,state->money_y,state->dialogboxDest.x,state->dialogboxDest.y,state->seller_emoDest.x,state->seller_emoDest.y,state->win)>0){

                state->showpop = true;

            }

        }
        
    }
    else{

        state->buttonhover4 = false;

    }

    if(state->mouseposition.x >=537 && state->mouseposition.x<=989 && state->mouseposition.y >=695 && state->mouseposition.y <= 824){

        state->buttonhover5 = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state->mode=MENU;

        }
    }
    else{

        state->buttonhover5 = false;

    }

    if(state->mouseposition.x >=1012 && state->mouseposition.x<=1097 && state->mouseposition.y >=102 && state->mouseposition.y <= 200){

        state->closebutton_hover = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state->mode=PLAYING;

        }

    }
    else{
        state->closebutton_hover = false;
    }

}

//Load Game Data
void load_game_data(const char* referfile,GameState *state ){

    FILE *file;
    long file_size;
    char *json_string;
    struct json_object *parsed_json;

    // Open the JSON file
    file = fopen(referfile, "r");
    if (!file) {
        perror("Could not open file");

    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the JSON string
    json_string = malloc(file_size + 1);
    if (!json_string) {
        perror("Could not allocate memory");
        fclose(file);

    }

    // Read the file into the string
    fread(json_string, 1, file_size, file);
    json_string[file_size] = '\0'; // Null-terminate the string

    // Close the file
    fclose(file);

    // Parse the JSON string
    parsed_json = json_tokener_parse(json_string);
    if (!parsed_json) {
        fprintf(stderr, "Failed to parse JSON\n");
        free(json_string);

    }

    // Accessing scalar values
    struct json_object *x_pos_player, *y_pos_player, *harvested_wheat_number,*harvested_wheat_number_x,*harvested_wheat_number_y,*harvested_wheat_x,*harvested_wheat_y,*settingbutton_x,*settingbutton_y,*menutools_x,*menutools_y,*menuicon1_x,*menuicon1_y,*menuicon2_x,*menuicon2_y,*menuicon3_x,*menuicon3_y,*menuicon4_x,*menuicon4_y,*menuicon5_x,*menuicon5_y,*menuicon6_x,*menuicon6_y,*chaticon_x,*chaticon_y,*wheaticon_x,*wheaticon_y,*menutoolshover_x,*menutoolshover_y,*showfarmsignal_x,*showfarmsignal_y,*moneydisplaymenu_x,*moneydisplaymenu_y,*number_money,*money_coin_x,*money_coin_y,*dialogbox_x,*dialogbox_y,*emote_x,*emote_y,*win_situation;
    json_object_object_get_ex(parsed_json, "X position of Player", &x_pos_player);
    json_object_object_get_ex(parsed_json, "Y position of Player", &y_pos_player);
    json_object_object_get_ex(parsed_json, "Number of harvested wheat", &harvested_wheat_number);
    json_object_object_get_ex(parsed_json, "X position of number of harvested wheat", &harvested_wheat_number_x);
    json_object_object_get_ex(parsed_json, "Y position of number of harvested wheat", &harvested_wheat_number_y);
    json_object_object_get_ex(parsed_json, "X position of harvested wheat", &harvested_wheat_x);
    json_object_object_get_ex(parsed_json, "Y position of harvested wheat", &harvested_wheat_y);
    json_object_object_get_ex(parsed_json, "X position of setting button", &settingbutton_x);
    json_object_object_get_ex(parsed_json, "Y position of setting button", &settingbutton_y);
    json_object_object_get_ex(parsed_json, "X position of menu tools", &menutools_x);
    json_object_object_get_ex(parsed_json, "Y position of menu tools", &menutools_y);
    json_object_object_get_ex(parsed_json, "X position of menu icon1", &menuicon1_x);
    json_object_object_get_ex(parsed_json, "Y position of menu icon1", &menuicon1_y);
    json_object_object_get_ex(parsed_json, "X position of menu icon2", &menuicon2_x);
    json_object_object_get_ex(parsed_json, "Y position of menu icon2", &menuicon2_y);
    json_object_object_get_ex(parsed_json, "X position of menu icon3", &menuicon3_x);
    json_object_object_get_ex(parsed_json, "Y position of menu icon3", &menuicon3_y);
    json_object_object_get_ex(parsed_json, "X position of menu icon4", &menuicon4_x);
    json_object_object_get_ex(parsed_json, "Y position of menu icon4", &menuicon4_y);
    json_object_object_get_ex(parsed_json, "X position of menu icon5", &menuicon5_x);
    json_object_object_get_ex(parsed_json, "Y position of menu icon5", &menuicon5_y);
    json_object_object_get_ex(parsed_json, "X position of menu icon6", &menuicon6_x);
    json_object_object_get_ex(parsed_json, "Y position of menu icon6", &menuicon6_y);
    json_object_object_get_ex(parsed_json, "X position of chat icon", &chaticon_x);
    json_object_object_get_ex(parsed_json, "Y position of chat icon", &chaticon_y);
    json_object_object_get_ex(parsed_json, "X position of wheat icon", &wheaticon_x);
    json_object_object_get_ex(parsed_json, "Y position of wheat icon", &wheaticon_y);
    json_object_object_get_ex(parsed_json, "X position of menu tools hover", &menutoolshover_x);
    json_object_object_get_ex(parsed_json, "Y position of menu tools hover", &menutoolshover_y);
    json_object_object_get_ex(parsed_json, "X position of menu farm signal", &showfarmsignal_x);
    json_object_object_get_ex(parsed_json, "Y position of menu farm signal", &showfarmsignal_y);
    json_object_object_get_ex(parsed_json, "X position of menu display money", &moneydisplaymenu_x);
    json_object_object_get_ex(parsed_json, "Y position of menu display money", &moneydisplaymenu_y);
    json_object_object_get_ex(parsed_json, "Money", &number_money);
    json_object_object_get_ex(parsed_json, "X position of money coin", &money_coin_x);
    json_object_object_get_ex(parsed_json, "Y position of money coin", &money_coin_y);
    json_object_object_get_ex(parsed_json, "X position of dialog box", &dialogbox_x);
    json_object_object_get_ex(parsed_json, "Y position of dialog box", &dialogbox_y);
    json_object_object_get_ex(parsed_json, "X position of dialog emote", &emote_x);
    json_object_object_get_ex(parsed_json, "Y position of dialog emote", &emote_y);
    json_object_object_get_ex(parsed_json, "Win", &win_situation);

    state->playerDest.x = json_object_get_double(x_pos_player);
    state->playerDest.y = json_object_get_double(y_pos_player);
    state->harvestedwheat = json_object_get_int(harvested_wheat_number);
    state->harvestedwheat_x = json_object_get_double(harvested_wheat_number_x);
    state->harvestedwheat_y = json_object_get_double(harvested_wheat_number_y);
    state->wheatDest.x = json_object_get_double(harvested_wheat_x);
    state->wheatDest.y = json_object_get_double(harvested_wheat_y);
    state->settingbuttonDest.x= json_object_get_double(settingbutton_x);
    state->settingbuttonDest.y = json_object_get_double(settingbutton_y);
    state->menu_toolsDest.x= json_object_get_double(menutools_x);
    state->menu_toolsDest.y = json_object_get_double(menutools_y);
    state->menu_icon1Dest.x= json_object_get_double(menuicon1_x);
    state->menu_icon1Dest.y = json_object_get_double(menuicon1_y);
    state->menu_icon2Dest.x= json_object_get_double(menuicon2_x);
    state->menu_icon2Dest.y = json_object_get_double(menuicon2_y);
    state->menu_icon3Dest.x= json_object_get_double(menuicon3_x);
    state->menu_icon3Dest.y = json_object_get_double(menuicon3_y);
    state->menu_icon4Dest.x= json_object_get_double(menuicon4_x);
    state->menu_icon4Dest.y = json_object_get_double(menuicon4_y);
    state->menu_icon5Dest.x= json_object_get_double(menuicon5_x);
    state->menu_icon5Dest.y = json_object_get_double(menuicon5_y);
    state->menu_icon6Dest.x= json_object_get_double(menuicon6_x);
    state->menu_icon6Dest.y = json_object_get_double(menuicon6_y);
    state->chat_iconDest.x= json_object_get_double(chaticon_x);
    state->chat_iconDest.y = json_object_get_double(chaticon_y);
    state->wheat_iconDest.x= json_object_get_double(wheaticon_x);
    state->wheat_iconDest.y = json_object_get_double(wheaticon_y);
    state->menu_toolshoverDest.x= json_object_get_double(menutoolshover_x);
    state->menu_toolshoverDest.y = json_object_get_double(menutoolshover_y);
    state->can_farm_signalDest.x= json_object_get_double(showfarmsignal_x);
    state->can_farm_signalDest.y = json_object_get_double(showfarmsignal_y);
    state->displaymoneyDest.x= json_object_get_double(moneydisplaymenu_x);
    state->displaymoneyDest.y = json_object_get_double(moneydisplaymenu_y);
    state->money= json_object_get_int(number_money);
    state->money_x= json_object_get_int(money_coin_x);
    state->money_y= json_object_get_int(money_coin_y);
    state->dialogboxDest.x= json_object_get_double(dialogbox_x);
    state->dialogboxDest.y = json_object_get_double(dialogbox_y);
    state->seller_emoDest.x= json_object_get_double(emote_x);
    state->seller_emoDest.y= json_object_get_double(emote_y);
    state->win= json_object_get_int(win_situation);
    

    // Accessing scalar values
    struct json_object *dig_array, *seed_array, *water_array,*harvest_array, *growth_rate_array, *water_rate_array;

    json_object_object_get_ex(parsed_json, "Dig Array", &dig_array);
    json_object_object_get_ex(parsed_json, "Seed Array", &seed_array);
    json_object_object_get_ex(parsed_json, "Water Array", &water_array);
    json_object_object_get_ex(parsed_json, "Harvest Array", &harvest_array);
    json_object_object_get_ex(parsed_json, "Growth Rate Array", &growth_rate_array);
    json_object_object_get_ex(parsed_json, "Water Rate Array", &water_rate_array);

    // Fill the arrays in the state struct
    for (int i = 0; i < 5; i++) {

        struct json_object *dig_row = json_object_array_get_idx(dig_array, i);
        struct json_object *seed_row = json_object_array_get_idx(seed_array, i);
        struct json_object *water_row = json_object_array_get_idx(water_array, i);
        struct json_object *harvest_row = json_object_array_get_idx(harvest_array, i);
        struct json_object *growth_row = json_object_array_get_idx(growth_rate_array, i);
        struct json_object *water_row_rate = json_object_array_get_idx(water_rate_array, i);

        for (int j = 0; j < 6; j++) {

            struct json_object *dig_value = json_object_array_get_idx(dig_row, j);
            struct json_object *seed_value = json_object_array_get_idx(seed_row, j);
            struct json_object *water_value = json_object_array_get_idx(water_row, j);
            struct json_object *harvest_value = json_object_array_get_idx(harvest_row, j);
            struct json_object *growth_value = json_object_array_get_idx(growth_row, j);
            struct json_object *water_value_rate = json_object_array_get_idx(water_row_rate, j);

            state->array_land[i][j] = json_object_get_int(dig_value);
            state->array_seed[i][j] = json_object_get_int(seed_value);
            state->array_water[i][j] = json_object_get_int(water_value);
            state->array_harvested[i][j] = json_object_get_int(harvest_value);
            state->array_growth[i][j] = json_object_get_double(growth_value);
            state->array_watercontent[i][j] = json_object_get_double(water_value_rate);
        }
    }

    // Clean up
    json_object_put(parsed_json); 
    free(json_string); 

}

//Structure loading menu
void DrawLoadingMenu(GameState *state){

    static int currentFrame = 0;    
    static float MenuframeTime = 0.1f; 
    static float elapsedTime = 0.0f;    
    static int totalFrames = 10;

    DrawTexturePro(state->loadingbackground, state->loadingbackgroundSrc, state->loadingbackgroundDest,state->origin_loadingbackground,0, WHITE);

    elapsedTime += GetFrameTime();

    if (elapsedTime >= MenuframeTime) {

        currentFrame = (currentFrame + 1) % 52; 

        elapsedTime = 0.0f;

    }

    DrawTexturePro(state->loadinganimationframes[currentFrame], state->loadinganimationSrc, state->loadinganimationDest,state->origin_loadinganimation,0, WHITE);

    
    if(!(state->closebutton_hover)){

        DrawTexturePro(state->closesettingbutton, state->closesettingbuttonSrc, state->closesettingbutton2Dest, state->origin_closesettingbutton, 0, WHITE);

    }
    else{

        DrawTexturePro(state->closesettingbutton, state->closesettingbutton1Src, state->closesettingbutton2Dest, state->origin_closesettingbutton, 0, WHITE);
    }

    if(!(state->new_game)){

        DrawTexturePro(state->loadingbutton, state->loadingbuttonSrc, state->loadingbuttonDest, state->origin_loadingbutton, 0, WHITE);

    }
    else{

        DrawTexturePro(state->loadingbutton, state->loadingbutton2Src, state->loadingbutton2Dest, state->origin_loadingbutton, 0, WHITE);

    }

    if(!(state->load_game)){

        DrawTexturePro(state->loadingbutton, state->loadingbuttonSrc, state->loadingbutton3Dest, state->origin_loadingbutton, 0, WHITE);

    }
    else{

        DrawTexturePro(state->loadingbutton, state->loadingbutton2Src, state->loadingbutton4Dest, state->origin_loadingbutton, 0, WHITE);

    }


    DrawTextEx(state->myfont, "New Game", (Vector2){ state->loadingbuttonDest.x+70, state->loadingbuttonDest.y-30 }, 55, 2, BLACK);

    DrawTextEx(state->myfont, "Load Game", (Vector2){ state->loadingbuttonDest.x+70, state->loadingbuttonDest.y+110 }, 55, 2, BLACK);


    if (state->musicPaused){

        DrawTexturePro(state->menu_sound, state->menu_sound2Src, state->menu_sound2Dest,state->origin_menu_sound,0, WHITE);

    }

    else{

        DrawTexturePro(state->menu_sound, state->menu_soundSrc, state->menu_soundDest,state->origin_menu_sound,0, WHITE);

    }


    if((state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130)||(state->mouseposition.x >=1372 && state->mouseposition.x<=1469 && state->mouseposition.y >=62 && state->mouseposition.y <= 146)||(state->mouseposition.x >=1076 && state->mouseposition.x<=1184 && state->mouseposition.y >=239 && state->mouseposition.y <= 300)||(state->mouseposition.x >=1076 && state->mouseposition.x<=1184 && state->mouseposition.y >=378 && state->mouseposition.y <= 441)){

        DrawTexturePro(state->hover_cursor, state->hover_cursorSrc, state->hover_cursorDest, state->origin_hover_cursor, 0, WHITE);

    }

    else{

        if(state->mouseposition.x >=25 && state->mouseposition.x<=1475 && state->mouseposition.y >=25 && state->mouseposition.y <= 975){

            DrawTexturePro(state->normal_cursor, state->normal_cursorSrc, state->normal_cursorDest, state->origin_normal_cursor, 0, WHITE);

        }
    }

    if(state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130){

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& !(state->musicPaused)){

            state->musicPaused = true;

        }

        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state->musicPaused){

            state->musicPaused = false;

        }

    }

    if(state->mouseposition.x >=1372 && state->mouseposition.x<=1469 && state->mouseposition.y >=62 && state->mouseposition.y <= 146){

        state->closebutton_hover = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state->mode=MENU;

        }

    }
    else{
        state->closebutton_hover = false;
    }

    if(state->mouseposition.x >=1076 && state->mouseposition.x<=1184 && state->mouseposition.y >=239 && state->mouseposition.y <= 300){

        state->new_game = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            load_game_data(rawfilename,state);

            state->mode=PLAYING;

        }

    }
    else{
        state->new_game = false;
    }

    if(state->mouseposition.x >=1076 && state->mouseposition.x<=1184 && state->mouseposition.y >=378 && state->mouseposition.y <= 441){

        state->load_game = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            load_game_data(savedfilename,state);

            state->mode=PLAYING;

        }

    }
    else{
        state->load_game = false;
    }


}

//Structure instruction menu
void DrawInstructionMenu(GameState *state){

    DrawTexturePro(state->settingmenubackground, state->settingmenubackgroundSrc, state->settingmenubackgroundDest, state->origin_settingmenubackground, 0, WHITE);

    DrawTexturePro(state->loadingmenu, state->loadingmenuSrc, state->loadingmenuDest, state->origin_loadingmenu, 0, WHITE);

    DrawTextEx(state->myfont, "Control", (Vector2){ 560,125 }, 60, 2, BLACK);

    DrawTextEx(state->myfont, "Right Key : Move Right", (Vector2){ 420,215 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "Left Key : Move Left", (Vector2){ 420,255 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "Down Key : Move Down", (Vector2){ 420,295 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "Up Key : Move Up", (Vector2){ 420,335 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "Enter Key : Open Setting Menu", (Vector2){ 420,375 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "Q Key : Mute/Unmute The Sound", (Vector2){ 420,415 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "Z Key : Move Left for item slot", (Vector2){ 420,455 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "X Key : Move Right for item slot", (Vector2){ 420,495 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "C Key : Activate selected item slot", (Vector2){ 420,535 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "How To Win", (Vector2){ 560,585 }, 60, 2, BLACK);

    DrawTextEx(state->myfont, "In this game, you'll step into the ", (Vector2){ 420,675 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "role of a farmer, cultivating crops ", (Vector2){ 420,715 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "and earning money to achieve your", (Vector2){ 420,755 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "goals. Embark on your farming", (Vector2){ 420,795 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "adventure and enjoy the journey", (Vector2){ 420,835 }, 30, 2, GRAY);

    DrawTextEx(state->myfont, "ahead! Have fun!", (Vector2){ 420,875 }, 30, 2, GRAY);


    if(!(state->closebutton_hover)){

        DrawTexturePro(state->closesettingbutton, state->closesettingbuttonSrc, state->closesettingbuttonDest, state->origin_closesettingbutton, 0, WHITE);

    }
    else{

        DrawTexturePro(state->closesettingbutton, state->closesettingbutton1Src, state->closesettingbuttonDest, state->origin_closesettingbutton, 0, WHITE);
    }


    if (state->musicPaused){

        DrawTexturePro(state->menu_sound, state->menu_sound2Src, state->menu_sound2Dest,state->origin_menu_sound,0, WHITE);

    }

    else{

        DrawTexturePro(state->menu_sound, state->menu_soundSrc, state->menu_soundDest,state->origin_menu_sound,0, WHITE);

    }

    if((state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130)||((state->mouseposition.x >=1012 && state->mouseposition.x<=1097 && state->mouseposition.y >=102 && state->mouseposition.y <= 200))){

        DrawTexturePro(state->hover_cursor, state->hover_cursorSrc, state->hover_cursorDest, state->origin_hover_cursor, 0, WHITE);

    }

    else{

        if(state->mouseposition.x >=25 && state->mouseposition.x<=1475 && state->mouseposition.y >=25 && state->mouseposition.y <= 975){

            DrawTexturePro(state->normal_cursor, state->normal_cursorSrc, state->normal_cursorDest, state->origin_normal_cursor, 0, WHITE);

        }
    }

    if(state->mouseposition.x >=34 && state->mouseposition.x<=125 && state->mouseposition.y >=34 && state->mouseposition.y <= 130){

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&& !(state->musicPaused)){

            state->musicPaused = true;

        }

        else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state->musicPaused){

            state->musicPaused = false;

        }

    }

    if(state->mouseposition.x >=1012 && state->mouseposition.x<=1097 && state->mouseposition.y >=102 && state->mouseposition.y <= 200){

        state->closebutton_hover = true;

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){

            state->mode= SETTING;

        }

    }
    else{
        state->closebutton_hover = false;
    }

}

//Structure ending menu
void DrawEndingMenu(GameState *state){

    int numCredits = 0;


    while (credits[numCredits] != NULL){
        numCredits++;  
    } 

    
    static float scrollY = 0;
    
    if (scrollY + numCredits * 40 < 0) {
        scrollY = screenHeight;
        state->frequency++;
    }

    float scrollSpeed = 50.0f;
    scrollY -= scrollSpeed * GetFrameTime();

    ClearBackground(BLACK);

    for (int i = 0; i < numCredits; i++) {
        float posY = scrollY + i * 40;
        if (posY > -20 && posY < screenHeight + 20) {  
            DrawTextEx(state->creditfont, credits[i], (Vector2){ 20, posY }, 20, 2, RAYWHITE);
        }
    }

    static int currentFrame = 0;    
    static float MenuframeTime = 0.1f; 
    static float elapsedTime = 0.0f;    

    elapsedTime += GetFrameTime();

    if (elapsedTime >= MenuframeTime) {

        currentFrame = (currentFrame + 1) % 127; 

        elapsedTime = 0.0f;

    }

    DrawTexturePro(state->endingframes[currentFrame], state->endingframesSrc, state->endingframesDest,state->origin_endingframes,0, WHITE);

    if (state->frequency > 0) {
        DrawTextEx(state->creditfont, "Press Enter to Go Back to Main", (Vector2){ 875, 900 }, 30, 2, RAYWHITE);
        if (IsKeyPressed(KEY_ENTER)) {

            state->win = 1;

            state->startchat = false;

            save_game(state->playerDest.x,state->playerDest.y,state->harvestedwheat,state->harvestedwheat_x,state->harvestedwheat_y,state->wheatDest.x,state->wheatDest.y,state->settingbuttonDest.x,state->settingbuttonDest.y,state->array_land,state->array_seed,state->array_water,state->array_harvested,state->array_growth,state->array_watercontent,state->menu_toolsDest.x,state->menu_toolsDest.y,state->menu_icon1Dest.x,state->menu_icon1Dest.y,state->menu_icon2Dest.x,state->menu_icon2Dest.y,state->menu_icon3Dest.x,state->menu_icon3Dest.y,state->menu_icon4Dest.x,state->menu_icon4Dest.y,state->menu_icon5Dest.x,state->menu_icon5Dest.y,state->menu_icon6Dest.x,state->menu_icon6Dest.y,state->chat_iconDest.x,state->chat_iconDest.y,state->wheat_iconDest.x,state->wheat_iconDest.y,state->menu_toolshoverDest.x,state->menu_toolshoverDest.y,state->can_farm_signalDest.x,state->can_farm_signalDest.y,state->displaymoneyDest.x,state->displaymoneyDest.y,state->money,state->money_x,state->money_y,state->dialogboxDest.x,state->dialogboxDest.y,state->seller_emoDest.x,state->seller_emoDest.y,state->win);

            state->mode= MENU;
            
        }
    }
    if(state->mouseposition.x >=25 && state->mouseposition.x<=1475 && state->mouseposition.y >=25 && state->mouseposition.y <= 975){

            DrawTexturePro(state->normal_cursor, state->normal_cursorSrc, state->normal_cursorDest, state->origin_normal_cursor, 0, WHITE);

        }



}

//Draw picture of each menu
void SetupWindow(GameState *state, int windowcase){

    BeginDrawing();

    ClearBackground(state->bgcolor);

    switch (windowcase)
    {
    case 1:

        DrawMenu(state);

        break;
    
    case 2:

        BeginMode2D(state->view);

        ConstructScene(state);

        EndMode2D();

        break;

    
    case 3:

        DrawSettingMenu(state); 

        break;

    case 4:

        DrawLoadingMenu(state);

        break;
    
    case 5:

        DrawInstructionMenu(state);

        break;
    
    case 6:

        DrawEndingMenu(state);

        break;

    }

    
    EndDrawing();

}

//Control the action of players
void Instruction(GameState *state) {
    state->playerMoving = false;

    if (IsKeyDown(KEY_UP)&& !(state->startchat)) {

        state->playerMoving = true;

        state->playerDir = 1;

        state->playerUp = true;

    }

    else if (IsKeyDown(KEY_DOWN)&& !(state->startchat)) {

        state->playerMoving = true;

        state->playerDir = 0;

        state->playerDown = true;

    }

    else if (IsKeyDown(KEY_LEFT) && !(state->startchat) ) {

        state->playerMoving = true;

        state->playerDir = 2;

        state->playerLeft = true;

    }

    else if (IsKeyDown(KEY_RIGHT) && !(state->startchat) ) {

        state->playerMoving = true;

        state->playerDir = 3;

        state->playerRight = true;

    }

    if (IsKeyPressed(KEY_Q)) {

        state->musicPaused = !state->musicPaused;


    }

    if (IsKeyDown(KEY_ENTER)  && !(state->startchat)) {

        state->mode = SETTING;

    }

    if (IsKeyPressed(KEY_X) && !(state->startchat) ) {


        if (state->menu_toolshoverDest.x >= state->menu_icon1Dest.x && state->menu_toolshoverDest.x < state->menu_icon6Dest.x){

            state->menu_toolshoverDest.x += 97;

        }
        else{

            state->menu_toolshoverDest.x = state->menu_icon1Dest.x;


        }
        

    }

    if (IsKeyPressed(KEY_Z) && !(state->startchat) ) {

        if (state->menu_toolshoverDest.x < state->menu_icon6Dest.x+10 && state->menu_toolshoverDest.x > state->menu_icon1Dest.x){

            state->menu_toolshoverDest.x -= 97;

        }
        else{

            state->menu_toolshoverDest.x = state->menu_icon1Dest.x+485;


        }

    }
}

//action to respective slots
void actionactivate(GameState *state){

    state->canspeak = false;
    state->candig = false;
    state->canseed = false;
    state->canwater = false;
    state->canharvest = false;
    state->canother = false;

    if (state->menu_toolshoverDest.x == state->menu_icon1Dest.x) {
        state->canspeak = true;
    } 
    else if (state->menu_toolshoverDest.x == state->menu_icon1Dest.x + 97) {
        state->candig = true;
    } 
    else if (state->menu_toolshoverDest.x == state->menu_icon1Dest.x + 194) {
        state->canseed = true;
    } 
    else if (state->menu_toolshoverDest.x == state->menu_icon1Dest.x + 291) {
        state->canwater = true;
    } 
    else if (state->menu_toolshoverDest.x == state->menu_icon1Dest.x + 388) {
        state->canharvest = true;
    }
    else if (state->menu_toolshoverDest.x == state->menu_icon1Dest.x + 485) {
        state->canother = true;
    }

    if(state->canspeak){
        state->slot = slot0;
    }
    else if(state->candig){
        state->slot = slot1;
    }
    else if(state->canseed){
        state->slot = slot2;
    }
    else if(state->canwater){
        state->slot = slot3;
    }
    else if(state->canharvest){
        state->slot = slot4;
    }
    else if(state->canother){
        state->slot = slot5;
    }

}

//Gardening action and picture
void GardeningAction(GameState *state,int number){

    switch (number)
    {
    case 0:

            if (!(state->musicPaused)){

                PlaySound(state->dig_sound);

            }

            BeginDrawing();
         
            state->dig_actionSrc=(Rectangle){48 , 0 ,48,48};

            DrawTexturePro(state->player_action, state->dig_actionSrc, state->dig_actionDest, state->origin_digaction, 0, WHITE);

            state->dig_actionSrc=(Rectangle){0 , 0 ,48,48};

            EndDrawing();

        break;
    
    case 1:

            if (!(state->musicPaused)){

                PlaySound(state->dig_sound);

            }

            BeginDrawing();
                    
            state->dig_actionSrc=(Rectangle){48 , 48 ,48, 48};

            DrawTexturePro(state->player_action, state->dig_actionSrc, state->dig_actionDest, state->origin_digaction, 0, WHITE);

            state->dig_actionSrc=(Rectangle){0 , 48 ,48, 48};

            EndDrawing();

        break;

    case 2:

            if (!(state->musicPaused)){

                PlaySound(state->dig_sound);

            }

            BeginDrawing();
                    
            state->dig_actionSrc=(Rectangle){0 , 96 ,48, 48};

            DrawTexturePro(state->player_action, state->dig_actionSrc, state->dig_actionDest, state->origin_digaction, 0, WHITE);

            state->dig_actionSrc=(Rectangle){48 , 96 ,48, 48};

            EndDrawing();

        break;
    
    case 3:

            if (!(state->musicPaused)){

                PlaySound(state->dig_sound);

            }

            BeginDrawing();
                    
            state->dig_actionSrc=(Rectangle){0 , 132 ,48, 48};

            DrawTexturePro(state->player_action, state->dig_actionSrc, state->dig_actionDest, state->origin_digaction, 0, WHITE);

            state->dig_actionSrc=(Rectangle){48 , 132 ,48, 48};

            EndDrawing();


        break;
    }

}

//Detect the place to active gardening action
void Gardening(GameState * state,float CurrentplayerDestx,float CurrentplayerDesty){
    
    //printf("\n%f,%f",CurrentplayerDestx,CurrentplayerDesty);

    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){
            

             if (230+161*i <= CurrentplayerDesty && CurrentplayerDesty <= 310+138*i  && (990+132*j <= CurrentplayerDestx && CurrentplayerDestx <= 1041+138*j)){
                    
                if (state->array_land[i][j] == 1){

                        state->array_land[i][j] = 1;
                }
                else{

                    state->array_land[i][j] = 0;

                }

                }

            else{
                
                if(state->playerDir == 0 && 214+156*i <= CurrentplayerDesty && CurrentplayerDesty <= 232+153*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j && IsKeyDown(KEY_C) && state->array_land[i][j] == 0 && state->candig){


                    state->dig_actionDest=(Rectangle){CurrentplayerDestx - 250-145*j,CurrentplayerDesty-160*i+10*j + 275,200,200};

                    GardeningAction(state,0);

                    state->array_land[i][j] = 1;

                }

                if(state->playerDir == 1 && 330+145*i <= CurrentplayerDesty && CurrentplayerDesty <= 355+135*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j && IsKeyDown(KEY_C) && state->array_land[i][j] == 0 && state->candig){


                    state->dig_actionDest=(Rectangle){CurrentplayerDestx - 245 - 155*j,CurrentplayerDesty + 180 -150*i,200,200};

                    GardeningAction(state,1);

                    state->array_land[i][j] = 1;

                }


                if(state->playerDir == 2 && 241 +159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 + 150*i && 1031 +151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1060 + 148*j && IsKeyDown(KEY_C) && state->array_land[i][j] == 0 && state->candig){


                    state->dig_actionDest=(Rectangle){CurrentplayerDestx - 315 -145*j+10*i ,CurrentplayerDesty + 220 -150*i,200,200};

                    GardeningAction(state,2);

                    state->array_land[i][j] = 1;

                }
            

                if(state->playerDir == 3 && 241 + 159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 +150*i && 942 + 141*j <= CurrentplayerDestx && CurrentplayerDestx <= 954 +141*j && IsKeyDown(KEY_C) && state->array_land[i][j] == 0 && state->candig){


                    state->dig_actionDest=(Rectangle){CurrentplayerDestx - 200 -135*j +10*i,CurrentplayerDesty + 180 -150*i -5*j,200,200};

                    GardeningAction(state,3);

                    state->array_land[i][j] = 1;

                }

                
                }


            
        }

    }


}

//Detect the place to active seedling action
void Seedling(GameState * state,float CurrentplayerDestx,float CurrentplayerDesty){
    

    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){
            

             if (230+161*i <= CurrentplayerDesty && CurrentplayerDesty <= 310+138*i  && (990+132*j <= CurrentplayerDestx && CurrentplayerDestx <= 1041+138*j)){
                    
                if (state->array_seed[i][j] == 1){

                        state->array_seed[i][j] = 1;
                }
                else{

                    state->array_seed[i][j] = 0;

                }

                }

            else{
                
                if(state->playerDir == 0 && 214+156*i <= CurrentplayerDesty && CurrentplayerDesty <= 232+153*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j && IsKeyDown(KEY_C) && state->array_seed[i][j] == 0 && state->array_land[i][j] ==1 && state->canseed){


                    state->array_seed[i][j] = 1;

                    if (!(state->musicPaused)){

                        PlaySound(state->seedling_sound);

                        }

                }

                if(state->playerDir == 1 && 330+145*i <= CurrentplayerDesty && CurrentplayerDesty <= 355+135*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j && IsKeyDown(KEY_C) && state->array_seed[i][j] == 0 && state->array_land[i][j] ==1 && state->canseed){

                    state->array_seed[i][j] = 1;

                    if (!(state->musicPaused)){

                        PlaySound(state->seedling_sound);

                        }
                }


                if(state->playerDir == 2 && 241 +159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 + 150*i && 1031 +151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1060 + 148*j &&  IsKeyDown(KEY_C) && state->array_seed[i][j] == 0 && state->array_land[i][j] ==1 && state->canseed){

                    state->array_seed[i][j] = 1;

                    if (!(state->musicPaused)){

                        PlaySound(state->seedling_sound);

                        }
                }
            

                if(state->playerDir == 3 && 241 + 159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 +150*i && 942 + 141*j <= CurrentplayerDestx && CurrentplayerDestx <= 954 +141*j && IsKeyDown(KEY_C) && state->array_seed[i][j] == 0 && state->array_land[i][j] ==1 && state->canseed){

                    state->array_seed[i][j] = 1;

                    if (!(state->musicPaused)){

                        PlaySound(state->seedling_sound);

                        }
                }

                
                }


            
        }

    }


}

//Watering action and picture
void WateringAction(GameState *state,int number){

    switch (number)
    {
    case 0:
            if (!(state->musicPaused)){

                PlaySound(state->watering_sound);

            }

            BeginDrawing();
         
            state->water_actionSrc=(Rectangle){0 , 384 ,48,48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 384 ,48,48};

            EndDrawing();

        break;
    
    case 1:

            if (!(state->musicPaused)){

                PlaySound(state->watering_sound);

            }

            BeginDrawing();
                    
            state->water_actionSrc=(Rectangle){0 , 432 ,48, 48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 432 ,48, 48};

            EndDrawing();

        break;

    case 2:

            if (!(state->musicPaused)){

                PlaySound(state->watering_sound);

            }

            BeginDrawing();
                    
            state->water_actionSrc=(Rectangle){0 , 480 ,48, 48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 480 ,48, 48};

            EndDrawing();

        break;
    
    case 3:

            if (!(state->musicPaused)){

                PlaySound(state->watering_sound);

            }

            BeginDrawing();
                    
            state->water_actionSrc=(Rectangle){0 , 528 ,48, 48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 528 ,48, 48};

            EndDrawing();


        break;
    }

}

//Detect the place to active watering action
void Watering(GameState * state,float CurrentplayerDestx,float CurrentplayerDesty){

    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){
            

             if (230+161*i <= CurrentplayerDesty && CurrentplayerDesty <= 310+138*i  && (990+132*j <= CurrentplayerDestx && CurrentplayerDestx <= 1041+138*j)){
                    
                if (state->array_water[i][j] == 1){

                        state->array_water[i][j] = 1;
                }
                else{

                    state->array_water[i][j] = 0;

                }

                }

            else{
                
                if(state->playerDir == 0 && 214+156*i <= CurrentplayerDesty && CurrentplayerDesty <= 232+153*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j && IsKeyDown(KEY_C) && state->array_seed[i][j] == 1 && state->array_land[i][j] == 1 && state->array_water[i][j] ==0 && state->canwater){


                    state->water_actionDest=(Rectangle){CurrentplayerDestx - 250-145*j,CurrentplayerDesty-160*i+10*j + 275,200,200};

                    WateringAction(state,0);

                    state->array_water[i][j] = 1;

                    state->array_watercontent [i][j] += 50;

                }

                if(state->playerDir == 1 && 330+145*i <= CurrentplayerDesty && CurrentplayerDesty <= 355+135*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j  && IsKeyDown(KEY_C) && state->array_seed[i][j] == 1 && state->array_land[i][j] == 1 && state->array_water[i][j] ==0 && state->canwater){


                    state->water_actionDest=(Rectangle){CurrentplayerDestx - 245 - 155*j,CurrentplayerDesty + 180 -150*i,200,200};

                    WateringAction(state,1);

                    state->array_water[i][j] = 1;

                    state->array_watercontent [i][j] += 50;

                }


                if(state->playerDir == 2 && 241 +159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 + 150*i && 1031 +151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1060 + 148*j  && IsKeyDown(KEY_C) && state->array_seed[i][j] == 1 && state->array_land[i][j] == 1 && state->array_water[i][j] ==0 && state->canwater){


                    state->water_actionDest=(Rectangle){CurrentplayerDestx - 315 -145*j+10*i ,CurrentplayerDesty + 220 -150*i,200,200};

                    WateringAction(state,2);

                    state->array_water[i][j] = 1;

                    state->array_watercontent [i][j] += 50;

                }
            

                if(state->playerDir == 3 && 241 + 159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 +150*i && 942 + 141*j <= CurrentplayerDestx && CurrentplayerDestx <= 954 +141*j  && IsKeyDown(KEY_C) && state->array_seed[i][j] == 1 && state->array_land[i][j] == 1 && state->array_water[i][j] ==0 && state->canwater){


                    state->water_actionDest=(Rectangle){CurrentplayerDestx - 200 -135*j +10*i,CurrentplayerDesty + 180 -150*i+ 5*j,200,200};

                    WateringAction(state,3);

                    state->array_water[i][j] = 1;

                    state->array_watercontent [i][j] += 50;

                }

                
                }


            
        }

    }


}

//Harvesting action and picture
void HarvestingAction(GameState *state,int number){

    switch (number)
    {
    case 0:

            if (!(state->musicPaused)){

                PlaySound(state->harvesting_sound);

            }

            BeginDrawing();
         
            state->water_actionSrc=(Rectangle){0 , 192 ,48,48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 192 ,48,48};

            EndDrawing();

        break;
    
    case 1:
            if (!(state->musicPaused)){

                PlaySound(state->harvesting_sound);

            }

            BeginDrawing();
                    
            state->water_actionSrc=(Rectangle){0 , 240 ,48, 48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 240 ,48, 48};

            EndDrawing();

        break;

    case 2:

            if (!(state->musicPaused)){

                PlaySound(state->harvesting_sound);

            }

            BeginDrawing();
                    
            state->water_actionSrc=(Rectangle){0 , 288 ,48, 48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 288 ,48, 48};

            EndDrawing();

        break;
    
    case 3:

            if (!(state->musicPaused)){

                PlaySound(state->harvesting_sound);

            }

            BeginDrawing();
                    
            state->water_actionSrc=(Rectangle){0 , 336 ,48, 48};

            DrawTexturePro(state->player_action, state->water_actionSrc, state->water_actionDest, state->origin_wateraction, 0, WHITE);

            state->water_actionSrc=(Rectangle){48 , 336 ,48, 48};

            EndDrawing();


        break;
    }

}

//Detect the place to active harvesting action
void Harvesting(GameState * state,float CurrentplayerDestx,float CurrentplayerDesty){

    state->show_can_farm = false;

    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){
            
                
            if(state->playerDir == 0 && 214+156*i <= CurrentplayerDesty && CurrentplayerDesty <= 232+153*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j){

                state->show_can_farm = true;


                state->harvest_actionDest=(Rectangle){CurrentplayerDestx - 250-145*j,CurrentplayerDesty-160*i+10*j + 275,200,200};

                if(IsKeyDown(KEY_C)&& state->canharvest  && state->array_harvested[i][j]==1){

                    HarvestingAction(state,0);

                    state->array_land[i][j] = 0;

                    state->array_seed[i][j] = 0;

                    state->array_water[i][j] = 0;

                    state->array_growth [i][j] = 0;

                    state->array_watercontent [i][j] = 0;

                    state->array_harvested[i][j] = 0 ;

                    state->harvestedwheat += 1;


                }
            }

            if(state->playerDir == 1 && 330+145*i <= CurrentplayerDesty && CurrentplayerDesty <= 355+135*i && 970+151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1015+148*j){


                state->harvest_actionDest=(Rectangle){CurrentplayerDestx - 245 - 155*j,CurrentplayerDesty + 180 -150*i,200,200};

                state->show_can_farm = true;

                if(IsKeyDown(KEY_C)&& state->canharvest  && state->array_harvested[i][j]==1){

                    HarvestingAction(state,1);

                    state->array_land[i][j] = 0;

                    state->array_seed[i][j] = 0;

                    state->array_water[i][j] = 0;

                    state->array_growth [i][j] = 0;

                    state->array_watercontent [i][j] = 0;

                    state->array_harvested[i][j] = 0 ;

                    state->harvestedwheat += 1;


                }

                }


            if(state->playerDir == 2 && 241 +159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 + 150*i && 1031 +151*j <= CurrentplayerDestx && CurrentplayerDestx <= 1060 + 148*j ){

                state->show_can_farm = true;

                state->harvest_actionDest=(Rectangle){CurrentplayerDestx - 315 -145*j+10*i ,CurrentplayerDesty + 220 -150*i,200,200};

                if(IsKeyDown(KEY_C)&& state->canharvest  && state->array_harvested[i][j]==1){

                    HarvestingAction(state,2);

                    state->array_land[i][j] = 0;

                    state->array_seed[i][j] = 0;

                    state->array_water[i][j] = 0;

                    state->array_growth [i][j] = 0;

                    state->array_watercontent [i][j] = 0;

                    state->array_harvested[i][j] = 0 ;

                    state->harvestedwheat += 1;


                }

                }
            

            if(state->playerDir == 3 && 241 + 159*i <= CurrentplayerDesty && CurrentplayerDesty <= 307 +150*i && 942 + 141*j <= CurrentplayerDestx && CurrentplayerDestx <= 954 +141*j){

                state->show_can_farm = true;

                state->harvest_actionDest=(Rectangle){CurrentplayerDestx - 200 -135*j +10*i,CurrentplayerDesty + 180 -150*i+ 5*j,200,200};

                if(IsKeyDown(KEY_C)&& state->canharvest  && state->array_harvested[i][j]==1){

                    HarvestingAction(state,3);

                    state->array_land[i][j] = 0;

                    state->array_seed[i][j] = 0;

                    state->array_water[i][j] = 0;

                    state->array_growth [i][j] = 0;

                    state->array_watercontent [i][j] = 0;

                    state->array_harvested[i][j] = 0 ;

                    state->harvestedwheat += 1;


                }

                }

            }

        }

}

//Growth mechanism of the plant/paddy
void Growth(GameState *state){

    for (int i=0; i<5 ; i++){

        for (int j =0 ; j<6 ; j++){

            if( state->array_seed[i][j] ==1){

                state->array_growth[i][j] += 0.02;

                state->array_watercontent[i][j] -= 0.03;

                if(state->array_watercontent[i][j] <= -50 && state->array_watercontent[i][j] >= -100){

                    state->array_water[i][j] = 0;

                }

                if(state->array_watercontent[i][j] < -100 ){

                    state->array_land[i][j] = 0;

                    state->array_seed[i][j] = 0;

                    state->array_water[i][j] = 0;

                    state->array_growth [i][j] = 0;

                    state->array_watercontent [i][j] = 0;

                    state->array_harvested[i][j] = 0 ;
                                    
                }
            }
        }

    }

}

//Unload all the things while leaving the game
void LeaveGame(GameState *state) {

    UnloadTexture(state->grass);

    UnloadTexture(state->player);

    UnloadTexture(state->fence);

    UnloadTexture(state->house);

    UnloadTexture(state->door);

    UnloadTexture(state->furniture);

    UnloadTexture(state->path);

    UnloadTexture(state->dig_land);

    UnloadTexture(state->player_action);

    UnloadTexture(state->wheat);

    UnloadTexture(state->watered_land);

    UnloadTexture(state->tree);

    UnloadTexture(state->menu_sound);

    for (int i = 0; i < 32; i++) {

        UnloadTexture(state->menuframes[i]);

    }

    UnloadTexture(state->button);

    UnloadTexture(state->normal_cursor);

    UnloadTexture(state->hover_cursor);

    UnloadTexture(state->buttonhover);

    UnloadTexture(state->settingbutton);

    UnloadTexture(state->settingmenu);

    UnloadTexture(state->settingmenubackground);

    UnloadTexture(state->closesettingbutton);

    UnloadTexture(state->settinggoodbyepicture);

    UnloadTexture(state->savebackground);

    UnloadTexture(state->loadingmenu);

    UnloadTexture(state->loadingbackground);

    for (int i = 0; i < 53; i++) {

        UnloadTexture(state->loadinganimationframes[i]);

    }


    for (int i = 0; i < 127; i++) {

        UnloadTexture(state->endingframes[i]);

    }

    UnloadTexture(state->loadingbutton);

    UnloadTexture(state->menu_tools);

    UnloadTexture(state->menu_icons);

    UnloadTexture(state->chat_icon);

    UnloadTexture(state->wheat_icon);

    UnloadTexture(state->menu_toolshover);

    UnloadTexture(state->signal);

    UnloadTexture(state->displaymoney);

    UnloadTexture(state->seller);

    UnloadTexture(state->chatbox);

    UnloadTexture(state->dialogbox);

    UnloadTexture(state->seller_emo);

    UnloadTexture(state->character_emo);

    UnloadTexture(state->developer);

    UnloadSound(state->dig_sound);

    UnloadSound(state->seedling_sound);

    UnloadSound(state->watering_sound);

    UnloadSound(state->harvesting_sound);

    UnloadMusicStream(state->bg_music);

    UnloadFont(state->titlefont);

    UnloadFont(state->myfont);

    UnloadFont(state->creditfont);

    CloseAudioDevice();

    CloseWindow();

}

//Changing cursor display on the screen
void cursorchanging(GameState *state, int casetype){

    state->mouseposition = GetMousePosition();

    //printf("x:%f,y:%f",state->mouseposition.x,state->mouseposition.y);

    switch (casetype)
    {
    case 1:
        HideCursor();

        state->normal_cursorDest.x = state->mouseposition.x;

        state->normal_cursorDest.y = state->mouseposition.y;

        state->hover_cursorDest.x =  state->mouseposition.x;

        state->hover_cursorDest.y = state->mouseposition.y;
        break;
    
    case 2:

        ShowCursor();

        break;
    }

}

//Run the game
void main() {

    GameState state = {0};

    //Set up random variable for the maximum accepted value by the seller
    srand(time(NULL));

    Initialise(&state);

    while (!WindowShouldClose()) {

        UpdateMusicStream(state.bg_music);

        if (state.musicPaused) {

            PauseMusicStream(state.bg_music);

        } else {

            ResumeMusicStream(state.bg_music);

        }
        
        switch (state.mode) {
            case MENU:

                SetupWindow(&state,1);

                cursorchanging(&state,1);

                break;

            case PLAYING:

                cursorchanging(&state,2);

                SetupWindow(&state,2);

                checkCollisionwallxtop(&state);

                checkCollisionwallyleft(&state);

                checkCollisionwallyright(&state);

                checkCollisionwallxbottom(&state);

                CollisionObject(&state);

                AnimationOnDoor(&state);

                actionactivate(&state);

                state.playerDest.x = clamp(state.playerDest.x, state.min_x, state.max_x);

                state.playerDest.y = clamp(state.playerDest.y, state.min_y, state.max_y);

                state.wheatDest.x = clamp(state.wheatDest.x , 760-300, 760+1690);

                state.wheatDest.y = clamp(state.wheatDest.y , -125-400, -125+1550);

                state.harvestedwheat_x = clamp(state.harvestedwheat_x , 810-300, 810+1690);

                state.harvestedwheat_y = clamp(state.harvestedwheat_y , -150-400, -150+1550);

                state.settingbuttonDest.x = clamp(state.settingbuttonDest.x , -490-300, -490+1690);

                state.settingbuttonDest.y = clamp(state.settingbuttonDest.y , -130-400, -130+1550);

                state.menu_toolsDest.x = clamp(state.menu_toolsDest.x , 200-300, 200+1690);

                state.menu_toolsDest.y = clamp(state.menu_toolsDest.y, 733-400, 733+1550);

                state.menu_icon1Dest.x = clamp(state.menu_icon1Dest.x, -43-300, -43+1690);

                state.menu_icon1Dest.y = clamp(state.menu_icon1Dest.y, 710-400, 710+1550);

                state.menu_icon2Dest.x = clamp(state.menu_icon2Dest.x, 54-300, 54+1690);

                state.menu_icon2Dest.y = clamp(state.menu_icon2Dest.y, 710-400, 710+1550);

                state.menu_icon3Dest.x = clamp(state.menu_icon3Dest.x, 151-300, 151+1690);

                state.menu_icon3Dest.y = clamp(state.menu_icon3Dest.y, 710-400, 710+1550);

                state.menu_icon4Dest.x = clamp(state.menu_icon4Dest.x, 252-300, 252+1690);

                state.menu_icon4Dest.y = clamp(state.menu_icon4Dest.y, 710-400, 710+1550);

                state.menu_icon5Dest.x = clamp(state.menu_icon5Dest.x, 342-300, 342+1690);

                state.menu_icon5Dest.y = clamp(state.menu_icon5Dest.y, 710-400, 710+1550);

                state.menu_icon6Dest.x = clamp(state.menu_icon6Dest.x, 439-300, 439+1690);

                state.menu_icon6Dest.y = clamp(state.menu_icon6Dest.y, 710-400, 710+1550);

                state.chat_iconDest.x = clamp(state.chat_iconDest.x, -40-300, -40+1690);

                state.chat_iconDest.y = clamp(state.chat_iconDest.y, 713-400, 713+1550);

                state.wheat_iconDest.x = clamp(state.wheat_iconDest.x, 152-300, 152+1690);

                state.wheat_iconDest.y = clamp(state.wheat_iconDest.y, 711-400, 711+1550);

                state.can_farm_signalDest.x = clamp(state.can_farm_signalDest.x, 650-300, 650+1690);

                state.can_farm_signalDest.y = clamp(state.can_farm_signalDest.y, -70-400, -70+1550);

                state.displaymoneyDest.x = clamp(state.displaymoneyDest.x , 830-300, 830+1690);

                state.displaymoneyDest.y = clamp(state.displaymoneyDest.y , 30-400, 30+1550);

                state.money_x = clamp(state.money_x , 810-300, 810+1690);

                state.money_y = clamp(state.money_y , -35-400, -35+1550);

                state.dialogboxDest.x = clamp(state.dialogboxDest.x , 200-300, 200+1690);

                state.dialogboxDest.y = clamp(state.dialogboxDest.y , 820-400, 820+1550);

                state.seller_emoDest.x = clamp(state.seller_emoDest.x , -385-300, -385+1690);

                state.seller_emoDest.y = clamp(state.seller_emoDest.y , 720-400, 720+1550);

                switch (state.slot)
                {
                case slot0:
                    
                    state.menu_toolshoverDest.x = clamp(state.menu_toolshoverDest.x, -43-300, -43+1690);

                    break;
                
                case slot1:

                    state.menu_toolshoverDest.x = clamp(state.menu_toolshoverDest.x, 54-300, 54+1690);


                    break;

                case slot2:

                    state.menu_toolshoverDest.x = clamp(state.menu_toolshoverDest.x, 151-300, 151+1690);

                    break;

                case slot3:

                    state.menu_toolshoverDest.x = clamp(state.menu_toolshoverDest.x, 248-300, 248+1690);

                    break;

                case slot4:

                    state.menu_toolshoverDest.x = clamp(state.menu_toolshoverDest.x, 345-300, 345+1690);

                    break;

                case slot5:

                    state.menu_toolshoverDest.x = clamp(state.menu_toolshoverDest.x, 442-300, 442+1690);
                    
                    break;
                }

                state.menu_toolshoverDest.y = clamp(state.menu_toolshoverDest.y, 718-400, 718+1550);

                state.playerSrc.x = state.playerSrc.width * state.playerframe;

                if (state.playerMoving) {

                    state.stay = false;

                    if (state.playerUp){

                        moveAllY(&state,-state.playerSpeed);

                        }

                    if (state.playerDown){

                        moveAllY(&state,state.playerSpeed);

                        }

                    if (state.playerLeft) {

                        moveAllX(&state,-state.playerSpeed);

                        }
                    if (state.playerRight) {

                        moveAllX(&state,state.playerSpeed);

                        }

                    if (state.frameCount % 8 == 1) {

                        state.playerframe++;

                        }

                } else if (state.stay) {

                    if (state.frameCount % 45 == 1) 
                    {

                        state.playerframe++;

                    }

                }

                if (state.frameCount % 20 == 1) 
                    {
                        state.sellerFrame++;

                    }

                state.frameCount++;

                if (state.playerframe > 3){

                    state.playerframe = 0;
                    }
                if (!state.playerMoving && state.playerframe > 1 && state.stay){

                    state.playerframe = 0;
                    }
                if (state.sellerFrame > 2){

                    state.sellerFrame = 0;
                    }


                state.sellerSrc.x = state.sellerSrc.width * state.sellerFrame;

                state.playerSrc.x = state.playerSrc.width * state.playerframe;

                state.playerSrc.y = state.playerSrc.height * state.playerDir;

                state.view.target = (Vector2){(float)state.playerDest.x - (state.playerDest.width / 2),
                                            (float)state.playerDest.y - (state.playerDest.height / 2)};

                state.playerUp = state.playerDown = state.playerRight = state.playerLeft = false;

                state.stay = true;

                float CurrentplayerDestx = state.playerDest.x;

                float CurrentplayerDesty = state.playerDest.y;

                Instruction(&state);

                Chatting(&state);

                Gardening(&state,CurrentplayerDestx,CurrentplayerDesty);

                Seedling(&state,CurrentplayerDestx,CurrentplayerDesty);

                Watering(&state,CurrentplayerDestx,CurrentplayerDesty);

                Growth(&state);

                Harvesting(&state,CurrentplayerDestx,CurrentplayerDesty);

                break;

            case SETTING:

                SetupWindow(&state,3);

                cursorchanging(&state,1);

                break;

            case LOADING:

                SetupWindow(&state,4);

                cursorchanging(&state,1);

                break;

            case INSTRUCTION:

                SetupWindow(&state,5);

                cursorchanging(&state,1);

                break;

            case ENDING:

                SetupWindow(&state,6);

                cursorchanging(&state,1);

                break;
        }

    }

    LeaveGame(&state);

}