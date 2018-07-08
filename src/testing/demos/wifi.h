#ifndef DEMO_WIFI_CONTROLLER_H
#define DEMO_WIFI_CONTROLLER_H

#include <argos3/core/control_interface/ci_controller.h>

//#include <argos3/core/utility/math/rng.h>


//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_proximity_sensor.h>
//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_light_sensor.h>
//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_ircom_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wifi_sensor.h>
#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wifi_actuator.h>

//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_ircom_actuator.h>
//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_wheels_actuator.h>
//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_base_leds_actuator.h>
//#include <argos3/plugins/robots/e-puck/control_interface/ci_epuck_rgb_leds_actuator.h>

namespace argos
{
    class CDemoWifiController : public CCI_Controller
    {
    public:

        CDemoWifiController();
        virtual ~CDemoWifiController();

        virtual void Init(TConfigurationNode& t_node);
        virtual void ControlStep();
        virtual void Reset() {};
        virtual void Destroy() {};

    private:

        SInt32 wheel_speed;

        // Sensors
//        CCI_EPuckProximitySensor* proximity_sensor;
  //      CCI_EPuckLightSensor* light_sensor;
//	CCI_EPuckIRComSensor* ircom_sensor;
//	CCI_EPuckCameraSensor* camera_sensor;
	CCI_EPuckWifiSensor* wifi_sensor;

        // Actuators
//        CCI_EPuckWheelsActuator* wheels_actuator;
///        CCI_EPuckBaseLEDsActuator* base_leds_actuator;
//        CCI_EPuckRGBLEDsActuator* rgb_leds_actuator;
//	CCI_EPuckIRComActuator* ircom_actuator;
//	CCI_EPuckCameraActuator* camera_actuator;
	CCI_EPuckWifiActuator* wifi_actuator;
        int control_step;
  //      int flashCounter;
//        int flashThreshold;

    };
};

#endif
