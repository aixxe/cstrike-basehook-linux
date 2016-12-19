#pragma once

class IClientEntity: public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable {
	public:
		virtual void Release(void) = 0;
		virtual const Vector& GetAbsOrigin(void) const = 0;
		virtual const QAngle& GetAbsAngles(void) const = 0;
};