#pragma once

class CBaseHandle {
	public:
		inline bool IsValid() const {
			return m_Index != INVALID_EHANDLE_INDEX;
		}

		inline int GetEntryIndex() const {
			return m_Index & ENT_ENTRY_MASK;
		}

		unsigned long m_Index;
};