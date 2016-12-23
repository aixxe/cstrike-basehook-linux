#pragma once

class TestEventListener: public IGameEventListener2 {
	public:
		TestEventListener(const char* name) {
			// Register self as an event listener.
			gameevents->AddListener(this, name, false);
		};

		~TestEventListener() {
			// Unregister when destructor is called.
			gameevents->RemoveListener(this);
		}

		void FireGameEvent(IGameEvent* event) {
			// Print text to console when event is fired.
			cvar->ConsoleColorPrintf(Color(150, 255, 150), "Event fired: %s\n", event->GetName());
		}

		int GetEventDebugID() override {
			return EVENT_DEBUG_ID_INIT;
		};
};