#include <stdio.h>
#include <string.h>
#include <nvs.h>
#include <nvs_flash.h>
#include "profile_management.h"



// Globale Variablen für Profile
#define MAX_PROFILES 5                 // Maximale Anzahl von Profilen
ReflowProfile profiles[MAX_PROFILES];   // Alle gespeicherten Profile
int profile_count = 0;                  // Anzahl gespeicherter Profile


bool updateLocalProfileCount(void) {
    // Open NVS for reading
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("reflow", NVS_READONLY, &my_handle);
    if (err != ESP_OK) {
        printf("Failed to open NVS for reading!\n");
        return false;
    }

    // Read the profile count
    size_t size = sizeof(profile_count);
    err = nvs_get_i32(my_handle, "profile_count", &profile_count);
    if (err != ESP_OK) {
        profile_count = 0; // If no profiles were saved
        nvs_close(my_handle);
        return false;
    }

    // Close NVS
    nvs_close(my_handle);
    return true;
}

// 🔍 **Check if a profile already exists**
bool profileExists(const char *profileName) {
    for (int i = 0; i < profile_count; i++) {
        if (strcmp(profiles[i].profile_Name, profileName) == 0) {
            return true;
        }
    }
    return false;
}

// ✏ **Overwrite an existing profile**
void overwriteProfile(ReflowProfile newProfile) {
    for (int i = 0; i < profile_count; i++) {
        if (strcmp(profiles[i].profile_Name, newProfile.profile_Name) == 0) {
            profiles[i] = newProfile;  // Overwrite existing profile

            // Save updated profile list to NVS
            nvs_handle_t my_handle;
            esp_err_t err = nvs_open("reflow", NVS_READWRITE, &my_handle);
            if (err != ESP_OK) {
                printf("NVS öffnen fehlgeschlagen!\n");
                return;
            }

            err = nvs_set_blob(my_handle, "profiles", profiles, sizeof(profiles));
            if (err == ESP_OK) {
                nvs_commit(my_handle);
                printf("Profile '%s' successfully updated!\n", newProfile.profile_Name);
            } else {
                printf("Error saving updated profile!\n");
            }
            nvs_close(my_handle);
            return;
        }
    }
}

// **Speichert ein neues Profil in NVS**
bool saveProfile(ReflowProfile newProfile) {
    if (profile_count >= MAX_PROFILES) {
        //printf("Maximale Anzahl an Profilen erreicht!\n");
        return false;
    }

    // Füge neues Profil hinzu
    profiles[profile_count] = newProfile;
    profile_count++;

    // Speichere in NVS
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("reflow", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        //printf("NVS öffnen fehlgeschlagen!\n");
        return false;
    }

    // Save the profile count and the profiles array in NVS
    err = nvs_set_i32(my_handle, "profile_count", profile_count);
    if (err != ESP_OK) {
        // printf("Error saving profile count!\n");
        nvs_close(my_handle);
        return false;
    }
    
    err = nvs_set_blob(my_handle, "profiles", profiles, sizeof(profiles));
    if (err != ESP_OK) {
        // printf("Error saving profiles data!\n");
        nvs_close(my_handle);
        return false;
    }

    nvs_commit(my_handle);
    nvs_close(my_handle);

    //printf("Profil '%s' gespeichert!\n", newProfile.profile_Name);
    return true;
}

// **Löscht ein spezifisches Profil**
void deleteProfile(int index) {
    if (index < 0 || index >= profile_count) {
        printf("Ungültiger Index!\n");
        return;
    }

    // Profile nach vorne verschieben
    for (int i = index; i < profile_count - 1; i++) {
        profiles[i] = profiles[i + 1];
    }

    profile_count--;

    // Speichere in NVS
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("reflow", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        //printf("NVS öffnen fehlgeschlagen!\n");
        return;
    }

    nvs_set_i32(my_handle, "profile_count", profile_count);
    nvs_set_blob(my_handle, "profiles", profiles, sizeof(profiles));

    nvs_commit(my_handle);
    nvs_close(my_handle);

    //printf("Profil %d gelöscht!\n", index);
}

int getProfileCount(void) {
    return profile_count;
}
// **Gibt ein Profil zurück**
bool getProfile(ReflowProfile *profile, int index) {
    if (index < 0 || index >= profile_count) {
        printf("Ungültiger Index!\n");
        return false;
    }

    *profile = profiles[index];
    return true;
}

// **Lade alle Profile aus NVS**
bool loadProfiles() {
    nvs_handle_t my_handle;
    esp_err_t err;

    err = nvs_open("reflow", NVS_READONLY, &my_handle);
    if (err != ESP_OK) {
        //printf("NVS öffnen fehlgeschlagen!\n");
        return false;
    }

    // Lade Anzahl der Profile
    size_t size = sizeof(profile_count);
    err = nvs_get_i32(my_handle, "profile_count", &profile_count);
    if (err != ESP_OK) {
        profile_count = 0; // Falls nichts gespeichert wurde
        return false;
    }

    // Lade gespeicherte Profile
    size = sizeof(profiles);
    err = nvs_get_blob(my_handle, "profiles", profiles, &size);
    if (err != ESP_OK) {
        //printf("Keine gespeicherten Profile gefunden.\n");
        return false;
    }

    nvs_close(my_handle);
    return true;
}

// **Löscht alle Profile**
void clearProfiles() {
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("reflow", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) {
        //printf("NVS öffnen fehlgeschlagen!\n");
        return;
    }

    nvs_erase_key(my_handle, "profiles");
    nvs_erase_key(my_handle, "profile_count");
    nvs_commit(my_handle);
    nvs_close(my_handle);

    profile_count = 0;
    memset(profiles, 0, sizeof(profiles));

    //printf("Alle Profile gelöscht!\n");
}
