#pragma once
/*
 * La idea sería tener un archivo de lectura de este tipo de data en vez de un .h a compilar
*/

#include <SDL.h>
#include <iostream>
#include "../core/Vector2D.h"
#include "../components/ecs.h"

#ifndef CONSTANTS_H_
#define CONSTANTS_H_
using namespace std;
using uint = unsigned int;

const Vector2D VECTOR_ZERO = { 0,0 };


// WINDOW ----------------------------------------------------------------------------------------
const int WIN_WIDTH = 1280;
const int WIN_HEIGHT = 720;
const float WIN_WIDTH_PER_PIXEL = WIN_WIDTH/544;
const float WIN_HEIGHT_PER_PIXEL = WIN_HEIGHT/306;
const SDL_Rect FULLWINDOW = { 0, 0, WIN_WIDTH, WIN_HEIGHT };

const float PIXEL_WIDTH = WIN_WIDTH / 544.0f;
const float PIXEL_HEIGHT = WIN_HEIGHT / 306.0f;

// FRAME TIMES ------------------------------------------------------------------------------------
const double FRAME_TIME = 30;
const int DELAY_TIME = 17;

// TEXTURES ---------------------------------------------------------------------------------------
const string TEXTURES_FILE = "../Game/src/data/textures.txt"; // Hay que rehacer las movidas bien aquí, en vez del archivo este
const int NUM_TEXTURES = 19;
const int BLOCK_NUMB = 3;
const int DIGITS_NUMB = 4;

// FONTS ------------------------------------------------------------------------------------------
const string USED_FONT = "ARIAL24";
const int USED_FONT_SIZE = 24;
const string FONT_SS_REG22 = "SILKSCREEN_REGULAR22";
const string FONT_SS_BOLD22 = "SILKSCREEN_BOLD22";
const string FONT_SS_REG30 = "SILKSCREEN_REGULAR30";
const string FONT_SS_BOLD30 = "SILKSCREEN_BOLD30";

// TEXT COLORS ------------------------------------------------------------------------------------
const SDL_Color COLOR_WHITE = { 255, 255, 255 };
const SDL_Color COLOR_RED = { 255, 0,0 };

// ANIMATIONS -------------------------------------------------------------------------------------
const string ONOUT = "OnOut";
const string ONOVER = "OnOver";
const string ONCLICK = "OnClick";
const string ONLOCKED = "OnLocked";
const string ONCOMPLETED = "OnCompleted";
const string SHUFFLING_CARDS = "ShufflingCards";
const string IDLE = "Idle";
const string REVERSE = "CardReverse";
const string NUMBERS = "Numbers";

// CHARACTER ANIMATOR -----------------------------------------------------------------------------
const string CHARACTER_IDLE_KEY = "charaIdle";
const string CHARACTER_MOVE_KEY = "charaMove";
const string CHARACTER_ATTACK_IDLE_KEY = "charaAttackIdle";
const string CHARACTER_ATTACK_MOVE_KEY = "charaAttackMove";
const string CHARACTER_SKILL_IDLE_KEY = "charaSkillIdle";
const string CHARACTER_SKILL_MOVE_KEY = "charaSkillMove";
const string CHARACTER_DEATH_KEY = "charaDeath";

// PLAYER -----------------------------------------------------------------------------------------
// PLAYER ANIMATIONS
const string PLAYER = "newPlayer";
const int PLAYER_SPRITE_WIDTH = 32;
const int PLAYER_SPRITE_HEIGHT = 32;
const int PLAYER_SPRITE_ROWS = 7;
const int PLAYER_SPRITE_COLS = 8;

//PLAYER IDLE ANIM
const int PLAYER_IDLE_INITIAL_FRAME = 0;
const int PLAYER_IDLE_FINAL_FRAME = 7;
const int PLAYER_IDLE_FRAME_RATE = 10;
//PLAYER MOVE ANIM
const int PLAYER_MOVE_INITIAL_FRAME = 8;
const int PLAYER_MOVE_FINAL_FRAME = 15;
const int PLAYER_MOVE_FRAME_RATE = 10;
//PLAYER SKILL IDLE ANIM
const int PLAYER_SKILL_IDLE_INITIAL_FRAME = 16;
const int PLAYER_SKILL_IDLE_FINAL_FRAME = 23;
const int PLAYER_SKILL_IDLE_FRAME_RATE = 12;
//PLAYER SKILL MOVE ANIM
const int PLAYER_SKILL_MOVE_INITIAL_FRAME = 24;
const int PLAYER_SKILL_MOVE_FINAL_FRAME = 31;
const int PLAYER_SKILL_MOVE_FRAME_RATE = 12;
//PLAYER ATTACK IDLE ANIM
const int PLAYER_ATTACK_IDLE_INITIAL_FRAME = 32;
const int PLAYER_ATTACK_IDLE_FINAL_FRAME = 39;
const int PLAYER_ATTACK_IDLE_FRAME_RATE = 12;
//PLAYER ATTACK MOVE ANIM
const int PLAYER_ATTACK_MOVE_INITIAL_FRAME = 40;
const int PLAYER_ATTACK_MOVE_FINAL_FRAME = 47;
const int PLAYER_ATTACK_MOVE_FRAME_RATE = 12;
//PLAYER DEATH ANIM
const int PLAYER_DEATH_INITAL_FRAME = 48;
const int PLAYER_DEATH_FINAL_FRAME = 56;
const int PLAYER_DEATH_FRAME_RATE = 8;
const double DEATH_DELAY = 1000;

// FLOOR -----------------------------------------------------------------------------------------
const float FLOOR_WIDTH = 6750; //Dimension horizontal del sprite de suelo
const float FLOOR_HEIGHT = 4500; //Dimension vertical del sprite de suelo
const Vector2D FLOOR_PAST_VELOCITY = VECTOR_ZERO;

// PLAYER DIMENSIONS
const float PLAYER_INITIAL_WIDTH = PLAYER_SPRITE_WIDTH * PIXEL_WIDTH;
const float PLAYER_INITIAL_HEIGHT = PLAYER_SPRITE_HEIGHT * PIXEL_HEIGHT;
const Vector2D PLAYER_INITIAL_POSITION = { FLOOR_WIDTH / 2.0f - PLAYER_INITIAL_WIDTH / 2, FLOOR_HEIGHT / 2.0f - PLAYER_INITIAL_HEIGHT / 2};
const Vector2D PLAYER_INITIAL_VELOCITY = { 0.0f, 0.0f };
const float PLAYER_INITIAL_ROTATION = 0;
const float PLAYER_SPEED = 200;
const float DASH_SPEED = 1400;
const float DASH_DURATION = 0.15;
const float REDUCTION_FACTOR = 1.001f;

// POINTER -----------------------------------------------------------------------------------------
const string POINTER = "Pointer";
const int POINTER_WIDTH = 20;
const int POINTER_HEIGHT = 20;
const float POINTER_DEFAULT_RADIUS = 100.0f;
const float POINTER_NORMAL_INCLINATION = -25.0f;

// ENEMIES ---------------------------------------------------------------------------------------
const int ENEMY_WIDTH = 30 * 2;
const int ENEMY_HEIGHT = 60 * 2;
const int BULLET_ANGLE = 20;
const int SHIELD_SPEED = 20;
const float ENEMY_SPEED = 50;
const int PUSH_STRENGTH = 100;

