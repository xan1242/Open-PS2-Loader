#ifndef __OPL_H
#define __OPL_H

#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <hdd-ioctl.h>
#include "opl-hdd-ioctl.h"
#include <iopcontrol.h>
#include <iopheap.h>
#include <string.h>
#include <loadfile.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <sbv_patches.h>
#include <libcdvd.h>
#include <libpad.h>
#include <libmc.h>
#include <netman.h>
#include <ps2ips.h>
#include <debug.h>
#include <gsKit.h>
#include <dmaKit.h>
#include <malloc.h>
#include <math.h>
#include <osd_config.h>
#include <libpwroff.h>
#include <usbhdfsd-common.h>
#include <smod.h>
#include <smem.h>
#include <debug.h>
#include <ps2smb.h>
#include "config.h"

#include "include/hddsupport.h"
#include "include/supportbase.h"
#include "include/bdmsupport.h"

// Last Played Auto Start
#include <time.h>

// Master password for disabling the parental lock.
#define OPL_PARENTAL_LOCK_MASTER_PASS "989765"

// IO type IDs
#define IO_CUSTOM_SIMPLEACTION    1 // handler for parameter-less actions
#define IO_MENU_UPDATE_DEFFERED   2
#define IO_CACHE_LOAD_ART         3 // io call to handle the loading of covers
#define IO_COMPAT_UPDATE_DEFFERED 4

// Codes have been planned to fit the design of the GUI functions within gui.c.
#define OPL_COMPAT_UPDATE_STAT_WIP        0
#define OPL_COMPAT_UPDATE_STAT_DONE       1
#define OPL_COMPAT_UPDATE_STAT_ERROR      -1
#define OPL_COMPAT_UPDATE_STAT_CONN_ERROR -2
#define OPL_COMPAT_UPDATE_STAT_ABORTED    -3

#define OPL_VMODE_CHANGE_CONFIRMATION_TIMEOUT_MS 10000

int oplPath2Mode(const char *path);
int oplGetAppImage(const char *device, char *folder, int isRelative, char *value, char *suffix, GSTEXTURE *resultTex, short psm);
int oplScanApps(int (*callback)(const char *path, config_set_t *appConfig, void *arg), void *arg);
int oplShouldAppsUpdate(void);
config_set_t *oplGetLegacyAppsConfig(void);
config_set_t *oplGetLegacyAppsInfo(char *name);

void setErrorMessage(int strId);
void setErrorMessageWithCode(int strId, int error);
int loadConfig(int types);
int saveConfig(int types, int showUI);
void applyConfig(int themeID, int langID, int skipDeviceRefresh);
void menuDeferredUpdate(void *data);
void moduleUpdateMenu(int mode, int themeChanged, int langChanged);
void handleLwnbdSrv();
void deinit(int exception, int modeSelected);

// Shutdown minimal services initiated for auto loading.
void miniDeinit(config_set_t *configSet);

extern char *gBaseMCDir;

enum ETH_OP_MODES {
    ETH_OP_MODE_AUTO = 0,
    ETH_OP_MODE_100M_FDX,
    ETH_OP_MODE_100M_HDX,
    ETH_OP_MODE_10M_FDX,
    ETH_OP_MODE_10M_HDX,

    ETH_OP_MODE_COUNT
};

extern int ps2_ip_use_dhcp;
extern int ps2_ip[4];
extern int ps2_netmask[4];
extern int ps2_gateway[4];
extern int ps2_dns[4];
extern int gETHOpMode; // See ETH_OP_MODES.
extern int gPCShareAddressIsNetBIOS;
extern int pc_ip[4];
extern int gPCPort;
// Please keep these string lengths in-sync with the limits within CDVDMAN.
extern char gPCShareNBAddress[17];
extern char gPCShareName[32];
extern char gPCUserName[32];
extern char gPCPassword[32];

//// Settings

// describes what is happening in the network startup thread (>0 means loading, <0 means error)...
extern int gNetworkStartup;
extern int gHDDSpindown;
/// Refer to enum START_MODE within iosupport.h
extern int gBDMStartMode;
extern int gHDDStartMode;
extern int gETHStartMode;
extern int gAPPStartMode;
extern int bdmCacheSize;
extern int hddCacheSize;
extern int smbCacheSize;

