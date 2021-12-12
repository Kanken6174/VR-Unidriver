#include <WinUser.h>

static const char* const k_pch_hmd_Section = "hmd_sim";	//nom du driver (clé générale)
static const char* const k_pch_hmd_SerialNumber_String = "serialNumber";//le reste ce sont des sous-clés dépendantes de la clé générale
static const char* const k_pch_hmd_ModelNumber_String = "modelNumber";//Ces clés ne représentent pas une valeur mais un chemin vers
static const char* const k_pch_hmd_WindowX_Int32 = "windowX";		//une valeur
static const char* const k_pch_hmd_WindowY_Int32 = "windowY";
static const char* const k_pch_hmd_WindowWidth_Int32 = "windowWidth";
static const char* const k_pch_hmd_WindowHeight_Int32 = "windowHeight";
static const char* const k_pch_hmd_RenderWidth_Int32 = "renderWidth";
static const char* const k_pch_hmd_RenderHeight_Int32 = "renderHeight";
static const char* const k_pch_hmd_SecondsFromVsyncToPhotons_Float = "secondsFromVsyncToPhotons";
static const char* const k_pch_hmd_DisplayFrequency_Float = "displayFrequency";

// Icons can be configured in code or automatically configured by an external file "drivername\resources\driver.vrresources".
// Icon properties NOT configured in code (post Activate) are then auto-configured by the optional presence of a driver's "drivername\resources\driver.vrresources".
// In this manner a driver can configure their icons in a flexible data driven fashion by using an external file.
//
// The structure of the driver.vrresources file allows a driver to specialize their icons based on their HW.
// Keys matching the value in "Prop_ModelNumber_String" are considered first, since the driver may have model specific icons.
// An absence of a matching "Prop_ModelNumber_String" then considers the ETrackedDeviceClass ("HMD", "Controller", "GenericTracker", "TrackingReference")
// since the driver may have specialized icons based on those device class names.
//
// An absence of either then falls back to the "system.vrresources" where generic device class icons are then supplied.
//
// Please refer to "bin\drivers\hmd\resources\driver.vrresources" which contains this hmd configuration.
//
// "Alias" is a reserved key and specifies chaining to another json block.
//
// In this hmd configuration file (overly complex FOR EXAMPLE PURPOSES ONLY)....
//
// "Model-v2.0" chains through the alias to "Model-v1.0" which chains through the alias to "Model-v Defaults".
//
// Keys NOT found in "Model-v2.0" would then chase through the "Alias" to be resolved in "Model-v1.0" and either resolve their or continue through the alias.
// Thus "Prop_NamedIconPathDeviceAlertLow_String" in each model's block represent a specialization specific for that "model".
// Keys in "Model-v Defaults" are an example of mapping to the same states, and here all map to "Prop_NamedIconPathDeviceOff_String".
//