// MELEE ENEMY
const float MELEE_ENEMY_COOLDOWN = 500;
const string MELEE_ENEMY_TEXTURE_KEY = "MeleeEnemy";
const int MELEE_ENEMY_SPRITE_WIDTH = 32;
const int MELEE_ENEMY_SPRITE_HEIGHT = 32;
const int MELEE_ENEMY_SPRITE_ROWS = 2;
const int MELEE_ENEMY_SPRITE_COLS = 12;

const int MELEE_ENEMY_WIDTH = MELEE_ENEMY_SPRITE_WIDTH * PIXEL_WIDTH;
const int MELEE_ENEMY_HEIGHT = MELEE_ENEMY_SPRITE_HEIGHT * PIXEL_HEIGHT;

const Animation MELEE_ENEMY_IDLE_ANIMATION(12, 19, 10, -1);
const Animation MELEE_ENEMY_MOVEMENT_ANIMATION(0, 11, 10, -1);
const Animation MELEE_ENEMY_ATTACK_ANIMATION(12, 19, 10, 1);
const int MELEE_LIFE = 20;
const int MELEE_ATTACK_DAMAGE = 20;

// RANGED ENEMY
const string RANGED_ENEMY_TEXTURE_KEY = "RangedEnemy";
const int RANGED_ENEMY_SPRITE_WIDTH = 32;
const int RANGED_ENEMY_SPRITE_HEIGHT = 32;
const int RANGED_ENEMY_SPRITE_ROWS = 2;
const int RANGED_ENEMY_SPRITE_COLS = 11;

const int RANGED_ENEMY_WIDTH = RANGED_ENEMY_SPRITE_WIDTH * PIXEL_WIDTH;
const int RANGED_ENEMY_HEIGHT = RANGED_ENEMY_SPRITE_HEIGHT * PIXEL_HEIGHT;

const Animation RANGED_ENEMY_IDLE_ANIMATION(0, 4, 10, -1);
const Animation RANGED_ENEMY_MOVEMENT_ANIMATION(14, 21, 10, -1);
const Animation RANGED_ENEMY_ATTACK_ANIMATION(5, 13, 10, 1);

const int RANGED_ATTACK_ANIM_DELAY = 670;
const int RANGED_LIFE = 10;
const int RANGED_ATTACK_DAMAGE = 20;

// ASSASIN ENEMY
const string ASSASIN_ENEMY_TEXTURE_KEY = "AssasinEnemy";
const int ASSASIN_ENEMY_SPRITE_WIDTH = 32;
const int ASSASIN_ENEMY_SPRITE_HEIGHT = 32;
const int ASSASIN_ENEMY_SPRITE_ROWS = 2;
const int ASSASIN_ENEMY_SPRITE_COLS = 7;

const Animation ASSASIN_ENEMY_IDLE_ANIMATION(0, 4, 10, -1);
const Animation ASSASIN_ENEMY_MOVEMENT_ANIMATION(0, 6, 10, -1);
const Animation ASSASIN_ENEMY_ATTACK_ANIMATION(7, 11, 10, 1);

// TANK ENEMY
const string TANK_ENEMY_TEXTURE_KEY = "TankEnemy";
const int TANK_ENEMY_SPRITE_WIDTH = 40;
const int TANK_ENEMY_SPRITE_HEIGHT = 40;
const int TANK_ENEMY_SPRITE_ROWS = 6;
const int TANK_ENEMY_SPRITE_COLS = 5;

const int TANK_WIDTH = TANK_ENEMY_SPRITE_WIDTH * PIXEL_WIDTH;
const int TANK_HEIGHT = TANK_ENEMY_SPRITE_HEIGHT * PIXEL_HEIGHT;
const float TANK_SPEED = 35;
const int TANK_ATTACK_DAMAGE = 10;
const int TANK_LIFE = 60;
const float TANK_STOP_TIME = 500;
const float TANK_ATTACK_DISTANCE = 200;
const float TANK_ATTACK_TIME = 2000;
const Animation TANK_ENEMY_IDLE_ANIMATION(0, 0, 10, -1);
const Animation TANK_ENEMY_MOVEMENT_ANIMATION(21, 25, 10, -1);
const Animation TANK_ENEMY_ATTACK_ANIMATION(0, 20, 10, 1);

// BOSS ENEMY
const float BOSS_ENEMY_COOLDOWN = 500;
const string BOSS_ENEMY_TEXTURE_KEY = "BossEnemy";
const int BOSS_ENEMY_SPRITE_WIDTH = 300;
const int BOSS_ENEMY_SPRITE_HEIGHT = 300;
const int BOSS_ENEMY_SPRITE_ROWS = 6;
const int BOSS_ENEMY_SPRITE_COLS = 7;
const int BOSS_ENEMY_WIDTH = BOSS_ENEMY_SPRITE_WIDTH * PIXEL_WIDTH;
const int BOSS_ENEMY_HEIGHT = BOSS_ENEMY_SPRITE_HEIGHT * PIXEL_HEIGHT;
const Vector2D BOSS_OFFSET = Vector2D(BOSS_ENEMY_WIDTH / 2, -BOSS_ENEMY_HEIGHT / 2);
const int BOSS_LIFE = 2500;
const int BOSS_COLLIDER_W = 350;
const float BOSS_CLOCK_DELAYTIME = 2;
const float BOSS_CLOCK_ATTACKTIME = 1;
const float BOSS_CLOCK_ATTACKDURATION = 4;

const float BOSS_TARGETED_DELAY = 3;

//BOSS ANIMATIONS--------------------------

const Animation BOSS_ENEMY_IDLE_ANIMATION(0, 4, 5, -1);
const Animation BOSS_ENEMY_MOVEMENT_ANIMATION(0, 4, 5, -1);
const Animation BOSS_ENEMY_ATTACK_ANIMATION(0, 4, 5, -1);


const string BOSS_ENEMY_BULLETHELL_KEY = "BulletHell";
const Animation BOSS_ENEMY_BULLETHELL_ANIMATION(5, 15, 5, 1);

const string BOSS_ENEMY_GRENADE_ATTACK_KEY = "GrenadeAttack";
const Animation BOSS_ENEMY_GRENADE_ATTACK_ANIMATION(16, 26, 5, 1);

const string BOSS_ENEMY_COMBINED_ATTACK_KEY = "CombinedAttack";
const Animation BOSS_ENEMY_COMBINED_ATTACK_ANIMATION(27, 38, 5, 1);

//BOSS ATTACKS-----------------------------
const int CONE_HITBOX_SIZE = 250;
const float CONE_WITDH = 300;
const float CONE_HEIGHT = 180;
const int CONE_ATTACK_DURATION = 2; // 2 seconds
const int CONE_ATTACK_COOLDOWN = 2000; // 2 seconds
const float RAD_TO_DEG = 180.0f / M_PI;
const Animation BOSS_TENTACLE_ANIMATION(0, 10, 5, -1);

const string BOSS_TENTACLE = "BossTentacle";
const string BOSS_TARGETED_TENTACLE = "TargetedTentacle";
const string BOSS_BULLET = "BossBullet";
const string CONE_BOSS = "ConeAttack";
const float BOSS_BULLET_W = 35;
const float BOSS_BULLET_H = 7;
const float BOSS_BULLET_DMG = 20;
const float BOSS_GRENADE_DIMENSIONS = 100;
const float BOSS_GRENADE_EXPLOSION = 200;

