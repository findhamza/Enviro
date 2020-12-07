#ifndef MANAGERFSM_H
#define MANAGERFSM_H

#include "syslib.h"
#include "CloudFSM.h"
#include "PlantFSM.h"

class ManagerFSM {

	cloudState_codes cloudStatus;
	plantState_codes plantStatus;

	void initManager() {

		cloudStatus = processCloud(false);
		plantStatus = processPlant(false, false);

	}

public:
	ManagerFSM() {
		initManager();
	}

	updateFlag updateFSM(double sPower) {

		bool sunLight = false;
		bool water = false;
		updateFlag uFlag;

		if (sPower < 0.4)
			sunLight = true;
		if (cloudStatus == cRain)
			water = true;

		cloudStatus = processCloud(sunLight);
		plantStatus = processPlant(water, sunLight);

		if (plantStatus == grow)
			uFlag.plant.grow = true;
		else
			uFlag.plant.grow = false;
		if (plantStatus == wilt)
			uFlag.plant.wilt = true;
		else
			uFlag.plant.wilt = false;
		if (cloudStatus == cGrowth)
			uFlag.cloud.grow = true;
		else
			uFlag.cloud.grow = false;
		if (cloudStatus == cRain)
			uFlag.cloud.rain = true;
		else
			uFlag.cloud.rain = false;

		return uFlag;
	}
};

#endif