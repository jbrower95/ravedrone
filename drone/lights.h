#ifndef LIGHTS_H
#define LIGHTS_H

/* Call inside Arduino setup function */
void setupLights();

/* Update the lights with whether or not a beat has occurred */
void updateLightsWithBeatDidOccur(bool beatDidOccur);

#endif
