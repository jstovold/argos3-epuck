/**
 * @file <argos3/plugins/robots/e-puck/real_robot/real_epuck_wifi_actuator.h
 *
 */

#ifndef REAL_EPUCK_WIFI_ACTUATOR_H
#define REAL_EPUCK_WIFI_ACTUATOR_H

namespace argos {
   class CRealEPuckWifiActuator;
}

#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_base.h>
#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_serial_actuator.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wifi_actuator.h>

namespace argos {

   class CRealEPuckWifiActuator : virtual public CCI_EPuckWifiActuator,
                                   virtual public CRealEPuckSerialActuator {

   public:

      virtual ~CRealEPuckWifiActuator() {}
      virtual void SendMessage(UInt8 un_data);
   };
}
#endif
