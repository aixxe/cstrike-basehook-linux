#pragma once

#define MAX_SPLITSCREEN_PLAYERS 1

enum MouseParams: int {
	MOUSE_ACCEL_THRESHHOLD1 = 0,
	MOUSE_ACCEL_THRESHHOLD2,
	MOUSE_SPEED_FACTOR,
	NUM_MOUSE_PARAMS
};

enum JoystickAxis_t {
	JOY_AXIS_X = 0,
	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

typedef struct {
	unsigned int AxisFlags;
	unsigned int AxisMap;
	unsigned int ControlMap;
} joy_axis_t;

struct Split_t {
	int m_nDown[2];
	int m_nState;
};

struct kbutton_t {
	Split_t m_PerUser[MAX_SPLITSCREEN_PLAYERS];
};

class CKeyboardKey {
	public:
		char m_szName[32];
		kbutton_t* m_pKey;
		CKeyboardKey* m_pNext;
};

class CUserCmd;
class CVerifiedUserCmd;

class CInput {
	private:
		virtual ~CInput(void) {};
	public:
		bool m_fMouseInitialized;
		bool m_fMouseActive;
		bool m_fJoystickAdvancedInit;
		bool m_fHadJoysticks;

		float m_flAccumulatedMouseXMovement;
		float m_flAccumulatedMouseYMovement;
		float m_flPreviousMouseXPosition;
		float m_flPreviousMouseYPosition;
		float m_flRemainingJoystickSampleTime;
		float m_flKeyboardSampleTime;

		bool m_fRestoreSPI;
		int m_rgOrigMouseParms[NUM_MOUSE_PARAMS];
		int m_rgNewMouseParms[NUM_MOUSE_PARAMS];
		bool m_rgCheckMouseParam[NUM_MOUSE_PARAMS];
		bool m_fMouseParmsValid;

		joy_axis_t m_rgAxes[MAX_JOYSTICK_AXES];
		CKeyboardKey* m_pKeys;

		bool m_fCameraInterceptingMouse;
		bool m_fCameraInThirdPerson;
		bool m_fCameraMovingWithMouse;

		bool m_fCameraDistanceMove;

		int m_nCameraOldX;
		int m_nCameraOldY;
		int m_nCameraX;
		int m_nCameraY;

		bool m_CameraIsOrthographic;

		QAngle m_angPreviousViewAngles;

		float m_flLastForwardMove;

		float m_flPreviousJoystickForward;
		float m_flPreviousJoystickSide;
		float m_flPreviousJoystickPitch;
		float m_flPreviousJoystickYaw;

		CUserCmd* m_pCommands;
		CVerifiedUserCmd* m_pVerifiedCommands;

		inline CUserCmd* GetUserCmd(int sequence) {
			return &this->m_pCommands[sequence % MULTIPLAYER_BACKUP];
		}

		inline CVerifiedUserCmd* GetVerifiedUserCmd(int sequence) {
			return &this->m_pVerifiedCommands[sequence % MULTIPLAYER_BACKUP];
		}

		inline void VerifyUserCmd(CUserCmd* cmd, int sequence) {
			CVerifiedUserCmd* cmd_verified = this->GetVerifiedUserCmd(sequence);

			cmd_verified->m_cmd = *cmd;
			cmd_verified->m_crc = cmd->GetChecksum();
		}
};

extern CInput* input;