extern int gEnableILK;
extern int gEnableMX4SIO;
extern int gEnableBdmHDD;

extern int gAutosort;
extern int gAutoRefresh;
extern int gEnableNotifications;
extern int gEnableArt;
extern int gWideScreen;
extern int gVMode; // 0 - Auto, 1 - PAL, 2 - NTSC
extern int gXOff;
extern int gYOff;
extern int gOverscan;
extern int gSelectButton;
extern int gHDDGameListCache;

extern int gEnableSFX;
extern int gEnableBootSND;
extern int gEnableBGM;
extern int gSFXVolume;
extern int gBootSndVolume;
extern int gBGMVolume;
extern char gDefaultBGMPath[128];

extern int gXSensitivity;
extern int gYSensitivity;

extern int gCheatSource;
extern int gGSMSource;
extern int gPadEmuSource;

extern int gOSDLanguageValue;
extern int gOSDTVAspectRatio;
extern int gOSDVideOutput;
extern int gOSDLanguageEnable;
extern int gOSDLanguageSource;

extern int showCfgPopup;

#ifdef IGS
#define IGS_VERSION "0.1"
#endif

// ------------------------------------------------------------------------------------------------------------------------

#ifdef PADEMU
extern int gEnablePadEmu;
extern int gPadEmuSettings;
extern int gPadMacroSource;
extern int gPadMacroSettings;
#endif

// ------------------------------------------------------------------------------------------------------------------------

// 0,1,2 scrolling speed
extern int gScrollSpeed;
// Exit path
extern char gExitPath[256];
// Enable Debug Colors
extern int gEnableDebug;

extern int gPS2Logo;

// Default device
extern int gDefaultDevice;

extern int gEnableWrite;

// These prefixes are relative to the device's name (meaning that they do not include the device name).
extern char gBDMPrefix[32];
extern char gETHPrefix[32];

extern int gRememberLastPlayed;

// Last Played Auto Start
extern int KeyPressedOnce;
extern int gAutoStartLastPlayed;
extern int RemainSecs, DisableCron;
extern clock_t CronStart;

extern unsigned char gDefaultBgColor[3];
extern unsigned char gDefaultTextColor[3];
extern unsigned char gDefaultSelTextColor[3];
extern unsigned char gDefaultUITextColor[3];

// Launching games with args
extern hdl_game_info_t *gAutoLaunchGame;
extern base_game_info_t *gAutoLaunchBDMGame;
extern bdm_device_data_t *gAutoLaunchDeviceData;
extern char *gHDDPrefix;
extern char gOPLPart[128];

void initSupport(item_list_t *itemList, int mode, int force_reinit);

void setDefaultColors(void);

#define MENU_ITEM_HEIGHT 19

#include "include/menusys.h"

typedef struct
{
    item_list_t *support;

    /// menu item used with this list support
    menu_item_t menuItem;

    /// submenu list
    submenu_list_t *subMenu;
} opl_io_module_t;

/*
BLURT output char blurttext[128];
#define BLURT                                                                           \
    snprintf(blurttext, sizeof(blurttext), "%s\\%s(%d)", __FILE__, __func__, __LINE__); \
    delay(10);
#define BLURT snprintf(blurttext, sizeof(blurttext), "%s(%d)", blurttext, __LINE__);
*/

typedef struct
{
    const char* bsd;
    size_t bsd_len;

    const char* bsdfs;
    size_t bsdfs_len;

    const char* dvd;
    size_t dvd_len;

    const char* mc0;
    size_t mc0_len;

    const char* mc1;
    size_t mc1_len;

    const char* elf;
    size_t elf_len;

    const char* mt;
    size_t mt_len;

    const char* gc;
    size_t gc_len;

    const char* gsm;
    size_t gsm_len;

    const char* oplpart;
    size_t oplpart_len;
    
} neutrino_args_t;

typedef struct
{
    int mode;
    int bdm_type : 8;
    int media_type : 8;
    int logo : 8;
    int dbc : 8;
    int elf_passthru_argc;
    char** elf_passthru_argv;
    const char* opl_part_name;
    const char* vmc0_path;
    const char* vmc1_path;
    const char* filename;
}neutrino_config_t;

#endif
