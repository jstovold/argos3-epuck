/**
 * @file <argos3/plugins/robot/e-puck/real_robot/real_epuck_rgb_leds_actuator.h>
 *
 * @author Lorenzo Garattoni - <lgaratto@ulb.ac.be>
 */

#ifndef REAL_EPUCK_RGB_LEDS_ACTUATOR_H
#define REAL_EPUCK_RGB_LEDS_ACTUATOR_H

namespace argos {
   class CRealEPuckRGBLEDsActuator;
}

#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_rgb_leds_actuator.h>
//#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_i2c_actuator.h>
#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_serial_actuator.h>

namespace argos {

   class CRealEPuckRGBLEDsActuator : virtual public CCI_EPuckRGBLEDsActuator,
                                     virtual public CRealEPuckSerialActuator {
//                                     virtual public CRealEPuckI2CActuator {

   public:

      CRealEPuckRGBLEDsActuator();
      virtual ~CRealEPuckRGBLEDsActuator();


      /**
       * Sets the color of a single LED.
       * @param un_led_number The number of the LED [0-2]
       * @param c_color The wanted color.
       */
      virtual void SetColor(size_t un_led_number,
                            const CColor& c_color);

      /**
       * Sets the same color for all LEDs.
       * @param c_color The wanted color.
       */
      virtual void SetColors(const CColor& c_color);

      /**
       * Sets the colors of all LEDs individually.
       */
      virtual void SetColors(const TLEDSettings& c_colors);

   private:

//      TI2CDeviceStream m_tDeviceStream;

   };
}
#endif


