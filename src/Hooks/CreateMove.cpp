#include "Hooks.h"

typedef void (*CreateMove_t) (IBaseClientDLL*, int, float, bool);

bool GUI::BunnyHop::Enabled = true;

void Hooks::CreateMove(IBaseClientDLL* thisptr, int sequence, float frametime, bool active) {
	// Get the original function and store it statically.
	static CreateMove_t oCreateMove = clientdll_hook->GetOriginalFunction<CreateMove_t>(21);

	// Call original 'IBaseClientDLL::CreateMove'.
	oCreateMove(thisptr, sequence, frametime, active);

	// Get the current user command.
	CUserCmd* cmd = input->GetUserCmd(sequence);

	// Get the LocalPlayer entity.
	C_BasePlayer* localplayer = static_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	
	// No need to validate if we stop here since we haven't changed anything yet.
	if (!localplayer)
		return;

	// Auto-bunnyhop when jump key is held. (releases the IN_JUMP button when on ground)
	if (GUI::BunnyHop::Enabled && cmd->buttons & IN_JUMP && !(localplayer->GetFlags() & FL_ONGROUND))
		cmd->buttons &= ~IN_JUMP;
	
	// Re-calculate the command checksum after making changes.
	input->VerifyUserCmd(cmd, sequence);
}