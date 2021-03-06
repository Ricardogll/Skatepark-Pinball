#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
	ray_on = false;
	sensed = false;
	maprect.x = 0;
	maprect.y = 0;
	maprect.w = 596;
	maprect.h = 945;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	//gameover = App->textures->Load("pinball/gameover.png");
	intro = App->textures->Load("pinball/start.png");
	//App->player->Disable();

	App->renderer->camera.x = App->renderer->camera.y = 0;
	spring = App->textures->Load("pinball/muelle.png");
	flipper1 = App->textures->Load("pinball/flipper.png"); 
	flipper2 = App->textures->Load("pinball/flipperl.png");
	map = App->textures->Load("pinball/SkateparkMap.png");
	power = App->textures->Load("pinball/Power.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");
	spring_fx = App->audio->LoadFx("pinball/springfx2.wav");
	flipper_fx = App->audio->LoadFx("pinball/FlipperUp1.wav");
	start_fx = App->audio->LoadFx("pinball/CoinIn.wav");
	bounce_fx = App->audio->LoadFx("pinball/Bumper11.wav");
	wall_fx = App->audio->LoadFx("pinball/BallCollision1.wav");
	//skatepark_music = App->audio->LoadFx("pinball/skateparkmusic.ogg");
	App->audio->PlayMusic("pinball/skateparkmusic.ogg");
	//sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

	/*int prueba[8] = { 10,10,
		10,20,
		20,20,
		20,10
	};
	b2Vec2 test[4];
	test[0].x = 0;
	test[1].x = 10;
	test[2].x = 10;
	test[3].x = 0;
	test[0].y = 0;
	test[1].y = 0;
	test[2].y = 10;
	test[3].y = 10;
*/

	//int SkateparkMap[88] = {
	//	100, 335,
	//	21, 228,
	//	11, 140,
	//	82, 51,
	//	210, 6,
	//	345, 7,
	//	473, 53,
	//	540, 113,
	//	575, 180,
	//	583, 216,
	//	583, 816,
	//	550, 816,
	//	550, 315,
	//	512, 391,
	//	483, 435,
	//	435, 471,
	//	471, 520,
	//	512, 581,
	//	532, 644,
	//	540, 692,
	//	538, 764,
	//	527, 820,
	//	475, 878,
	//	410, 909,
	//	360, 933,
	//	359, 966,
	//	658, 1025,
	//	665, 1383,
	//	22, 1427,
	//	30, 957,
	//	217, 945,
	//	225, 936,
	//	149, 909,
	//	90, 866,
	//	50, 787,
	//	63, 709,
	//	65, 613,
	//	47, 541,
	//	37, 573,
	//	26, 586,
	//	9, 584,
	//	8, 420,
	//	33, 375,
	//	67, 351
	//};
	int SkateparkMap[106] = {
		23, 953,
		225, 934,
		148, 908,
		89, 864,
		50, 786,
		64, 710,
		68, 630,
		48, 541,
		32, 583,
		11, 587,
		8, 418,
		32, 374,
		62, 351,
		86, 340,
		45, 318,
		25, 304,
		34, 286,
		52, 270,
		20, 227,
		10, 173,
		36, 105,
		99, 49,
		162,12,
		208, 3,
		346, 5,
		470, 48,
		540, 112,
		566, 161,
		576, 181,
		584, 213,
		584, 815,
		550, 815,
		550, 314,
		517, 386,
		488, 428,
		501, 436,
		507, 448,
		504, 461,
		482, 471,
		441, 482,
		485, 539,
		512, 582,
		531, 637,
		540, 691,
		537, 766,
		527, 820,
		478, 873,
		415, 908,
		360, 932,
		580, 945,
		598, 1345,
		300, 1509,
		9, 1334
	};
	int SkateparkMap2[24] = {
		102, 653,
		113, 703,
		145, 753,
		177, 784,
		188, 795,
		188, 788,
		193, 785,
		203, 780,
		180, 768,
		149, 748,
		117, 700,
		108, 655
	};
	int SkateparkMap3[30] = {
		480, 652,
		475, 680,
		462, 713,
		440, 740,
		412, 761,
		378, 779,
		401, 777,
		398, 790,
		398, 789,
		393, 798,
		422, 771,
		452, 740,
		467, 714,
		474, 691,
		484, 656
	};
	int SkateparkMap4[22] = {
		91, 795,
		107, 833,
		141, 863,
		183, 880,
		224, 881,
		233, 854,
		195, 848,
		150, 816,
		122, 786,
		107, 763,
		93, 779
	};
	int SkateparkMap5[22] = {
		353, 850,
		350, 876,
		402, 877,
		446, 858,
		480, 830,
		493, 800,
		484, 764,
		466, 780,
		442, 809,
		416, 833,
		386, 846
	};
	int SkateparkMap6[8] = {
		167, 641,
		166, 685,
		178, 698,
		205, 700
	};
	int SkateparkMap7[8] = {
		380, 702,
		400, 701,
		419, 688,
		420, 643
	};
	int SkateparkMap8[22] = {
		338, 541,
		373, 521,
		406, 520,
		432, 535,
		445, 555,
		453, 588,
		441, 563,
		427, 540,
		405, 525,
		376, 525,
		343, 543
	};
	int SkateparkMap9[26] = {
		225, 507,
		171, 441,
		137, 417,
		107, 408,
		78, 419,
		55, 452,
		61, 429,
		92, 405,
		121, 402,
		148, 414,
		175, 436,
		196, 458,
		228, 500
	};
	int SkateparkMap10[20] = {
		339, 371,
		365, 381,
		387, 395,
		402, 412,
		408, 431,
		416, 432,
		410, 411,
		397, 392,
		374, 377,
		348, 367
	};
	int SkateparkMap11[8] = {
		239, 560,
		244, 582,
		252, 583,
		248, 556
	};
	int SkateparkMap12[26] = {
		516, 278,
		527, 247,
		527, 208,
		514, 170,
		489, 134,
		456, 95,
		457, 90,
		487, 119,
		515, 158,
		529, 196,
		535, 225,
		532, 252,
		523, 281
	};
	int SkateparkMap13[20] = {
		369, 124,
		371, 155,
		384, 180,
		408, 194,
		436, 197,
		436, 190,
		403, 180,
		383, 163,
		376, 136,
		375, 124
	};

	int SkateparkMap14[22] = {
		358, 102,
		349, 94,
		335, 102,
		317, 103,
		279, 112,
		280, 119,
		317, 117,
		336, 112,
		343, 116,
		354, 115,
		358, 109
	};
	int SkateparkMap15[10] = {
		201, 41,
		262, 32,
		326, 37,
		317, 46,
		211, 49
	};
	int SkateparkMap16[8] = {
		47, 197,
		71, 239,
		82, 230,
		60, 190
	};

	//muelle = App->physics->CreateRectangle(561,517,25,101,b2_dynamicBody, WALL);
	//muelle2 = App->physics->CreateRectangle(560, 527, 10, 10, b2_staticBody,WALL);
	
	PhysBody* pb;
	b2Filter filterspring;
	filterspring.categoryBits = BOUNCE;
	filterspring.maskBits = -1;

	muelle = App->physics->CreateRectangle(555, 517, 31, 100, b2_dynamicBody, WALL);
	muelle2 = App->physics->CreateRectangle(564, 592, 10, 10, b2_staticBody, WALL);

	b2DistanceJointDef spring;
	spring.type = e_distanceJoint;
	spring.bodyA = muelle->body;
	spring.bodyB = muelle2->body;
	spring.localAnchorA.Set(0, PIXEL_TO_METERS(25));// 534, 567);
	spring.localAnchorB.Set(0, 0);//563, 532);
	spring.length = 0.0f;
	spring.frequencyHz = 20.0f;
	spring.dampingRatio = 1;

	App->physics->world->CreateJoint(&spring);


	muelle->body->GetFixtureList()->SetFilterData(filterspring);
	muelle2->body->GetFixtureList()->SetFilterData(filterspring);

	int SkateparkMap17[16] = {
		564, 618,
		564, 526,
		552, 526,
		552, 517,
		583, 517,
		583, 526,
		573, 526,
		573, 618
	};
	int SkateparkFlipperDL[18] = {
		213, 785,
		203, 791,
		200, 801,
		202, 810,
		212, 815,
		270, 806,
		277, 804,
		277, 797,
		225, 787
	};
	int SkateparkFlipperDR[18] = {
		306, 797,
		368, 785,
		379, 790,
		383, 799,
		380, 810,
		372, 813,
		356, 812,
		314, 806,
		307, 803
	};
	int SkateparkFlipperTL[18] = {
		97, 340,
		46, 316,
		37, 306,
		38, 293,
		51, 287,
		62, 293,
		80, 311,
		104, 335,
		102, 340
	};
	int SkateparkFlipperTR[16] = {
		480, 440,
		424, 473,
		425, 478,
		431, 479,
		486, 468,
		497, 460,
		498, 452,
		491, 440
	};
	int SkateparkBounceR[8] = {
		380, 699,
		375, 695,
		415, 638,
		419, 642
	};
	int SkateparkBounceL[10] = {
		167, 641,
		206, 698,
		211, 695,
		172, 638,
		378, 602
	};

	//PhysBody* pb;
	b2Filter filterwall;
	filterwall.categoryBits = WALL;
	filterwall.maskBits = -1;

	b2Filter filterbounce;
	filterbounce.categoryBits = BOUNCE;
	filterbounce.maskBits = BALL;
	//circle para que rebote bola en lado izquierdo
	pb=App->physics->CreateCBounce(20, 602, 18, 2.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	//App->physics->CreateChain(0, 0, SkateparkMap, 88, b2_staticBody,WALL);
	pb=App->physics->CreateChain(0, 0, SkateparkMap, 106, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap2, 24, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap3, 30, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap4, 20, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap5, 22, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	//bounce6=App->physics->CreateChain(0, 0, SkateparkMap6, 8, b2_staticBody, BOUNCE);
	//bounce7=App->physics->CreateChain(0, 0, SkateparkMap7, 8, b2_staticBody, BOUNCE);
	pb = App->physics->CreateChain(0, 0, SkateparkMap6, 8, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap7, 8, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkBounceR, 8, 3.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkBounceL, 8, 3.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap8, 22, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkMap9, 26, 2.0f,b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap10, 20, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap11, 8, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateChain(0, 0, SkateparkMap12, 26, b2_staticBody, WALL);
	pb->body->GetFixtureList()->SetFilterData(filterwall);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkMap13, 20, 1.0f,b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkMap14, 22, 1.7f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkMap15, 10, 2.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateBounce(0, 0, SkateparkMap16, 8, 2.0f,b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	//App->physics->CreateChain(0, 0, SkateparkFlipperDL, 18, b2_staticBody, WALL);//Flippers D= down, T=top, R=right, L=left.
	//App->physics->CreateChain(0, 0, SkateparkFlipperDR, 18, b2_staticBody, WALL);
	//App->physics->CreateChain(0, 0, SkateparkFlipperTL, 18, b2_staticBody, WALL);
	//App->physics->CreateChain(0, 0, SkateparkFlipperTR, 16, b2_staticBody, WALL);

	pb = App->physics->CreateCBounce(388, 577, 28, 1.0f,b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateCBounce(106, 465, 28, 0.5f ,b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateCBounce(346, 444, 18, 2.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateCBounce(479, 252, 18, 2.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateCBounce(448, 151, 14, 1.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;
	pb = App->physics->CreateCBounce(420, 124, 14, 1.0f, b2_staticBody, BOUNCE);
	pb->body->GetFixtureList()->SetFilterData(filterbounce);
	pb->listener = this;

	lose=App->physics->CreateRectangleSensor(300, 1280, 300, 500, DEAD);
	lose->body->GetFixtureList()->SetFilterData(filterwall);
	lose->listener = this;

	/*b2Filter filterstart;
	filterwall.categoryBits = START;
	filterwall.maskBits = BALL;

	start = App->physics->CreateRectangleSensor(571, 527, 39, 401, START);
	start->body->GetFixtureList()->SetFilterData(filterstart);
	start->listener = this;*/

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	
	App->textures->Unload(flipper1);
	App->textures->Unload(flipper2);
	App->textures->Unload(map);
	App->textures->Unload(power);
	App->textures->Unload(spring);
	
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	currentTime = SDL_GetTicks();

	//http://www.vpforums.org/Tutorials/Sounds/SndLib1.html
	
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT && can_play)
	{
		//variable que vaya aumentando en el update y sea la variable y del applydforce
		muelle->body->ApplyForceToCenter({ 0,spring_force }, true);

		if (spring_force<22000 && lastTime + 10<currentTime) {
			spring_force += 300;
			lastTime = currentTime;
			//LOG("LastTime=%d, spring_force=%f", currentTime, spring_force);
		}
	}	
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP && can_play) {
		spring_force = 0;
		App->audio->PlayFx(spring_fx);
	}
	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {
		App->textures->Unload(intro);
		can_play = true;
		App->audio->PlayFx(start_fx);
		//App->player->Enable();
	}



	// Prepare for raycast ------------------------------------------------------
	
	App->renderer->Blit(map, 0, 0, &maprect);
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}
	
	int x, y;
	muelle->GetPosition(x, y);
	App->renderer->Blit(spring, x, y, NULL, 1.0f, muelle->GetRotation());
	App->renderer->Blit(power, 548, 619, NULL, 1.0f);
	App->renderer->Blit(flipper1, 309, 780, NULL, 1.0f, App->physics->dr_flipper->GetRotation(), 64, 16);
	App->renderer->Blit(flipper2, 195, 780, NULL, 1.0f, App->physics->dl_flipper->GetRotation(), 18, 19);
	App->renderer->Blit(flipper1, 420, 438, NULL, 1.0f, App->physics->tr_flipper->GetRotation() - 20, 64, 20);
	App->renderer->Blit(flipper2, 28, 285, NULL, 1.0f, App->physics->tl_flipper->GetRotation() + 32, 18, 18);
	App->renderer->Blit(intro, 100, 300, NULL);
	/*if (App->player->lifes == 0 && flag==true) {
		App->renderer->Blit(gameover, 100, 300, NULL);
	}*/
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;
	
	
	
	if ((bodyA->body == App->player->ball->body && bodyB->body == lose->body) || (bodyA->coll == BALL && bodyB->coll == DEAD)
		|| (bodyB->coll == BALL && bodyA->coll == DEAD)) {
		
		//App->player->loselife();
		App->player->lose_life = true;
		
	}
	else
		
	if ((bodyB->coll == BALL && bodyA->coll == BOUNCE)|| (bodyA->coll == BALL && bodyB->coll == BOUNCE)) {
		LOG("POOOOOOOOOOOOOOOIIIIIIIIIIIIIINTS");
		App->player->points += 100;
		App->audio->PlayFx(bounce_fx);
	}


	if((bodyA->coll==BALL && bodyB->coll==WALL)|| (bodyB->coll == BALL && bodyA->coll == WALL)){
	
		App->audio->PlayFx(wall_fx);
	
	}

	/*if (bodyA->coll == BALL && bodyB->coll == START) {
		LOG("STAAAAAAAAAAAAAAAAAAAAAART");
	}*/
	
	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