const Vector2D TENTACLES_PORTALS_OFFSET = Vector2D(250, 100);
const float PORTALS_W = 500;
const float PORTALS_H = 200;
const float TENTACLE_MAX_W = 450;
const float TARGETED_TENTACLE_MAX_W = 600;
const float TENTACLE_INITIAL_W = 50;
const float TENTACLE_H = 40;

// NAMES SPRITES ---------------------------------------------------------------------------------------
const string HEAL_AREA = "HealArea";
const string SWORD_SLASH = "SwordSlash";
const string SWORD_SPIN = "SwordSpin";
const string SPEAR_THRUST = "SpearThrust";
const string SOUND_ATTACK = "Sound";
const string BULLET= "Bullet";
const string PLAYER_ARROW = "PlayerArrow";
const string ENEMY_ARROW = "EnemyArrow";
const string LIGHT_BULLET = "LightBullet";
const string LIGHT_EXPLOSION = "LightExplosion";
const string PULGA_BULLET = "PulgaBullet";
const string PULGA_EXPLOSION = "PulgaExplosion";
const string GRENADE = "Grenade";
const string GRENADE_EXPLOSION = "GrenadeExplosion";
const string FLASH_BANG = "FlashBang";
const string LASER = "Laser";
// SIZE SPRITES ---------------------------------------------------------------------------------------

// BULLETS ---------------------------------------------------------------------------------------
const float BULLET_SPEED = 200;
const float GUN_BULLET_SPEED = 550;
const float PULGA_BULLET_SPEED = 250;
const float SMG_BULLET_SPEED = 700;
const float LIGHT_BULLET_SPEED = 800;
const float ARROW_SPEED = 350;
const float THROWN_SPEAR_SPEED = 600;
const float TORCH_SIZE_HEAL = 400;
const float LASER_BULLET_SPEED = 2000;
const float LASER_BULLET_SPEED_A = 200;
// STATUS ---------------------------------------------------------------------------------------

const int BURN_DAMAGE = 4;

// BUTTONS ---------------------------------------------------------------------------------------
// BUTTONS DIMENSIONS
const int BUTTON_SPRITE_WIDTH = 79;
const int BUTTON_SPRITE_HEIGHT = 18;
const int BUTTON_SPRITE_COLUMS = 2;
const int BUTTON_SPRITE_ROWS = 6;
const int BUTTON_FRAME_SPRITE_WIDTH = 95;
const int BUTTON_FRAME_SPRITE_HEIGTH = 45;
// ANIMATIONS FRAMERATES
const int ONCLICK_ONOUT_SPEED = 1;
const int ONOVER_SPEED = 10;
// BUTTON FRAMES ANIMATIONS
const int ONOUT_ALL_FRAMES = 10;
const int ONONVER_START_FRAME = 0;
const int ONOVER_END_FRAME = 9;
const int ONCLICK_ALL_FRAMES = 11;
// MAINMENU: BUTTONS POSITIONS AND DIMENSIONS
const int MM_BUTTON_WIDTH = BUTTON_SPRITE_WIDTH * 3;
const int MM_BUTTON_HEIGHT = BUTTON_SPRITE_HEIGHT * 3;
const int MM_BUTTONFRAME_WIDTH = BUTTON_FRAME_SPRITE_WIDTH * 3;
const int MM_BUTTONFRAME_HEIGHT = BUTTON_FRAME_SPRITE_HEIGTH * 3;
const Vector2D FRAME_OFFSET = Vector2D(36, 66);
const Vector2D MM_PLAY_BUTTON_POS_NOSAVE = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 8 - FRAME_OFFSET.getX() / 2, WIN_HEIGHT * 0.55);
const Vector2D MM_PLAY_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 5 - FRAME_OFFSET.getX(), WIN_HEIGHT * 0.55);
const Vector2D MM_ALBUM_BUTTON_POS_NOSAVE = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 + WIN_WIDTH / 8 + FRAME_OFFSET.getX(), WIN_HEIGHT * 0.55);
const Vector2D MM_ALBUM_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 + WIN_WIDTH / 5 + FRAME_OFFSET.getX() * 2, WIN_HEIGHT * 0.55);
const Vector2D MM_OPTIONS_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 - WIN_WIDTH / 8 - FRAME_OFFSET.getX() / 2, WIN_HEIGHT * 0.7);
const Vector2D MM_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 + WIN_WIDTH / 8 + FRAME_OFFSET.getX(), WIN_HEIGHT * 0.7);
const Vector2D MM_RESUME_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2 + FRAME_OFFSET.getX() / 2, WIN_HEIGHT * 0.55);
const Vector2D FOUND_TEXT_POS = Vector2D(1016, 40);
// PAUSEMENU: BUTTON POSITIONS AND DIMENSIONS
const string PAUSE_MESSAGE = "PausaMessage";
const float PAUSE_MESSAGE_W = 300;
const float PAUSE_MESSAGE_H = 120;
const Vector2D PAUSE_MESSAGE_POS = Vector2D(WIN_WIDTH / 2 - PAUSE_MESSAGE_W / 2, WIN_HEIGHT / 5);
const int PM_BUTTON_WIDTH = BUTTON_SPRITE_WIDTH * 4;
const int PM_BUTTON_HEIGHT = BUTTON_SPRITE_HEIGHT * 4;
const int PM_BUTTONFRAME_WIDTH = BUTTON_FRAME_SPRITE_WIDTH * 4;
const int PM_BUTTONFRAME_HEIGHT = BUTTON_FRAME_SPRITE_HEIGTH * 4;
const Vector2D PM_RESUME_BUTTON_POS = Vector2D(WIN_WIDTH / 3 - MM_BUTTON_WIDTH / 2, WIN_HEIGHT / 2);
const Vector2D PM_OPTIONS_BUTTON_POS = Vector2D(WIN_WIDTH * 2 / 3 - (MM_BUTTON_WIDTH / 2), WIN_HEIGHT / 2);
const Vector2D PM_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - (MM_BUTTON_WIDTH / 2), WIN_HEIGHT * 2 / 3 + 30);
const Vector2D PM_RESUMEFRAME_BUTTON_POS = PM_RESUME_BUTTON_POS - FRAME_OFFSET;
const Vector2D PM_OPTIONSFRAME_BUTTON_POS = PM_OPTIONS_BUTTON_POS - FRAME_OFFSET;
const Vector2D PM_EXITFRAME_BUTTON_POS = PM_EXIT_BUTTON_POS - FRAME_OFFSET;
//CHESTMENU: BUTTON POSITIONS AND DIMENSIONS
const int CHEST_BUTTON_WIDTH = 100;
const int CHEST_BUTTON_HEIGHT = 50;
const int CHEST_SPRITE_WIDTH = 46;
const int CHEST_SPRITE_HEIGHT = 26;
const string CHEST_TEXTURE = "GachaChest";
const string SPARKLES_TEXTURE = "Sparkles";

