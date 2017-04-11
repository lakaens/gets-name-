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
#include "ModuleCollision.h"

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
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	App->player->Disable();
	App->collision->Disable();
	LOG("Loading menu scene");

	graphics = App->textures->Load("menu.png");
	grenade = App->textures->Load("items&HUD&snake.png");

	App->audio->play_music1();
	return true;
}

// UnLoad assets
bool ModuleMenu::CleanUp()
{
	App->player->Disable();
	LOG("Unloading menu scene");
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{
	update_status ret = UPDATE_CONTINUE;


	if (!App->render->Blit(graphics, 0, SCREEN_HEIGHT - 224, &background, 0.75f))
		ret = UPDATE_ERROR;

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN) {

		App->audio->play_fx2();
		move_y += 16;

		if (move_y == 182) {
			move_y -= 16 * 4;
		}
	}

	App->render->Blit(grenade, 71, move_y, &grenades, 0.75f);


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 && KEY_DOWN && move_y == 118) {
		App->render->UP = false;
		App->fade->FadeToBlack(this, App->scene_1, 3);

	}
	return ret;
}