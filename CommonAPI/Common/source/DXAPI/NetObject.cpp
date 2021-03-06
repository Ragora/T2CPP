#include <DXAPI/NetObject.h>

namespace DX
{
	NetObject::NetObject(unsigned int obj) : SimObject(obj),
		net_flags(MEMBER_FIELD(obj, unsigned int, 64))
	{

	}

	void NetObject::setMaskBits(unsigned int bits){
		unsigned int localbits=bits;
		unsigned int bpv = this->base_pointer_value;
		void * setmaskbitptr = (void *)(unsigned int)0x585BE0;
		__asm {
			push localbits
			mov ecx,bpv
			mov eax,setmaskbitptr
			call eax
		};
	}

	void NetObject::clearMaskBits(unsigned int bits){
		unsigned int localbits=bits;
		unsigned int bpv = this->base_pointer_value;
		void * clearmaskbitptr = (void *)(unsigned int)0x585C10;
		__asm {
			push localbits
			mov ecx,bpv
			mov eax,clearmaskbitptr
			call eax
		};
	}
}