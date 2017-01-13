# cstrike-basehook-linux

Internal project base for Counter-Strike: Source on Linux. Includes full OpenGL ImGui rendering and input handling, a minimal Source SDK implementation, virtual hooking class and various other features for quick prototyping.

### Features
* Retrieves interfaces directly from the *s_pInterfaceRegs* linked list.
* ImGui drawing and input handling via *ILauncherMgr* virtual hooks.
* Engine drawing with *ISurface* functions via *IEngineVGui::Paint* hook.
* *IBaseClientDLL::CreateMove* hook with *CUserCmd* checksum validation.
* *CInput* and *CGlobalVars* pointers retrieved from IBaseClientDLL virtuals.
* Can easily be unloaded, modified and reloaded without restarting the game.
* Includes an example game event listener in a self-contained class.

### Requirements

You will need **cmake**, a relatively up-to-date C++ compiler and 32-bit **SDL2** headers.

If you are on a 64-bit system you may need to enable 32-bit repositories.

```
pacman -S cmake base-devel lib32-sdl2 gcc-multilib
```

### Usage

After you have cloned or extracted an archive of the repository you can use `cmake .` to create a Makefile and `make` to build the shared library. When finished, load the output file into the game while it is running. Using [gdb](https://aixxe.net/2016/09/shared-library-injection) is recommended.

Press <kbd>INSERT</kbd> to toggle the configuration window.

### Credits

Special thanks to [luk1337](https://github.com/luk1337) for the ImGui SDL2 input fix.