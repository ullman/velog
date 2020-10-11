#include <stdlib.h>
#include <string.h>
#include "vedirect.h"


ve_direct_device_info_t *_ve_direct_get_device_info(unsigned int pid)
{
	char			name[256];
	ve_direct_device_info_t *info;
	ve_direct_device_type	type;

	if (pid == 0) return NULL;

	switch (pid) {

	case 0x203:
		type = ve_direct_device_type_bmv;
		strcpy(name, "BMV-700");
		break;
	case 0x204:
		type = ve_direct_device_type_bmv;
		strcpy(name, "BMV-702");
		break;
	case 0x205:
		type = ve_direct_device_type_bmv;
		strcpy(name, "BMV-700H");
		break;
	case 0x0300:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 70|15");
		break;
	case 0xA040:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 75|50");
		break;
	case 0xA041:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|35");
		break;
	case 0xA042:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 75|15");
		break;
	case 0xA043:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|15");
		break;
	case 0xA044:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|30");
		break;
	case 0xA045:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|50");
		break;
	case 0xA046:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|70");
		break;
	case 0xA047:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|100");
		break;
	case 0xA049:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|50 rev2");
		break;
	case 0xA04A:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|30 rev2");
		break;
	case 0xA04B:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|35 rev2");
		break;
	case 0xA04C:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 75|10");
		break;
	case 0xA04D:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|45");
		break;
	case 0xA04E:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|60");
		break;
	case 0xA04F:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|85");
		break;
	case 0xA050:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|100");
		break;
	case 0xA051:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|100");
		break;
	case 0xA052:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|85");
		break;
	case 0xA053:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 75|15");
		break;
	case 0xA054:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 75|10");
		break;
	case 0xA055:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 100|15");
		break;
	case 0xA056:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 100|30");
		break;
	case 0xA057:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 100|50");
		break;
	case 0xA058:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|35");
		break;
	case 0xA059:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|100 rev2");
		break;
	case 0xA05A:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|85 rev2");
		break;
	case 0xA05B:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|70");
		break;
	case 0xA05C:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|85");
		break;
	case 0xA05D:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|60");
		break;
	case 0xA05E:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|45");
		break;
	case 0xA05F:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 100|20");
		break;
	case 0xA060:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 100|20 48V");
		break;
	case 0xA061:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|45");
		break;
	case 0xA062:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|60");
		break;
	case 0xA063:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|70");
		break;
	case 0xA064:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|85 rev2");
		break;
	case 0xA065:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|100 rev2");
		break;
	case 0xA066:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|20");
		break;
	case 0xA067:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 100|20 48V");
		break;
	case 0xA068:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|60 rev2");
		break;
	case 0xA069:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 250|70 rev2");
		break;
	case 0xA06A:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|45 rev2");
		break;
	case 0xA06B:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|60 rev2");
		break;
	case 0xA06C:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|70 rev2");
		break;
	case 0xA06D:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|85 rev3");
		break;
	case 0xA06E:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT 150|100 rev3");
		break;
	case 0xA06F:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|45 rev2");
		break;
	case 0xA070:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|60 rev2");
		break;
	case 0xA071:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT 150|70 rev2");
		break;
	case 0xA102:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/70");
		break;
	case 0xA103:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/45");
		break;
	case 0xA104:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/60");
		break;
	case 0xA105:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/85");
		break;
	case 0xA106:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/100");
		break;
	case 0xA107:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/45");
		break;
	case 0xA108:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/60");
		break;
	case 0xA109:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/70");
		break;
	case 0xA10A:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/85");
		break;
	case 0xA10B:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/100");
		break;
	case 0xA10C:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/70 rev2");
		break;
	case 0xA10D:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/85 rev2");
		break;
	case 0xA10E:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 150/100 rev2");
		break;
	case 0xA10F:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT VE.Can 150/100");
		break;
	case 0xA112:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT VE.Can 250/70");
		break;
	case 0xA113:
		type = ve_direct_device_type_mppt;
		strcpy(name, "BlueSolar MPPT VE.Can 250/100");
		break;
	case 0xA114:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/70 rev2");
		break;
	case 0xA115:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/100 rev2");
		break;
	case 0xA116:
		type = ve_direct_device_type_mppt;
		strcpy(name, "SmartSolar MPPT VE.Can 250/85 rev2");
		break;
	case 0xA201:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 250VA 230V");
		break;
	case 0xA202:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 250VA 230V");
		break;
	case 0xA204:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 250VA 230V");
		break;
	case 0xA211:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 375VA 230V");
		break;
	case 0xA212:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 375VA 230V");
		break;
	case 0xA214:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 375VA 230V");
		break;
	case 0xA221:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 500VA 230V");
		break;
	case 0xA222:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 500VA 230V");
		break;
	case 0xA224:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 500VA 230V");
		break;
	case 0xA231:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 250VA 230V");
		break;
	case 0xA232:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 250VA 230V");
		break;
	case 0xA234:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 250VA 230V");
		break;
	case 0xA239:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 250VA 120V");
		break;
	case 0xA23A:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 250VA 120V");
		break;
	case 0xA23C:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 250VA 120V");
		break;
	case 0xA241:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 375VA 230V");
		break;
	case 0xA242:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 375VA 230V");
		break;
	case 0xA244:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 375VA 230V");
		break;
	case 0xA249:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 375VA 120V");
		break;
	case 0xA24A:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 375VA 120V");
		break;
	case 0xA24C:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 375VA 120V");
		break;
	case 0xA251:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 500VA 230V");
		break;
	case 0xA252:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 500VA 230V");
		break;
	case 0xA254:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 500VA 230V");
		break;
	case 0xA259:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 500VA 120V");
		break;
	case 0xA25A:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 500VA 120V");
		break;
	case 0xA25C:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 500VA 120V");
		break;
	case 0xA261:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 800VA 230V");
		break;
	case 0xA262:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 800VA 230V");
		break;
	case 0xA264:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 800VA 230V");
		break;
	case 0xA269:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 800VA 120V");
		break;
	case 0xA26A:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 800VA 120V");
		break;
	case 0xA26C:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 800VA 120V");
		break;
	case 0xA271:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 1200VA 230V");
		break;
	case 0xA272:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 1200VA 230V");
		break;
	case 0xA274:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 1200VA 230V");
		break;
	case 0xA279:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 1200VA 120V");
		break;
	case 0xA27A:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 1200VA 120V");
		break;
	case 0xA27C:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 1200VA 120V");
		break;
	case 0xA281:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 1600VA 230V");
		break;
	case 0xA282:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 1600VA 230V");
		break;
	case 0xA284:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 1600VA 230V");
		break;
	case 0xA291:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 2000VA 230V");
		break;
	case 0xA292:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 2000VA 230V");
		break;
	case 0xA294:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 2000VA 230V");
		break;
	case 0xA2A1:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 12V 3000VA 230V");
		break;
	case 0xA2A2:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 24V 3000VA 230V");
		break;
	case 0xA2A4:
		type = ve_direct_device_type_inverter;
		strcpy(name, "Phoenix Inverter 48V 3000VA 230V");
		break;
	case 0xA340:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 12|50 (1+1)");
		break;
	case 0xA341:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 12|50 (3)");
		break;
	case 0xA342:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 24|25 (1+1)");
		break;
	case 0xA343:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 24|25 (3)");
		break;
	case 0xA344:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 12|30 (1+1)");
		break;
	case 0xA345:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 12|30 (3)");
		break;
	case 0xA346:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 24|16 (1+1)");
		break;
	case 0xA347:
		type = ve_direct_device_type_smart_charger;
		strcpy(name, "Phoenix Smart IP43 Charger 24|16 (3)");
		break;
	case 0xA381:
		type = ve_direct_device_type_bmv;
		strcpy(name, "BMV-712 Smart Battery Monitor");
		break;
	default:
		type = ve_direct_device_type_unknown;
		strcpy(name, "Unknown device PID");
	}
	info = calloc(1,sizeof(ve_direct_device_info_t));
	info->name = malloc(strlen(name)+1);
	info->type = type;
	strcpy(info->name, name);
	return info;
}
