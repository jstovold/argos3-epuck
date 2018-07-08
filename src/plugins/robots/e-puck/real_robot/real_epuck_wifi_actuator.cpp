/**
 * @file <argos3/plugins/robots/e-puck/real_robot/real_epuck_wifi_actuator.cpp
 *
 */

#include "real_epuck_wifi_actuator.h"

namespace argos {

   /****************************************/
   /****************************************/


   void CRealEPuckWifiActuator::SendMessage(UInt8 un_data) {
      m_psState->WifiMessageToSend = true;
      BaseWifiMessage msg;
      msg.data = un_data;
      msg.source = 0;
      m_psState->WifiMessage = msg;
   }

   /****************************************/
   /****************************************/

}
