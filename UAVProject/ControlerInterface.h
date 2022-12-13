// ControlerInterface.h

#ifndef _CONTROLERINTERFACE_h
#define _CONTROLERINTERFACE_h
#include <ArduinoJson.h>

class ControlerInterface
{
public:
	virtual void init() = 0;

	/**
	 * @brief For func that need to set in the loop
	 *
	 */
	virtual void everyLoop() = 0;
	virtual void show(DynamicJsonDocument) = 0;

};
#endif