// MAPSCENE: BUTTON POSITIONS AND DIMENSIONS
const int MS_BUTTON_WIDTH = BUTTON_SPRITE_WIDTH * 3;
const int MS_BUTTON_HEIGHT = BUTTON_SPRITE_HEIGHT * 3;
const int MS_BUTTONFRAME_WIDTH = BUTTON_FRAME_SPRITE_WIDTH * 3;
const int MS_BUTTONFRAME_HEIGHT = BUTTON_FRAME_SPRITE_HEIGTH * 3;
const Vector2D MS_OPTIONS_BUTTON_POS = Vector2D(WIN_WIDTH / 8 - (MS_BUTTON_WIDTH / 2), WIN_HEIGHT * 5 / 6);
const Vector2D MS_INVENTORY_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - (MS_BUTTON_WIDTH / 2), WIN_HEIGHT * 5 / 6);
const Vector2D MS_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH * 7 / 8 - (MS_BUTTON_WIDTH / 2), WIN_HEIGHT * 5 / 6);
const Vector2D MS_OPTIONSFRAME_BUTTON_POS = MS_OPTIONS_BUTTON_POS - FRAME_OFFSET;
const Vector2D MS_INVENTORYFRAME_BUTTON_POS = MS_INVENTORY_BUTTON_POS - FRAME_OFFSET;
const Vector2D MS_EXITFRAME_BUTTON_POS = MS_EXIT_BUTTON_POS - FRAME_OFFSET;
// MAPSCENE: BACKGROUND
const int MAP_BACKGROUND_WIDTH = 544;
const int MAP_BACKGROUND_HEIGTH = 918;
const int MAP_PARALLAX_WIDTH = 544 * PIXEL_WIDTH;
const int MAP_PARALLAX_HEIGHT = 544 * PIXEL_HEIGHT;
const float MAP_SCROLLFACTOR = 0.5;

// INVENTORYSCENE: BUTTON POSITIONS AND DIMENSIONS
const int IS_BUTTON_WIDTH = BUTTON_SPRITE_WIDTH * 2;
const int IS_BUTTON_HEIGHT = BUTTON_SPRITE_HEIGHT * 2;
const int IS_BUTTONFRAME_WIDTH = BUTTON_FRAME_SPRITE_WIDTH * 2;
const int IS_BUTTONFRAME_HEIGHT = BUTTON_FRAME_SPRITE_HEIGTH * 2;
const Vector2D IS_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH - IS_BUTTON_WIDTH * 3 / 2 - 45, WIN_HEIGHT - IS_BUTTON_HEIGHT * 3 / 2 - 5);
const Vector2D COIN_OFFSET = Vector2D(WIN_WIDTH * 5 / 6 - 96, 10);
const Vector2D MONEY_TEXT = COIN_OFFSET + Vector2D(80, 8);
const int MAX_CARDS = 16;
const string FEEDBACKTEXT = "Necesitas al menos 4 cartas.";
const Vector2D FEEDBACK_POS = Vector2D(WIN_WIDTH / 2 - 18 * FEEDBACKTEXT.size() / 2, WIN_HEIGHT - 130);
const int FEEDBACK_WIDTH = 500;
const int FEEDBACK_HEIGHT = 150;

// INVENTORYSCENE : SYMBOLS
const string SYMBOLS_KEYS[5] = {
	"LifeSymbol", "ManaSymbol", "SpeedSymbol", "AttackSymbol", "CadenceSymbol"
};
const string STATS_TEXTS[5] = {
	"Vida", "Mana", "Velocidad", "Ataque", "Cadencia"
};
const int SYMBOL_DIMENSIONS = 64;
const Vector2D SYMBOL_POSITIONS[5] = {
	Vector2D(WIN_WIDTH * 5 / 6 - (IS_BUTTON_WIDTH / 2), 310),
	Vector2D(WIN_WIDTH * 5 / 6 - (IS_BUTTON_WIDTH / 2), 380),
	Vector2D(WIN_WIDTH * 5 / 6 - (IS_BUTTON_WIDTH / 2), 450),
	Vector2D(WIN_WIDTH * 5 / 6 - (IS_BUTTON_WIDTH / 2), 520),
	Vector2D(WIN_WIDTH * 5 / 6 - (IS_BUTTON_WIDTH / 2), 590)
};

const Vector2D STAT_OFFSET = Vector2D(74, 20);
const Vector2D STAT_VALUE_OFFSET = Vector2D(210, 20);

const string CARD_CIRCLE = "CardCircle";
const int CARD_CIRCLE_RADIOUS = 20;
const Vector2D CARD_CIRCLE_OFFSET = Vector2D(52, 75);
const string CARD_FRAME = "CardFrame";
const int CARD_FRAME_WIDTH = 66;
const int CARD_FRAME_HEIGHT = 101;
const Vector2D CARD_FRAME_OFFSET = Vector2D(4, 4);
const string CARD_RECTANGLE = "CardRectangle";
const int CARD_RECTANGLE_WIDTH = 34;
const int CARD_RECTANGLE_HEIGHT = 14;
const Vector2D CARD_RECTANGLE_OFFSET = Vector2D(44, -7);

const int PANEL_HEIGHT = 30;

const string DECK_PANEL = "DeckPanel";
const int DP_WIDTH = 74;
const Vector2D DP_POSITION = Vector2D(0, 243);

const string OBJECTS_PANEL = "ObjectsPanel";
const int OP_WIDTH = 125;
const Vector2D OP_POSITION = Vector2D(1116 - OP_WIDTH/2, 99);

const string INVENTORY_PANEL = "InventoryPanel";
const int IP_WIDTH = 175;
const Vector2D IP_POSITION = Vector2D(0, 0);

const string STATS_PANEL = "StatsPanel";
const int SP_WIDTH = 210;
const Vector2D SP_POSITION = Vector2D(1116 - SP_WIDTH / 2, 269);

const int ALB_CARD_W = 58 * PIXEL_WIDTH;
const int ALB_CARD_H = 93 * PIXEL_HEIGHT;
const int ALB_CARD_X[3] = { 65, 210, 355 };
const int ALB_CARD_Y = 275;
const int ALB_CARD_Y_DIST = 10;

const Animation UNSELECTED_CARD_ANIM(0, 0, 1, -1);
const Animation SELECTED_CARD_ANIM(1, 2, 2, -1);
const Animation CLICKED_CARD_ANIM(3, 3, 1, -1);


// INVENTORYSCENE : DECK
const int DECK_HEIGHT = 520;

// INVENTORY : OBJECTS
const int OBJECTS_DIMENSIONS = 64;
const Vector2D OBJECTS_POSITIONS[6] = {
	Vector2D(1010, 132),
	Vector2D(1090, 132),
	Vector2D(1170, 132),
	Vector2D(1010, 199),
	Vector2D(1090, 199),
	Vector2D(1170, 199),
};

// BUTTON KEYS
const string PLAY = "PlayButton";
const string CONTINUE = "ContinueButton";
const string OPTIONS = "OptionsButton";
const string ALBUM = "AlbumButton";
const string EXIT = "ExitButton";
const string RESUME = "ResumeButton";
const string INVENTORY = "InventoryButton";
const string BUY = "BuyButton";
const string SKIP = EXIT;

// BATTLEBACKGROUND ------------------------------------------------------------------------------
const float BATTLEBACKGROUND123_WIDTH = 1088 * PIXEL_WIDTH; 
const float BATTLEBACKGROUND123_HEIGHT = 612 * PIXEL_HEIGHT; 
const float BATTLEBACKGROUND3_SCROLLFACTOR = 0.1;
const float BATTLEBACKGROUND2_SCROLLFACTOR = 0.2;
const float BATTLEBACKGROUND1_SCROLLFACTOR = 0.3;

