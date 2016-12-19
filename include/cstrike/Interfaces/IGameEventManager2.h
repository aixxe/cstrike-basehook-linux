#pragma once

#define EVENT_DEBUG_ID_INIT 42
#define EVENT_DEBUG_ID_SHUTDOWN 13

class bf_read;
class bf_write;

class IGameEvent {
	public:
		virtual ~IGameEvent() {};
		virtual const char* GetName() const = 0;
		virtual bool IsReliable() const = 0;
		virtual bool IsLocal() const = 0;
		virtual bool IsEmpty(const char* key = 0) = 0;
		virtual bool GetBool(const char* key = 0, bool default_value = false) = 0;
		virtual int GetInt(const char* key = 0, int default_value = 0) = 0;
		virtual float GetFloat(const char* key = 0, float default_value = 0.0f) = 0;
		virtual const char* GetString(const char* key = 0, const char* default_value = "") = 0;
		virtual void SetBool(const char* key, bool value) = 0;
		virtual void SetInt(const char* key, int value) = 0;
		virtual void SetFloat(const char* key, float value) = 0;
		virtual void SetString(const char* key, const char* value) = 0;
};

class IGameEventListener2 {
	public:
		virtual	~IGameEventListener2() {};
		virtual void FireGameEvent(IGameEvent* event) = 0;
		virtual int GetEventDebugID(void) = 0;
};

class IGameEventManager2 {
	public:
		virtual	~IGameEventManager2() {};
		virtual int LoadEventsFromFile(const char* filename) = 0;
		virtual void Reset() = 0;
		virtual bool AddListener(IGameEventListener2* listener, const char* name, bool serverside) = 0;
		virtual bool FindListener(IGameEventListener2* listener, const char* name) = 0;
		virtual void RemoveListener(IGameEventListener2* listener) = 0;
		virtual IGameEvent* CreateEvent(const char* name, bool force = false) = 0;
		virtual bool FireEvent(IGameEvent* event, bool dont_broadcast = false) = 0;
		virtual bool FireEventClientSide(IGameEvent* event) = 0;
		virtual IGameEvent* DuplicateEvent(IGameEvent* event) = 0;
		virtual void FreeEvent(IGameEvent* event) = 0;
		virtual bool SerializeEvent(IGameEvent* event, bf_write* buf) = 0;
		virtual IGameEvent* UnserializeEvent(bf_read* buf) = 0;
};