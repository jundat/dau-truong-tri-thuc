#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <string>
#include "ConfigLoader.h"


//////////////////////////////////////////////////////////////////////////

class PairIntInt {
public:
	int keyRd;
	int valueId;

	PairIntInt(int krd, int vid) {
		keyRd = krd;
		valueId = vid;
	}
};

//////////////////////////////////////////////////////////////////////////
//MACRO

#define CONF_BOOL(config)		ConfigLoader::shareConfigLoader()->getBoolValue(#config)
#define CONF_INT(config)		ConfigLoader::shareConfigLoader()->getIntValue(#config)
#define CONF_FLOAT(config)		ConfigLoader::shareConfigLoader()->getFloatValue(#config)
#define CONF_STR(config)		ConfigLoader::shareConfigLoader()->getStringValue(#config)


//////////////////////////////////////////////////////////////////////////

#endif //__GLOBAL_H__