// TUTORIALSCENE ---------------------------------------------------------------------------------
// SPRITES DIMS
const int TUTO_SPRITE_WIDTH = 128;
const int TUTO_SPRITE_HEIGHT = 96;
const int TUTO_WIDTH = TUTO_SPRITE_WIDTH * PIXEL_WIDTH;
const int TUTO_HEIGHT = TUTO_SPRITE_HEIGHT * PIXEL_HEIGHT;
const int TUTO_POPUP_SPRITE_WIDTH = 376;
const int TUTO_POPUP_SPRITE_HEIGHT = 284;
const int TUTO_POPUP_WIDTH = TUTO_POPUP_SPRITE_WIDTH * PIXEL_WIDTH;
const int TUTO_POPUP_HEIGHT = TUTO_POPUP_SPRITE_HEIGHT * PIXEL_HEIGHT;
// ANIM KEYS
const string TUTO_TEXTURE = "Tuto";
const string DARK_PLAIN_TEXTURE = "DarkPlain";
const string TUTO_TALKING_TEXTURE = "TutoTalking";
// POSITIONS
const Vector2D TUTO_POPUP_POS = Vector2D(WIN_WIDTH / 2 - TUTO_POPUP_WIDTH / 2, 0);
const Vector2D RESUME_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2, WIN_HEIGHT - MM_BUTTON_HEIGHT - 5);
const Vector2D TEXT_OFFSET = Vector2D(80, 80);
const Vector2D SKIP_BUTTON_POS = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH / 4 - 8, MM_BUTTON_HEIGHT / 2);
const Vector2D SKIP_BUTTON_DROP_POS = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT / 2);

// STATISTICS FRAME ------------------------------------------------------------------------------
// KEY ANIMATIONS
const string STATISTICS = "StatisticsFrame";
const string LIFEBAR = "LifeBar";
const string MANABAR = "ManaBar";
const string ETHER_METER_FRAME = "EtherMeterFrame";
const string ETHER_METER = "EtherMeter";
const string STATISTICS_NUMBERS = "StatisticsNumbers";
const string ETHER_ANIM = "Ether";

// STATISTICS
const int STATISTICS_WIDTH = 250;
const int STATISTICS_HEIGHT = 28;
const int UI_STATISTICS_WIDTH = 250 * 2.5;
const int UI_STATISTICS_HEIGHT = 28 * 2.5;
const Vector2D UI_STATISTICS_POSITION = Vector2D(WIN_WIDTH / 2 - UI_STATISTICS_WIDTH / 2, 0);
// BARS
const int BAR_WIDTH = 83;
const int BAR_HEIGHT = 10;
const int UI_BAR_WIDTH = 83 * 2.5;
const int UI_BAR_HEIGHT = 10 * 2.5;
const int BAR_ROWS = 4;
const int BAR_COLUMNS = 3;
const int BAR_START = 0;
const int BAR_END = 10;
const int BAR_FRAMERATE = 7;
	// Lifebar
const Vector2D LIFEBAR_POSITION = Vector2D(WIN_WIDTH - 295 * 2 + 1, 15);
	// Manabar
const Vector2D MANABAR_POSITION = Vector2D(WIN_WIDTH / 2 - 258, 15);
// ETHER
const int ETHER_FRAME_WIDTH = 44;
const int ETHER_FRAME_HEIGHT = 26;
const int UI_ETHER_FRAME_WIDTH = ETHER_FRAME_WIDTH * 2.5 + 1;
const int UI_ETHER_FRAME_HEIGHT = ETHER_FRAME_HEIGHT * 2.5;
const Vector2D UI_ETHER_FRAME_POSITION = Vector2D(WIN_WIDTH / 2 - UI_ETHER_FRAME_WIDTH / 2, 0);
const int ETHER_WIDTH = 40;
const int ETHER_HEIGHT = 22;
const int UI_ETHER_WIDTH = 40 * 2.5 + 1;
const int UI_ETHER_HEIGHT = 22 * 2.5;
const Vector2D UI_ETHER_POSITION = Vector2D(WIN_WIDTH / 2 - ETHER_WIDTH * 2.5 / 2, 5);
const int MAX_ETHER = 100;
const int ETHER_ROWS = 4;
const int ETHER_COLUMNS = 2;
const int ETHER_START = 0;
const int ETHER_END = 7;
const int ETHER_FRAMERATE = 8;
const int ETHER_LIMIT = 100;
// COUNTERS
const int N_LIFE_COUNTER = 7;
const int N_MANA_COUNTER = 7;
const int N_ETHER_COUNTER = 4;
const int N_NUMBERS = 12;
const int ST_NUMBERS_WIDTH = 9;
const int ST_NUMBERS_HEIGHT = 18;
const int ST_NUMBERS_ROWS = 6;
const int ST_NUMBERS_COLUMNS = 2;
const Vector2D UI_COUNTDOWN_ETHER_POS = Vector2D(WIN_WIDTH / 2 - (ST_NUMBERS_WIDTH * 1.8 + 6) / 2, 9);
const float COUNTDOWN_TIME = 3.6f;

//MANA -------------------------------------------------------------------------------------------
const int MANA_H = 10;
const int MANA_W = 10;
const int MANA_OFFSET = 10;
const int MANA_VALUE = 5;
const string MANA_NAME = "Mana";
const int MANA_COLUMS = 2;
// ETHER ------------------------------------------------------------------------------------------
const int ETHER_H = 20;
const int ETHER_W = 20;
const int ETHER_VALUE = 1;
// CARDS -----------------------------------------------------------------------------------------
const int MAX_HAND_SIZE = 4;
// CARD REVERSE DIMENSIONS
const int REVERSE_WIDTH = 58;
const int REVERSE_HEIGHT = 93;
// UI CARD COUNTER DIMENSIONS
const int BS_REVERSE_WIDTH = REVERSE_WIDTH * 1.5;
const int BS_REVERSE_HEIGHT = REVERSE_HEIGHT * 1.5;
const int DECK_COUNTER_W = 130;
const int DECK_COUNTER_FRAME_W = 90;
// UI CARD COUNTER POS
const int RIGHT_OFFSET = 5 * REVERSE_WIDTH / 4;
const int LEFT_OFFSET = REVERSE_WIDTH / 2;
const int DOWN_OFFSET = WIN_HEIGHT - REVERSE_HEIGHT * 1.75;
const int CARD_OFFSET_W = 2 * 6;
const int CARD_OFFSET_H = 21 * 1.5;
//CARD DATA
const float BOW_CADENCE = 0.5;
const float SMG_CADENCE = 0.3;
const float ASSAULT_RIFLE_BURST = 25;
const float LASER_KATANA_BURST = 35;
// CARD DIMENSIONS
const int CARD_WIDTH = 58;
const int CARD_HEIGHT = 93;
// CARD ANIMATIONS
const int CARD_NUMROWS = 1;
const int CARD_NUMCOLS = 1;
// UI CARD DIMENSIONS
const int UI_CARD_WIDTH = CARD_WIDTH * 3;
const int UI_CARD_HEIGHT = CARD_HEIGHT * 3;
// UI CARD POSITIONS
const int SELECTED_OFFSET = 60;
const int Y_CARD_POS = WIN_HEIGHT - WIN_HEIGHT / 8 - CARD_HEIGHT / 2;
const int Y_CARD_POS_SELECTED = WIN_HEIGHT - WIN_HEIGHT / 8 - CARD_HEIGHT / 2 - SELECTED_OFFSET;
const int BETWEEN_CARD_SPACE = CARD_WIDTH * 3 / 2;
const int CENTERED_CARD_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2; // Usada para 3 y 1 cartas en mano
	// 4 CARDS IN HAND
