#ifndef PROFILE_MANAGEMENT_H
#define PROFILE_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "Arduino.h"

typedef struct {
    char profile_Name[20];
    int preheat_tempRise;
    int soak_temp;
    int soak_duration;
    int rampPeak_TempRise;
    int reflow_temp;
    int reflow_duration;
    int cooldown_temp;
    int cooldown_duration;
} ReflowProfile;


bool profileExists(const char *profileName);
void overwriteProfile(ReflowProfile newProfile);
bool saveProfile(ReflowProfile newProfile);
void deleteProfile(int index);
bool getProfile(ReflowProfile *profile, int index);
int getProfileCount(void);
bool loadProfiles();
void clearProfiles();
bool updateLocalProfileCount(void);

#ifdef __cplusplus
}
#endif

#endif