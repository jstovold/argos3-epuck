#include <stdlib.h>

#include "firefly.h"
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

CDemoFireflyController::CDemoFireflyController():
        flashCounter(0),
        flashThreshold(10),
        control_step(0),
        wheel_speed(10),
        wheels_actuator(NULL) {}

CDemoFireflyController::~CDemoFireflyController()
{

}

void CDemoFireflyController::Init(TConfigurationNode& t_node)
{
//    CRandom::CRNG* rng = CRandom::CreateRNG("flashRNG");

    // Sensors
    proximity_sensor = GetSensor<CCI_EPuckProximitySensor>("epuck_proximity");
    light_sensor = GetSensor<CCI_EPuckLightSensor>("epuck_light");
//    ircom_sensor = GetSensor<CCI_EPuckIRComSensor>("epuck_ircom");
    camera_sensor = GetSensor<CCI_EPuckCameraSensor>("epuck_camera");

    // Actuators
//    ircom_actuator = GetActuator<CCI_EPuckIRComActuator>("epuck_ircom");
    wheels_actuator = GetActuator<CCI_EPuckWheelsActuator>("epuck_wheels");
    base_leds_actuator = GetActuator<CCI_EPuckBaseLEDsActuator>("epuck_base_leds");
    rgb_leds_actuator = GetActuator<CCI_EPuckRGBLEDsActuator>("epuck_rgb_leds");
    camera_actuator = GetActuator<CCI_EPuckCameraActuator>("epuck_camera");
 //   CRange<UInt32> URANGE(0,flashThreshold);
    //light_sensor->Calibrate();
    flashCounter = 2; //rng->Uniform(URANGE);
//    proximity_sensor.calibrate();
//    light_sensor.calibrate();
//    flashCounter = rand;

}

bool CDemoFireflyController::lookForFlashes() {
  // how are we going to detect other flashes? we could use the camera, but this would only detect flashes in front of us
  // what about the light sensor?
  // depends on how sensitive it is
  // may need to trial it a few times on the real bots.

  //camera_sensor->Enable();
//  camera_actuator->RequestImage();

  //UInt8** camera_readings = camera_sensor->GetCameraReadings();
//  camera_sensor->Disable();

//  if (camera_readings[0][0] > 0) { return true;}




  // going to cheat a little bit -- using IRCom to announce when we are flashing
  // arguably this isn't actually cheating, we're just using non-visible light to synchronise

//  ircom_sensor->UpdateValues();
  /*CCI_EPuckIRComSensor::TPackets packets = ircom_sensor->GetPackets();

//  while (!packets.empty())
//  {
   if (packets.size() > 0) {
    CCI_EPuckIRComSensor::SPacket* packet = packets.front();
    if (packet->Data == 0xff) {  // flash!
	ircom_sensor->ClearPackets();
	printf("detected flash\r\n");
	return true;
    }
  }
  ircom_sensor->ClearPackets();
*/
  return false;

}

void CDemoFireflyController::ControlStep()
{
    control_step++;
///    SInt8 invert = (control_step % 2 == 0 ? -1 : 1) ;


     // move randomly:
     // move forward 1
     // if something in the way, turn

// code stolen from argos-examples:
  /* Get the highest reading in front of the robot, which corresponds to the closest object */

   Real fMaxReadVal = proximity_sensor->GetReadings()[0].Value;
   UInt32 unMaxReadIdx = 0;
   if(fMaxReadVal < proximity_sensor->GetReadings()[1].Value) {
      fMaxReadVal = proximity_sensor->GetReadings()[1].Value;
      unMaxReadIdx = 1;
   }
   if(fMaxReadVal < proximity_sensor->GetReadings()[7].Value) {
      fMaxReadVal = proximity_sensor->GetReadings()[7].Value;
      unMaxReadIdx = 7;
   }
   if(fMaxReadVal < proximity_sensor->GetReadings()[6].Value) {
      fMaxReadVal = proximity_sensor->GetReadings()[6].Value;
      unMaxReadIdx = 6;
   }

   /* Do we have an obstacle in front? */
   if(fMaxReadVal > 150.0f) {
     /* Yes, we do: avoid it */
     if(unMaxReadIdx == 0 || unMaxReadIdx == 1) {
       /* The obstacle is on the left, turn right */
       wheels_actuator->SetLinearVelocity(wheel_speed, 0.0f);
//	printf("turn right");
//	printf("%f", fMaxReadVal);

     }
     else {
       /* The obstacle is on the left, turn right */
       wheels_actuator->SetLinearVelocity(0.0f, wheel_speed);
//	printf("turn left");
//	printf("%f", fMaxReadVal);
     }
   }
   else {
     /* No, we don't: go straight */
      wheels_actuator->SetLinearVelocity(wheel_speed, wheel_speed);
//	printf("go straight");
   }

    if (lookForFlashes()) {
      flashCounter++;
    }

    if (flashCounter > flashThreshold) {
//    base_leds_actuator->SwitchLED((control_step % 4), true); // Turn one of the 8 base LEDs on
  //  base_leds_actuator->SwitchLED(((control_step - 1) % 4), false); // Turn previous base LED off
      printf("flashed\r\n");
    camera_actuator->RequestImage();

      rgb_leds_actuator->SetColors(CColor::BLUE);
      //ircom_actuator->SetData(0xff);
      flashCounter = 0;
    } else {
      rgb_leds_actuator->SetColors(CColor::BLACK);
      flashCounter++;
    }

//    printf("\r\n");// %f", light_sensor->GetReading(1).Value);



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
  //  printf("\n\n");
//
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

REGISTER_CONTROLLER(CDemoFireflyController, "demo_firefly_controller");
