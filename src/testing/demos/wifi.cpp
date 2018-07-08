#include <stdlib.h>

#include "wifi.h"
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <argos3/core/utility/logging/argos_log.h>
#include <argos3/core/utility/math/vector2.h>
static std::ofstream file;

#define LOG_FILE_INIT(FILENAME) if (file) file.open (FILENAME);
#define LOG_FILE(SMTHG) if (file.is_open()) file << SMTHG;
#define LOG_FILE_CLOSE() if (file.is_open()) file.close();

using namespace argos;

CDemoWifiController::CDemoWifiController():
        control_step(0) {}

CDemoWifiController::~CDemoWifiController()
{

}

void CDemoWifiController::Init(TConfigurationNode& t_node)
{
//    CRandom::CRNG* rng = CRandom::CreateRNG("flashRNG");

    // Sensors
//    proximity_sensor = GetSensor<CCI_EPuckProximitySensor>("epuck_proximity");
  //  light_sensor = GetSensor<CCI_EPuckLightSensor>("epuck_light");
//    ircom_sensor = GetSensor<CCI_EPuckIRComSensor>("epuck_ircom");
//    camera_sensor = GetSensor<CCI_EPuckCameraSensor>("epuck_camera");
	wifi_sensor = GetSensor<CCI_EPuckWifiSensor>("epuck_wifi");
    // Actuators
//    ircom_actuator = GetActuator<CCI_EPuckIRComActuator>("epuck_ircom");
//    wheels_actuator = GetActuator<CCI_EPuckWheelsActuator>("epuck_wheels");
  //  base_leds_actuator = GetActuator<CCI_EPuckBaseLEDsActuator>("epuck_base_leds");
   // rgb_leds_actuator = GetActuator<CCI_EPuckRGBLEDsActuator>("epuck_rgb_leds");
  //  camera_actuator = GetActuator<CCI_EPuckCameraActuator>("epuck_camera");
 //   CRange<UInt32> URANGE(0,flashThreshold);
	wifi_actuator = GetActuator<CCI_EPuckWifiActuator>("epuck_wifi");
    //light_sensor->Calibrate();
    //flashCounter = 2; //rng->Uniform(URANGE);
//    proximity_sensor.calibrate();
//    light_sensor.calibrate();
//    flashCounter = rand;

}

void CDemoWifiController::ControlStep()
{
    control_step++;

    if (control_step % 15 == 1) {
      wifi_actuator->SendMessage(1);
	printf("Message sent");
    }

    if (wifi_sensor->PacketAvailable()) {
 	CCI_EPuckWifiSensor::TPackets* allpackets = &(wifi_sensor->GetPackets());
	CCI_EPuckWifiSensor::SPacket* msg = allpackets->back();
	allpackets->pop_back();
	printf("Packet received: data = %d, source = %d", msg->Data, msg->Source);
    }
    printf("\r\n");




}

REGISTER_CONTROLLER(CDemoWifiController, "demo_wifi_controller");
