/**
 * @file <argos3/plugins/robots/e-puck/real_robot/real_epuck_wifi_sensor.h>
 * @author James Stovold <j.h.stovold@swansea.ac.uk>
 */

#ifndef REAL_EPUCK_WIFI_SENSOR_H
#define REAL_EPUCK_WIFI_SENSOR_H

namespace argos {
   class CRealEPuckWifiSensor;
}

#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wifi_sensor.h>
#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_serial_sensor.h>
#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_base.h>

namespace argos {
	// not actually a serial sensor, but we can still use it like one...
   class CRealEPuckWifiSensor : virtual public CCI_EPuckWifiSensor,
                                 virtual public CRealEPuckSerialSensor {

   public:

      CRealEPuckWifiSensor() {};
      virtual ~CRealEPuckWifiSensor() {};

      virtual void UpdateValues();

   };
}
#endif
