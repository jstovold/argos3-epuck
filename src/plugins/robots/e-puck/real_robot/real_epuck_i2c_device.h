/**
 * @file <argos3/plugins/robots/e-puck/real_robot/real_epuck_i2c_device.h>
 *
 * @author Lorenzo Garattoni - <lgaratto@ulb.ac.be>
 * @author Carlo Pinciroli <cpinciro@ulb.ac.be>
 */

#ifndef REAL_EPUCK_I2C_DEVICE_H
#define REAL_EPUCK_I2C_DEVICE_H

#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_base.h>

namespace argos {

   /** The type of the device stream */
   typedef int TI2CDeviceStream;

// this is a fucking awful way of doing this. but i'm tired
/*typedef struct {
   BaseRangeAndBearingMessage RBMessage; // 8 bytes
   SInt16 Proximity[8];                  // 8 x 2 bytes = 16 bytes
   UInt16  Battery_LOW;                   // 2 byte battery low
   SInt16 Accel[3];                      // (3 accelerator sensor readings) x 2 bytes = 8 bytes
   SInt16 Micro[4];                      // (3 micro-volume sensor readings + 1 of PADDING) x 2 byte$
   SInt16 Light[8];                      // 8 x 2 bytes = 16 bytes
   UInt16 RBhasReceived;                 // 2 bytes
   UInt16 IRComHasReceived;              // 2 bytes
   BaseIRComMessage IRComMessage;        // 8 bytes
} BaseSensorState;







typedef struct {
    SInt16 LWheel;               // 2 bytes
    SInt16 RWheel;               // 2 bytes
    UInt8 Speaker;               // 1 byte
    UInt8 BaseLEDs;                // 1 byte
    UInt8 LEDRed_1;                // 1 byte
    UInt8 LEDGreen_1;              // 1 byte
    UInt8 LEDBlue_1;               // 1 byte
    UInt8 LEDRed_2;                // 1 byte
    UInt8 LEDGreen_2;              // 1 byte
    UInt8 LEDBlue_2;               // 1 byte
    UInt8 LEDRed_3;                // 1 byte
    UInt8 LEDGreen_3;              // 1 byte
    UInt8 LEDBlue_3;               // 1 byte
    UInt8 LEDRed_4;                // 1 byte
    UInt8 LEDGreen_4;              // 1 byte
    UInt8 LEDBlue4;                // 1 byte
    UInt8 additional;              // 1 byte
} I2CActuatorState;


typedef struct {
  SInt16 Proximity[8];
  SInt16 Micro[4];
  UInt8  Selector;
  SInt16 StepsL;
  SInt16 StepsR;
  UInt8  TVRemote;
} I2CSensorState;
*/
//8 x Prox (16)
//4 x Mic (8)
//Selector (1)
//Left steps (2)
//Right steps (2)
//TV remote (1)



   class CRealEPuckI2CDevice {

   public:

      virtual ~CRealEPuckI2CDevice() {}

      /* Initializes the I2C device management. */
      static void Init();

      /**
       * Opens the stream for the wanted device.
       * @param n_address The address of the device.
       * @return A stream for the wanted device.
       * @throws CARGoSException if an error occurs
       */
      TI2CDeviceStream OpenDevice(SInt16 n_address);

      /**
       * Closes the stream for the wanted device.
       * @param t_stream The device stream, which must have been opened beforehand
       * @throws CARGoSException if an error occurs
       */
      void CloseDevice(TI2CDeviceStream t_stream);

      /**
       * Reads a register from the device stream.
       * @param t_stream The device stream, which must have been opened beforehand
       * @param n_register The id of the wanted register
       * @param n_count How many bytes to read; can be either 1 or 2
       * @throws CARGoSException if an error occurs
       * @see OpenDevice
       */
      UInt16 ReadRegister(TI2CDeviceStream t_stream,
                          SInt8 n_register,
                          SInt16 n_count);

      /**
       * Writes a value into a register.
       * @param t_stream The device stream, which must have been opened beforehand
       * @param n_register The id of the wanted register
       * @param n_value The value to write
       * @throws CARGoSException if an error occurs
       * @see OpenDevice
       */
      void WriteRegister(TI2CDeviceStream t_stream,
                         SInt8 n_register,
                         SInt8 n_value);

      /**
       * Writes data onto the device stream.
       * @param t_stream The device stream, which must have been opened beforehand
       * @param n_buffer The buffer containing the data
       * @param n_count How many bytes to write
       * @throws CARGoSException if an error occurs
       * @see OpenDevice
       */
      void WriteData(TI2CDeviceStream t_stream,
                     const SInt8* n_buffer,
                     SInt16 n_count);
 static void ThreadCleanup();

  static void convertActuatorState(BaseActuatorState* baseState, I2CActuatorState* i2c_state);
  static void convertSensorState(I2CSensorState* i2c_state, BaseSensorState* base_state);

//  static void unpackStruct_actuator(I2CActuatorState* i2c_state, UInt8* output_arr);

   private:
      /** This mutex protects the concurrent access to read/write i2c operations */
      static pthread_mutex_t m_tIOMutex;

   };

}

#endif
