#pragma once

class IHandleEntity {
	public:
		virtual ~IHandleEntity() {};
		virtual void SetRefEHandle(const CBaseHandle& Handle) = 0;
		virtual const CBaseHandle& GetRefEHandle() const = 0;
};