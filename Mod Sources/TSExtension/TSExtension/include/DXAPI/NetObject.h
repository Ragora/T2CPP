#pragma once

#include <DXAPI/SimObject.h>

namespace DX
{
	enum NetFlags
	{
		IsGhost = 1,
		ScopeAlways = 1 << 6,
		ScopeLocal = 1 << 7,
		Ghostable = 1 << 8
	};

	class NetObject : public SimObject
	{
	public:
		NetObject(unsigned int obj);

		unsigned int &net_flags;
	};
} // End NameSpace DX
