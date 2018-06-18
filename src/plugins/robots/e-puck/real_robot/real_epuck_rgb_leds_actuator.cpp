/**
 * @file <argos3/plugins/robot/e-puck/real_robot/real_epuck_rgb_leds_actuator.h>
 *
 * @author Lorenzo Garattoni - <lgaratto@ulb.ac.be>
 */

#include "real_epuck_rgb_leds_actuator.h"
#include <argos3/core/utility/logging/argos_log.h>

namespace argos {

/****************************************/
/*******************
*********************/

CRealEPuckRGBLEDsActuator::CRealEPuckRGBLEDsActuator() {


}

/****************************************/
/****************************************/

CRealEPuckRGBLEDsActuator::~CRealEPuckRGBLEDsActuator() {

    SetColors(CColor::BLACK);

}

void CRealEPuckRGBLEDsActuator::SetColor(size_t un_led_number,
					 const CColor& c_color) {

  switch (un_led_number) {
   case 0:
	m_psState->LEDRed_1   = c_color.GetRed();
	m_psState->LEDGreen_1 = c_color.GetGreen();
	m_psState->LEDBlue_1  = c_color.GetBlue();
	break;
   case 1:
	m_psState->LEDRed_2   = c_color.GetRed();
	m_psState->LEDGreen_2 = c_color.GetGreen();
	m_psState->LEDBlue_2  = c_color.GetBlue();
	break;
   case 2:
	m_psState->LEDRed_3   = c_color.GetRed();
	m_psState->LEDGreen_3 = c_color.GetGreen();
	m_psState->LEDBlue_3  = c_color.GetBlue();
	break;
   case 3:
	m_psState->LEDRed_4   = c_color.GetRed();
	m_psState->LEDGreen_4 = c_color.GetGreen();
	m_psState->LEDBlue_4  = c_color.GetBlue();
	break;
   default:
    break;
  }

}


void CRealEPuckRGBLEDsActuator::SetColors(const CColor& c_color) {
	m_psState->LEDRed_1   = c_color.GetRed();
	m_psState->LEDGreen_1 = c_color.GetGreen();
	m_psState->LEDBlue_1  = c_color.GetBlue();
	m_psState->LEDRed_2   = c_color.GetRed();
	m_psState->LEDGreen_2 = c_color.GetGreen();
	m_psState->LEDBlue_2  = c_color.GetBlue();
	m_psState->LEDRed_3   = c_color.GetRed();
	m_psState->LEDGreen_3 = c_color.GetGreen();
	m_psState->LEDBlue_3  = c_color.GetBlue();
	m_psState->LEDRed_4   = c_color.GetRed();
	m_psState->LEDGreen_4 = c_color.GetGreen();
	m_psState->LEDBlue_4  = c_color.GetBlue();

}

void CRealEPuckRGBLEDsActuator::SetColors(const TLEDSettings& c_colors) {
	m_psState->LEDRed_1   = c_colors[0].GetRed();
	m_psState->LEDGreen_1 = c_colors[0].GetGreen();
	m_psState->LEDBlue_1  = c_colors[0].GetBlue();

	m_psState->LEDRed_2   = c_colors[1].GetRed();
	m_psState->LEDGreen_2 = c_colors[1].GetGreen();
	m_psState->LEDBlue_2  = c_colors[1].GetBlue();

	m_psState->LEDRed_3   = c_colors[2].GetRed();
	m_psState->LEDGreen_3 = c_colors[2].GetGreen();
	m_psState->LEDBlue_3  = c_colors[2].GetBlue();
/*
	m_psState->LEDRed_4   = c_colors[3].GetRed();
	m_psState->LEDGreen_4 = c_colors[3].GetGreen();
	m_psState->LEDBlue_4  = c_colors[3].GetBlue();
*/
	m_psState->LEDRed_4   = c_colors[0].GetRed();
	m_psState->LEDGreen_4 = c_colors[0].GetGreen();
	m_psState->LEDBlue_4  = c_colors[0].GetBlue();

}


}
