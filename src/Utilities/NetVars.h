#pragma once

#include <unordered_map>

class NetVars {
	private:
		static uintptr_t FindOffset(RecvTable* recv_table, const char* property_name, RecvProp** property_ptr = nullptr) {
			for (int i = 0; i < recv_table->m_nProps; i++) {
				RecvProp& recv_prop = recv_table->m_pProps[i];

				if (strcmp(recv_prop.m_pVarName, property_name) == 0) {
					if (property_ptr)
						*property_ptr = &recv_table->m_pProps[i];

					return recv_prop.m_Offset;
				}

				if (recv_prop.m_RecvType != SendPropType::DPT_DataTable) {
					continue;
				}

				if (uintptr_t offset = FindOffset(recv_prop.m_pDataTable, property_name)) {
					if (property_ptr)
						*property_ptr = &recv_table->m_pProps[i];

					return recv_prop.m_Offset + offset;
				}
			}

			return 0;
		}
	public:
		static uintptr_t GetOffset(const char* class_name, const char* property_name, RecvProp** property_ptr = nullptr) {
            typedef std::unordered_map<const char *, uintptr_t> PropertyCache;
            typedef std::unordered_map<const char *, PropertyCache> ClassCache;
            static ClassCache classCache;
            
            ClassCache::iterator itrClassCache = classCache.find(class_name);
            if(itrClassCache != classCache.end())
            {
                PropertyCache &propertyCache = itrClassCache->second;
                PropertyCache::iterator itrPropertyCache = propertyCache.find(property_name);
                if(itrPropertyCache != propertyCache.end())
                {
                    return itrPropertyCache->second;
                }
            }
            
			for (ClientClass* class_ptr = clientdll->GetAllClasses(); class_ptr; class_ptr = class_ptr->m_pNext) {
				if (strcmp(class_ptr->m_pNetworkName, class_name) == 0) {
                    uintptr_t result = FindOffset(class_ptr->m_pRecvTable, property_name, property_ptr);
                    classCache[class_name][property_name] = result;
					return result;
				}
			}

			return 0;
		}
};