const int X1_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 - UI_CARD_WIDTH - BETWEEN_CARD_SPACE;
const int X2_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 - BETWEEN_CARD_SPACE; // Usada para 2 cartas en mano
const int X3_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 + BETWEEN_CARD_SPACE; // Usada para 2 cartas en mano
const int X4_4CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 + UI_CARD_WIDTH + BETWEEN_CARD_SPACE;
	// 3 CARDS IN HAND
const int X1_3CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 - BETWEEN_CARD_SPACE * 2;
const int X3_3CARDS_POS = WIN_WIDTH / 2 - UI_CARD_WIDTH / 2 + BETWEEN_CARD_SPACE * 2;
// UI AMMO AND MANA NUMBERS DIMENSIONS
const int UI_AMMO_NUMBERS_WIDTH = 10;
const int UI_AMMO_NUMBERS_HEIGHT = 15;
const string CARD_AMMO = "CardAmmo";
const string CARDS_NUMBERS = "CardsNumbers";
const int N_CARDS_NUMBERS = 10;
const int CARDS_NUMBERS_WIDTH = 9;
const int CARDS_NUMBERS_HEIGHT = 18;
const int CARDS_NUMBERS_ROWS = 5;
const int CARDS_NUMBERS_COLUMNS = 2;
	// 1ST CARD
const int X1_AMMO_XOFFSET_DECS = -4;
const int X1_AMMO_YOFFSET_DECS = 31;
const int X1_AMMO_XOFFSET_UNITS = 7;
const int X1_AMMO_YOFFSET_UNITS = 29;
const int X1_MANA_XOFFSET_DECS = 7;
const int X1_MANA_YOFFSET_DECS = 70;
const int X1_MANA_XOFFSET_UNITS = 19;
const int X1_MANA_YOFFSET_UNITS = 68;
	// 2ND CARD
const int X2_AMMO_XOFFSET_DECS = 6;
const int X2_AMMO_YOFFSET_DECS = 24;
const int X2_AMMO_XOFFSET_UNITS = 17;
const float X2_AMMO_YOFFSET_UNITS = 23.5;
const int X2_MANA_XOFFSET_DECS = 13;
const int X2_MANA_YOFFSET_DECS = 64;
const int X2_MANA_XOFFSET_UNITS = 25;
const int X2_MANA_YOFFSET_UNITS = 63;
	// 3RD CARD
const int X3_AMMO_XOFFSET_DECS = 26;
const int X3_AMMO_YOFFSET_DECS = 12;
const int X3_AMMO_XOFFSET_UNITS = 37;
const int X3_AMMO_YOFFSET_UNITS = 13;
const int X3_MANA_XOFFSET_DECS = 25;
const int X3_MANA_YOFFSET_DECS = 53;
const int X3_MANA_XOFFSET_UNITS = 37;
const int X3_MANA_YOFFSET_UNITS = 54;
	// 4RD CARD
const int X4_AMMO_XOFFSET_DECS = 36;
const int X4_AMMO_YOFFSET_DECS = 8;
const int X4_AMMO_XOFFSET_UNITS = 47;
const int X4_AMMO_YOFFSET_UNITS = 10;
const int X4_MANA_XOFFSET_DECS = 32;
const int X4_MANA_YOFFSET_DECS = 48;
const int X4_MANA_XOFFSET_UNITS = 44;
const int X4_MANA_YOFFSET_UNITS = 50;
	// CENTERED CARD
const int XC_AMMO_XOFFSET_DECS = 15;
const int XC_AMMO_XOFFSET_UNITS = 26;
const int XC_AMMO_YOFFSET = 18;
const int XC_MANA_XOFFSET_DECS = 19;
const int XC_MANA_XOFFSET_UNITS = 30;
const int XC_MANA_YOFFSET = 58;

// RELICS ----------------------------------------------------------------------------------------

// CHESTSCENE ------------------------------------------------------------------------------------
// KEYS
const string CHEST_BG = "ChestBackground";
const string RELIC_FRAME = "ItemFrame";
const string INFO_FRAME = "ItemInfoFrame";
const string NAME_FRAME = "ItemNameFrame";
// DIMENSIONS
const int RELIC_DIMS = 32 * 4;
const int RELIC_FRAME_DIMS = 38 * 4.2;
const int SPARKS_DIMS = 35 * 5;
const int INFO_FRAME_WIDTH = 72 * 4.2;
const int INFO_FRAME_HEIGHT = 100 * 4.2;
const int NAME_DIMS_OFFSET = 40;
// POSITIONS
const Vector2D CHEST_POS = Vector2D(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 4 + 165);
const Vector2D RELIC_FRAME_POS = Vector2D(WIN_WIDTH / 2 - 79 + 74, WIN_HEIGHT / 4 + 29);
const Vector2D RELIC_POS = Vector2D(WIN_WIDTH / 2 - 79 + 90, WIN_HEIGHT / 4 + 45);
const Vector2D RELIC_SPARKS_POS = Vector2D(WIN_WIDTH / 2 - 79 + 74, WIN_HEIGHT / 4 + 20);
const Vector2D INFO_FRAME_POS = Vector2D(WIN_WIDTH - INFO_FRAME_WIDTH - 60, WIN_HEIGHT / 6 + 20);
const Vector2D CHEST_EXIT_BUTTON_POS = Vector2D(WIN_WIDTH - MM_BUTTON_WIDTH - 30, WIN_HEIGHT - MM_BUTTON_HEIGHT - 30);

// NUMBERS ---------------------------------------------------------------------------------------
const int NUMBERS_WIDTH = 130;
const int NUMBERS_HEIGHT = 250;
const int NUMBERS_SPRITE_COLUMS = 2;
const int NUMBERS_SPRITE_ROWS = 5;
const int NUM_RENDER_W = NUMBERS_WIDTH / 4;
const int NUM_RENDER_H = NUMBERS_HEIGHT / 3;

// LOGO ------------------------------------------------------------------------------------------
const int LOGO_WIDTH = 404;
const int LOGO_HEIGHT = 284;
const Vector2D LOGO_POSITION = {WIN_WIDTH / 2 - LOGO_WIDTH / 2, WIN_HEIGHT / 8};
const int LOGO_ROWS = 1;
const int LOGO_COLUMNS = 4;
const int LOGO_FRAME_WIDTH = 200;
const int LOGO_FRAME_HEIGHT = 140;
const string LOGO_ANIM_KEY = "LogoIdle";
const int LOGO_START_FRAME = 0;
const int LOGO_END_FRAME = 3;
const int LOGO_FRAME_RATE = 4;

// NODOS -----------------------------------------------------------------------------------------
const string NODE_MAP_JSON_ROOT = "../Game/src/data/game.map.json";

const int HEIGHT = 17;

const string BATTLE_NODE_TEXTURE_KEY = "BattleNode";
const string SHOP_NODE_TEXTURE_KEY = "ShopNode";
const string CHEST_NODE_TEXTURE_KEY = "ChestNode";
const string EVENT_NODE_TEXTURE_KEY = "EventNode";

