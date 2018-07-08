/**
 * @file <argos3/plugins/robots/e-puck/real_robot/real_epuck_wifi_sensor.cpp
 *
 * @author Lorenzo Garattoni - <lgaratto@ulb.ac.be>
 */
#include "real_epuck_wifi_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   void CRealEPuckWifiSensor::UpdateValues() {
      LOG << "[wifi]in update values" << std::endl;
      if (m_psState->WifiHasReceived > 0) {
       	 LOG << "[wifi]received a packet" << std::endl;
         SPacket* psPacket = new SPacket();
         psPacket->Data    = m_psState->WifiMessage.data;       // the payload
	 psPacket->Source  = m_psState->WifiMessage.source;     // ID of the sending robot
         m_tPackets.push_back(psPacket);
      } else {
       	 LOG << "[wifi] no packet" << std::endl;
      }
   }

   /****************************************/
   /****************************************/
}
