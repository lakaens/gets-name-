#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleScene1.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "ModuleParticlesEnemies.h"
#include "ModuleParticlesGrenade.h"
#include "ModuleParticlesGrenade1.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleCinematic.h"
#include "ModuleUI.h"
#include "ModuleFonts.h"
#include "ModuleSaveData.h"
#include "ModuleTEX.h"
#include "ModulePlayer2.h"

#include<stdio.h>
#include<string.h>


ModuleMenu::ModuleMenu()
{
	background.x = 10;
	background.y = 0;
	background.w = 256;
	background.h = 224;

	grenades.x = 54;
	grenades.y = 225;
	grenades.w = 20;
	grenades.h = 20;

	newmode.PushBack({118, 125, 22, 5 });
	newmode.PushBack({ 118, 133, 22, 5 });
	newmode.speed = 0.2f;
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading menu scene");

	App->player2->torevive = 0;

	App->player->vides = 3;
	App->player2->vides = 3;
	App->UI->grenade = 3;
	App->player->move2 = true;
	App->player2->move2 = true;

	App->player2->move2 = true;
	App->player2->checkwaterdead = false;
	App->player2->checkwaterdead2 = false;
	App->player2->checkwaterdead3 = false;
	App->player->move2 = true;

	App->UI->grenade = 3;
	App->player->vides = 3;

	if (App->player->vides == 3)
		App->UI->score = 0;

	//Initialize audio
	check_audio = true;

	//Initialize camera and others (prepare it for use)
	App->render->camera.x = App->render->camera.y = 0;
	App->scene_1->cont = 0;

	App->player->position.x = App->fade->start_x;
	App->player->position.y = App->fade->start_y;

	if (App->player2->twoplayerson) {
		App->player2->position.x = 130;
		App->player2->position.y = 135;
	}
	App->scene_1->start1 = true;
	App->scene_1->start2 = false;
	App->scene_1->start3 = false;
	App->scene_1->start4 = false;
	App->scene_1->start5 = false;

	return true;
}

// UnLoad assets
bool ModuleMenu::CleanUp()
{
	
	LOG("Unloading menu scene");
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{
	update_status ret = UPDATE_CONTINUE;
	
	if (check_audio) {
		App->audio->play_music1();
		check_audio = false;
	}

	if (!App->render->Blit(App->TEX->graphics, 0, SCREEN_HEIGHT - 224, &background, 0.75f))
		ret = UPDATE_ERROR;

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN || App->input->buttonB == KEY_STATE::KEY_DOWN || App->input->buttonB2 == KEY_STATE::KEY_DOWN) {

		App->audio->play_fx2();
		move_y += 16;

		if (move_y == 182) {
			move_y -= 16 * 4;
		}
	}
	current_animation = &newmode;
	r = current_animation->GetCurrentFrame();
	App->render->Blit(App->TEX->newmodetxt, 161, 134, &r);

	App->render->Blit(App->TEX->grenade, 71, move_y, &grenades, 0.75f);


	if ((App->input->keyboard[SDL_SCANCODE_RETURN] == 1 && KEY_DOWN || App->input->buttonA == KEY_STATE::KEY_DOWN || App->input->buttonA2 == KEY_STATE::KEY_DOWN) && move_y == 118) {
		App->render->UP = false;
		App->player2->twoplayerson = false;
		App->fade->FadeToBlack(this, App->cinematic, 3);
		App->player2->twoplayerson = false;
	}

	if ((App->input->keyboard[SDL_SCANCODE_RETURN] == 1 && KEY_DOWN || App->input->buttonA == KEY_STATE::KEY_DOWN || App->input->buttonA2 == KEY_STATE::KEY_DOWN) && move_y == 118 + 16) {
		App->render->UP = false;
		App->player2->twoplayerson = true;
		App->fade->FadeToBlack(this, App->cinematic, 3);
	}

	sprintf_s(App->UI->str1, "%i", App->savedata->savescore_p1);
	App->fonts->BlitText(18, 27, App->savedata->font_score, App->UI->str1);

	sprintf_s(App->UI->str2, "%i", App->savedata->savescore);
	App->fonts->BlitText(104, 27, App->savedata->font_score2, App->UI->str2);

	sprintf_s(App->UI->str2, "%i", App->savedata->savescore2p);
	App->fonts->BlitText(200, 27, App->savedata->font_score, App->UI->str2);

	return ret;
}