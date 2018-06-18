#include <stdlib.h>

#include "jhs.h"
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

CTestController::CTestController():
        control_step(0),
        left_wheel_speed(1),
        right_wheel_speed(1),
        wheels_actuator(NULL) {}

CTestController::~CTestController()
{

}

void CTestController::Init(TConfigurationNode& t_node)
{
    // Sensors
  //  proximity_sensor = GetSensor<CCI_EPuckProximitySensor>("epuck_proximity");
  //  light_sensor = GetSensor<CCI_EPuckLightSensor>("epuck_light");

    // Actuators
    wheels_actuator = GetActuator<CCI_EPuckWheelsActuator>("epuck_wheels");
    base_leds_actuator = GetActuator<CCI_EPuckBaseLEDsActuator>("epuck_base_leds");
    rgb_leds_actuator = GetActuator<CCI_EPuckRGBLEDsActuator>("epuck_rgb_leds");
}

void CTestController::ControlStep()
{
    control_step++;
    SInt8 invert = (control_step % 2 == 0 ? -1 : 1) ;

//    wheels_actuator->SetLinearVelocity(-invert * left_wheel_speed, invert * right_wheel_speed);

    base_leds_actuator->SwitchLED((control_step % 4), true); // Turn one of the 8 base LEDs on
    base_leds_actuator->SwitchLED(((control_step - 1) % 4), false); // Turn previous base LED off

//    rgb_leds_actuator->SetColors(CColor::RED); //invert ? CColor::RED : CColor::BLUE);
    printf("[JHS] \t control_step : %d", control_step);
//  if (control_step > 22 && control_step < 28) {
 //   rgb_leds_actuator->SetColors(CColor::GREEN);
 // }
//  if (control_step >= 28) {
 //   rgb_leds_actuator->SetColors(CColor::BLUE);
  //}

  if (control_step > 30) {
//	wheels_actuator->SetLinearVelocity(1,1);
  } 
  if (control_step > 43) {
    rgb_leds_actuator->SetColors(CColor::BLUE);
  }
  if (control_step > 44) {
    rgb_leds_actuator->SetColors(CColor::GREEN);
  }

//    usleep(50000);

//    base_leds_actuator->FrontLED(control_step % 2 == 0);
  //  base_leds_actuator->BodyLED(control_step % 2 == 1);

/*    printf("[PROXIMITY]\t");

    const CCI_EPuckProximitySensor::TReadings& proximity_sensor_readings = proximity_sensor->GetReadings();

//    for (CCI_EPuckProximitySensor::SReading reading = proximity_sensor_readings.begin(); reading != proximity_sensor_readings.end(); ++reading) 
//    for(CCI_EPuckProximitySensor::SReading reading : proximity_sensor_readings)
      for (int i = 0; i < proximity_sensor_readings.size(); i++)
      {
	  CCI_EPuckProximitySensor::SReading reading = proximity_sensor_readings[i];
	  printf("%.2f, ", reading.Value);
      }
//        printf("%.0f degrees: %.2f, ", ToDegrees(reading.Angle).GetValue(), reading.Value);

    printf("\n");

    printf("[LIGHT]\t\t");

    const CCI_EPuckLightSensor::TReadings& light_sensor_readings = light_sensor->GetReadings();

//    for(CCI_EPuckLightSensor::SReading reading: light_sensor_readings)
      for (int i = 0; i < light_sensor_readings.size(); i++)
      {
        CCI_EPuckLightSensor::SReading reading = light_sensor_readings[i]; 
        printf("%.2f, ", reading.Value);
      }
    printf("\n");
*/
    printf("\n\n");

//    double velocity = CCI_EPuckWheelsActuator::MAX_VELOCITY_CM_SEC / 4;
//
//    CVector2 vector;
//
//    for(int i = 0; i < proximity_sensor_readings.size(); ++i)
//        vector += CVector2(proximity_sensor_readings[i].Value, proximity_sensor_readings[i].Angle);
//
//    vector /= proximity_sensor_readings.size();
//
//    printf("velocity: %f\n", velocity);
//    printf("length: %f, angle: %f\n", vector.Length(), ToDegrees(vector.Angle()));
//
//    if(vector.Length() > 50)
//    {
//        if(ToDegrees(vector.Angle()).GetValue() > 0.0f)
//            wheels_actuator->SetLinearVelocity(velocity, 0.0f);
//        else
//            wheels_actuator->SetLinearVelocity(0.0f, velocity);
//    }
//    else
//        wheels_actuator->SetLinearVelocity(velocity, velocity);
}

REGISTER_CONTROLLER(CTestController, "jhs");
