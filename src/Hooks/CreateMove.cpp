#include "Hooks.h"

typedef void (*CreateMove_t) (IBaseClientDLL*, int, float, bool);

void Hooks::CreateMove(IBaseClientDLL* thisptr, int sequence, float frametime, bool active) {
	// Get the original function and store it statically.
	static CreateMove_t oCreateMove = clientdll_hook->GetOriginalFunction<CreateMove_t>(21);

	// Call original 'IBaseClientDLL::CreateMove'.
	oCreateMove(thisptr, sequence, frametime, active);

	// Get the current user command.
	CUserCmd* cmd = input->GetUserCmd(sequence);

	if (cmd->buttons & IN_JUMP) {
		cmd->buttons |= IN_ATTACK;
	}

	// Re-calculate the command checksum after making changes.
	input->VerifyUserCmd(cmd, sequence);
}