const int NODE_FRAME_WIDTH = 32;
const int NODE_FRAME_HEIGHT = 32;
const int NODE_FRAME_ROWS = 6;
const int NODE_FRAME_COLUMNS = 3;

const int NODE_WIDTH = NODE_FRAME_WIDTH * PIXEL_WIDTH;
const int NODE_HEIGHT = NODE_FRAME_HEIGHT * PIXEL_HEIGHT;
const int NODE_DISTANCE = 50;
const int CONECTION_OFFSET = NODE_WIDTH / 2 - 3;

const int NODE_POSITIONS_X[5] = {
	WIN_WIDTH / 6 - NODE_WIDTH / 2,
	WIN_WIDTH / 6 * 2 - NODE_WIDTH / 2,
	WIN_WIDTH / 6 * 3 - NODE_WIDTH / 2,
	WIN_WIDTH / 6 * 4 - NODE_WIDTH / 2,
	WIN_WIDTH / 6 * 5 - NODE_WIDTH / 2 };
const int NODE_POSITION_Y = NODE_DISTANCE + NODE_HEIGHT;

const int NODE_BUTTON_ONOUT_START_FRAME = 0;
const int NODE_BUTTON_ONOUT_END_FRAME = 0;
const int NODE_BUTTON_ONOVER_START_FRAME = 2;
const int NODE_BUTTON_ONOVER_END_FRAME = 14;
const int NODE_BUTTON_ONCLICK_START_FRAME = 1;
const int NODE_BUTTON_ONCLICK_END_FRAME = 1;
const int NODE_BUTTON_ONLOCKED_START_FRAME = 15;
const int NODE_BUTTON_ONLOCKED_END_FRAME = 15;
const int NODE_BUTTON_ONCOMPLETED_START_FRAME = 16;
const int NODE_BUTTON_ONCOMPLETED_END_FRAME = 17;

// STUDIO ----------------------------------------------------------------------------------------
const int STUDIO_WIDTH = 84 * 3;
const int STUDIO_HEIGTH = 18 * 3;
const Vector2D STUDIO_POSITION = Vector2D(WIN_WIDTH / 15, WIN_HEIGHT - WIN_HEIGHT / 7.6);

// MESSAGE ---------------------------------------------------------------------------------------
const int MESSAGE_W = 300;
const int MESSAGE_H = 200;
const int MESSAGE_X = (WIN_WIDTH / 2) - 150;
const int MESSAGE_Y = WIN_HEIGHT / 4;

// RELIQUIAS -------------------------------------------------------------------------------------
const string ALMACENAMIENTO_CUANTICO = "Almacenamiento cuantico";
const string HOVERBOARD = "Hoverboard";
const string ENGRANAJE_AUREO = "Engranaje Aureo";
const string BRAZALETE_IONES = "Brazalete de Iones";
const string REGALO = "Regalo";
const string RELOJ_DIGITAL = "Reloj Digital";
const string COLLAR_GOTICO = "Collar Gotico";
const string CINTURON_HERRAMIENTAS = "Cinturon de Herramientas";
const string CETRO_PAPAL = "Cetro Papal";
const string LIBRO_PERDIDO = "Libro Perdido";
const string TAZA_CAFE = "Taza de Cafe";
const string BOTELLA_MINIATURA = "Barco en Miniatura";

//ENEMY GENERATOR---------------------------------------------------------------------------------
const int MELEE_RADIUS = 400;
const int RANGED_RADIUS = 600;
const int TANK_RADIUS = 500;

const int STARTING_TIME_PER_WAVE = 15000;

//SOUNDS
const string MELEE_DEATH_SOUND = "MeleeDeath";
const string MELEE_HIT_SOUND = "MeleeHit";
const string RANGED_DEATH_SOUND = "RangedDeath";
const string RANGED_HIT_SOUND = "RangedHit";
const string TANK_DEATH_SOUND = "TankDeath";
const string TANK_HIT_SOUND = "TankHit";
const string PLAYER_HIT_SOUND = "PlayerHit";
const string HOVER_OVER_BUTTON_SOUND = "HoverOverButton";
const string BUTTON_PRESSED_SOUND = "ButtonPressed";
const string LOAD_EXIT_SOUND = "LoadExit";
const string CHEST_OPENING_SOUND = "ChestOpening";
const string FASE_COMPLETED_SOUND = "FaseCompleted";
const string ETHER_PICK = "EtherPick";
const string MANA_PICK = "ManaPick";
const string HEAL_SOUND = "Heal";
const string SLASH_SOUND = "Slash";
const string SHOT_SOUND = "Shot";
const string ASSASSIN_HIT_SOUND = "AssassinHit";
const string ASSASSIN_DEATH_SOUND = "AssassinDeath";
const string BUY_SOUND = "BuySound";
const string CANT_BUY_SOUND = "CantBuySound";
const string BOSS_HIT_SOUND = "BossHit";
const string BOSS_DEATH_SOUND = "BossDeath";

//MUSICS
const string BATTLE_MUSIC = "BattleMusic";
const string MAIN_MUSIC = "MenusMusic";
const string SHOP_MUSIC = "ShopMusic";
const string INIT_MUSIC = "InitMusic";
const string FINAL_MUSIC = "EndMusic";
const string DEATH_MELODY = "Death";

//SHOP ------------------------------------------------------------------------------------------
const int SHOP_NUMBER_OF_CARDS = 4;
const int SHOP_CARD_SELECTED_POSY = WIN_HEIGHT - CARD_HEIGHT * 4 - 100;
const int SHOP_CARD_UNSELECTED_POSY = WIN_HEIGHT - CARD_HEIGHT * 4 - 50;
const int SHOP_CARD_OFFSET_X = 300;
const int SHOP_CARD_PRICE_WIDTH = 100;
const int SHOP_CARD_PRICE_HEIGHT = 50;
const Vector2D SHOP_BUYBUTTON_POSITION = Vector2D(WIN_WIDTH / 2 + 10, WIN_HEIGHT - 100);
const int SHOP_MONEY_WIDTH = 100;
const int SHOP_MONEY_HEIGHT = 50;
const int SHOP_MONEY_FRAME_WIDTH = CARD_WIDTH * PIXEL_WIDTH * 1.5;
const int SHOP_MONEY_FRAME_HEIGHT = 16 * PIXEL_HEIGHT * 1.5;
const Vector2D SHOP_MONEY_POSITION = Vector2D(WIN_WIDTH / 2 - SHOP_MONEY_FRAME_WIDTH + 20, WIN_HEIGHT - 95);
const Vector2D SHOP_EXITBUTTON_POSITION = Vector2D(5, 5);
const Vector2D SHOP_MONEY_FRAME_POSITION = Vector2D(WIN_WIDTH / 2 - SHOP_MONEY_FRAME_WIDTH - 20, WIN_HEIGHT - 100);
const Vector2D SHOP_MONEY_COIN_POSITION = Vector2D(WIN_WIDTH / 2 - 32 * PIXEL_WIDTH - 10, WIN_HEIGHT - 75 - 32 * PIXEL_HEIGHT / 2);
const int COIN_WIDHT = 32 * PIXEL_WIDTH;
const int COIN_HEIGHT = 32 * PIXEL_HEIGHT;

