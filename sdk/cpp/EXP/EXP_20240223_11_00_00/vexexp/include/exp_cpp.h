#include "exp_api.h"

#if defined(__has_include)
#if __has_include("exp_apiprivate.h")
#include "exp_apiprivate.h"
#endif
#endif

#include "vex_task.h"
#include "vex_thread.h"
#include "vex_event.h"
#include "vex_mevent.h"

#include "vex_units.h"
#include "vex_color.h"
#include "vex_device.h"
#include "vex_motor.h"
#include "vex_vision.h"
#include "vex_imu.h"
#include "vex_rotation.h"
#include "vex_optical.h"
#include "vex_distance.h"
#include "vex_electromag.h"
#include "vex_gps.h"
#include "vex_controller.h"
#include "vex_brain.h"
#include "vex_competition.h"
#include "vex_triport.h"
#include "vex_timer.h"
#include "vex_motorgroup.h"
#include "vex_drivetrain.h"
#include "vex_smartdrive.h"
#include "vex_vexlink.h"
#include "vex_aivision.h"
#include "vex_pneumatic.h"
#include "vex_signaltower.h"
#include "vex_ctearm.h"
#include "vex_global.h"