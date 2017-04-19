#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleFadeToBlack.h"
#include "ModuleScene1.h"
#include "ModuleScene2.h"
#include "ModuleMenu.h"
#include "ModuleRender.h"
#include "ModuleEND.h"
#include "ModulePlayer.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleFadeToBlack::ModuleFadeToBlack()
{
	screen = {0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE};
}

ModuleFadeToBlack::~ModuleFadeToBlack()
{}

// Load assets
bool ModuleFadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
update_status ModuleFadeToBlack::Update()
{
	if(current_step == fade_step::none)
		return UPDATE_CONTINUE;

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch(current_step)
	{
		case fade_step::fade_to_black:
		{
			
			if(now >= total_time)
			{
				off->CleanUp();
				off->Disable();
				on->Enable();
				if ((App->fade->on == App->END) || (App->fade->on == App->scene_1)) {
					App->render->camera.y = 0;
					App->player->position.x = 100;
					App->player->position.y = 220;
				}

				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = fade_step::fade_from_black;
			}
		} break;

		case fade_step::fade_from_black:
		{
			normalized = 1.0f - normalized;

			if(now >= total_time)
				current_step = fade_step::none;
			
		} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return UPDATE_CONTINUE;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool ModuleFadeToBlack::FadeToBlack(Module* module_off, Module* module_on, float time)
{
	bool ret = false;

	if(current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);

		off = module_off;
		on = module_on;

		ret = true;
	}

	return ret;
}

bool ModuleFadeToBlack::IsFading() const
{
	return current_step != fade_step::none;
}