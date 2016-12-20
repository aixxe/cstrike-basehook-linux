#pragma once

class CShowPixelsParams {
	public:
		unsigned int m_srcTexName;
		int m_width;
		int m_height;
		bool m_vsyncEnable;
		bool m_fsEnable;
		bool m_useBlit;
		bool m_noBlit;
		bool m_onlySyncView;
};