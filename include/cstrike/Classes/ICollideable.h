#pragma once

class ICollideable {
	public:
		virtual IHandleEntity* GetEntityHandle() = 0;
		virtual const Vector& OBBMinsPreScaled() const = 0;
		virtual const Vector& OBBMaxsPreScaled() const = 0;
		virtual const Vector& OBBMins() const = 0;
		virtual const Vector& OBBMaxs() const = 0;
};