// OPTIONS -------------------------------------------------------------------------------------
const string OPTIONS_JSON_ROOT = "../Game/src/data/game.options.json";
const SDL_Rect MUSIC_RECT = { WIN_WIDTH / 3 - 200 , WIN_HEIGHT / 3, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const SDL_Rect FX_RECT = { WIN_WIDTH / 3 - 200 , MUSIC_RECT.y + MUSIC_RECT.h + 10, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const SDL_Rect FULL_WINDOW_RECT = { WIN_WIDTH / 3 - 200 , FX_RECT.y + FX_RECT.h + 10, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const SDL_Rect PERIPHERAL_RECT = { WIN_WIDTH / 3 - 200 , FULL_WINDOW_RECT.y + FULL_WINDOW_RECT.h + 10, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const SDL_Rect GAMEPAD_CONNECTION_RECT = { WIN_WIDTH / 2 - 200 , PERIPHERAL_RECT.y + PERIPHERAL_RECT.h + 20, MM_BUTTON_WIDTH, MM_BUTTON_HEIGHT };
const string GAMEPAD_CONNECTION_TEXT = "No se detectó ningún mando";
const Animation ONOUT_OPTIONS_ARROW = Animation(0, 0, 7, -1);
const Animation ONOVER_OPTIONS_ARROW = Animation(1, 1, 7, -1);
const Animation ONCLICK_OPTIONS_ARROW = Animation(2, 2, 7, -1);

//POSTGAME SCENE ------------------------------------------------------------------------------------------
const Vector2D POSTGAME_EXITBUTTON_POSITION = Vector2D(1000, 650);
const Vector2D SPOTLIGHT_POSITION = Vector2D(765, 500);
const Vector2D CARD_CREATION_POSITION = Vector2D(817, 328);
const Vector2D NEW_CARD_POSITION = Vector2D(800, 198);
const float NEXT_EVENT_TIMER = 0.5;


//SPAWNS DE OLEADAS PARA LOS PRIMEROS 4 NODOS
//LOS VALORES GUARDADOS SON LAS PROBABILIDADES DE OLEADAS EN ORDEN
//LOS PORCENTAJES SON ACUMULATIVOS PARA REDUCIR OPERACIONES (ej, si son 15%, 50%, 35%, se guardarian como {15, 65, 100})
const int STARTING_SPAWNS[7][3] = {
	{100, 100, 100},
	{85, 95, 100},
	{70, 90, 100},
	{0, 100, 100},
	{40, 80, 100},
	{0, 0, 100},
	{25, 75, 100}
};

//SPAWNS DE OLEADAS PARA EL RESTO DE NODOS
//HAY UN TOTAL DE 7 TIPOS DE OLEADAS, PARA MAS INFORMACION CONSULTAR EXCEL EN LA CARPETA DE PROYECTOS
const int STANDARD_SPAWNS[30][7] = {
	{50, 80, 100, 100, 100, 100, 100},
	{46, 75, 94, 97, 97, 99, 100},
	{42, 70, 88, 94, 94, 98, 100},
	{38, 65, 82, 91, 91, 97, 100},
	{34, 60, 76, 88, 88, 96, 100},
	{0, 0, 0, 100, 100, 100, 100},
	{30, 55, 70, 85, 85, 95, 100},
	{28, 52, 66, 82, 82, 94, 100},
	{26, 49, 62, 79, 79, 93, 100},
	{24, 46, 58, 76, 76, 92, 100},
	{22, 43, 54, 73, 73, 91, 100},
	{0, 0, 0, 0, 0, 100, 100},
	{21, 40, 50, 69, 70, 90, 100},
	{19, 37, 47, 66, 68, 90, 100},
	{17, 34, 44, 62, 65, 89, 100},
	{15, 31, 41, 51, 55, 81, 100},
	{13, 28, 38, 48, 53, 81, 100},
	{0, 0, 0, 0, 0, 0, 100},
	{11, 25, 35, 50, 56, 85, 100},
	{9, 22, 32, 47, 54, 84, 100},
	{7, 19, 29, 44, 52, 83, 100},
	{5, 16, 26, 41, 50, 82, 100},
	{3, 13, 23, 38, 48, 81, 100},
	{0, 0, 0, 0, 100, 100, 100},
	{2, 10, 19, 34, 46, 80, 100},
	{0, 6, 14, 29, 43, 78, 100},
	{0, 4, 11, 24, 40, 76, 100},
	{0, 2, 8, 19, 37, 74, 100},
	{0, 0, 5, 14, 34, 72, 100},
	{0, 0, 0, 0, 30, 70, 100}
};

//OLEADAS
const int WAVES[7][3] = {
	{8, 0, 0},
	{5, 3, 0},
	{0, 8, 0},
	{6, 0, 1},
	{0, 0, 4},
	{4, 2, 1},
	{0, 4, 2}
};

//CALCULO DINERO

const float ENEMYFACTOR = 3.75;
const float DAMAGEFACTOR = 0.25;
const float MINTIME[12] = {60, 70, 80, 90, 100, 110, 120, 125, 130, 135, 140, 145};

// GUARDADO

const string SAVE_FILENAME = "../Game/src/data/game.playerData.json";


// CINEMATICS
const int CINEMATIC_WIDTH = 544;
const int CINEMATIC_HEIGHT = 306;

const string CINEMATIC_INITIAL_NAME = "InitialCinematic";
const int CINEMATIC_INITIAL_ROWS = 7;
const int CINEMATIC_INITIAL_COLS = 7;
const Animation CINEMATIC_INITIAL_ANIMATION = Animation(0, 6, 0.5f, 1);

const string CINEMATIC_FINAL_NAME = "FinalCinematic";
const int CINEMATIC_FINAL_ROWS = 7;
const int CINEMATIC_FINAL_COLS = 7;
const Animation CINEMATIC_FINAL_ANIMATION = Animation(0,49,2,1);

const Vector2D QUIT_CINEMATIC_BUTTON_POS = Vector2D(WIN_WIDTH / 2 - MM_BUTTON_WIDTH / 2, WIN_HEIGHT - MM_BUTTON_HEIGHT - 40);
const Vector2D QUIT_CINEMATICFRAME_BUTTON_POS = QUIT_CINEMATIC_BUTTON_POS - FRAME_OFFSET;

//STRUCTS

struct AnimatorInfo {
	string key;
	int w, h;
	int fw, fh;
	int rows, cols;

	AnimatorInfo() : key("null"), w(20), h(20), fw(20), fh(20), rows(1), cols(1) {}
	//Con constantes para botones gen�ricos
	AnimatorInfo(string _k) : key(_k), w(MM_BUTTON_WIDTH), h(MM_BUTTON_HEIGHT), fw(BUTTON_SPRITE_WIDTH), fh(BUTTON_SPRITE_HEIGHT),
		rows(BUTTON_SPRITE_ROWS), cols(BUTTON_SPRITE_COLUMS) { }
	//Con par�metros espec�ficos
	AnimatorInfo(string _k, int _w, int _h, int _fw = BUTTON_SPRITE_WIDTH, int _fh = BUTTON_SPRITE_HEIGHT,
		int _r = BUTTON_SPRITE_ROWS, int _c = BUTTON_SPRITE_COLUMS) :
		key(_k), w(_w), h(_h), fw(_fw), fh(_fh), rows(_r), cols(_c) { }
};
#endif