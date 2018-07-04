/**
 * @file <argos3/plugins/robots/e-puck/real_robot/real_epuck_i2c_device.cpp>
 *
 * @author Lorenzo Garattoni - <lgaratto@ulb.ac.be>
 */

#include "real_epuck_i2c_device.h"

#include <argos3/core/utility/configuration/argos_exception.h>
#include <argos3/core/utility/logging/argos_log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h> /* for I2C_SLAVE */
#include <linux/i2c.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

namespace argos {

pthread_mutex_t CRealEPuckI2CDevice::m_tIOMutex;
UInt8 maxRetries = 10;

/****************************************/
/****************************************/

void CRealEPuckI2CDevice::Init() {
    ::pthread_mutex_init(&m_tIOMutex, NULL);
}

/****************************************/
/****************************************/
void CRealEPuckI2CDevice::ThreadCleanup(){


    pthread_mutex_unlock(&m_tIOMutex);


}
/****************************************/
/****************************************/

TI2CDeviceStream CRealEPuckI2CDevice::OpenDevice(SInt16 n_address) {


    pthread_mutex_lock(&m_tIOMutex);

    TI2CDeviceStream tStream = ::open("/dev/i2c-3", O_RDWR);
    if(tStream == -1) {

        pthread_mutex_unlock(&m_tIOMutex);

        THROW_ARGOSEXCEPTION("Unable to open the I2C device stream: " << ::strerror(errno));
    }
    if(::ioctl(tStream, I2C_SLAVE, n_address) == -1) {

        pthread_mutex_unlock(&m_tIOMutex);

        THROW_ARGOSEXCEPTION("Unable to configure the I2C device stream: " << ::strerror(errno));
    }

    pthread_mutex_unlock(&m_tIOMutex);


    return tStream;
}

/****************************************/
/****************************************/

void CRealEPuckI2CDevice::CloseDevice(TI2CDeviceStream t_stream) {


    pthread_mutex_lock(&m_tIOMutex);


    if(::close(t_stream)) {

        pthread_mutex_unlock(&m_tIOMutex);

        THROW_ARGOSEXCEPTION("Unable to close the I2C device stream: " << ::strerror(errno));
    }

    pthread_mutex_unlock(&m_tIOMutex);



}

/****************************************/
/****************************************/

UInt16 CRealEPuckI2CDevice::ReadRegister(TI2CDeviceStream t_stream,
                                         SInt8 n_register,
                                         SInt16 n_count) {


    pthread_mutex_lock(&m_tIOMutex);

    UInt8 unData[2] = {0,0};
    UInt8 nRetries = 0;

    if(n_count < 1 || n_count > 2) {

        pthread_mutex_unlock(&m_tIOMutex);

        LOGERR << "CRealEPuckI2CDevice::ReadRegister()"
               << "can only read 1 or 2 bytes from device stream; requested "
               << n_count;
    }

    while (nRetries < maxRetries && ::write(t_stream, &n_register, 1) != 1) {nRetries++;}
    if (nRetries == maxRetries) {

        pthread_mutex_unlock(&m_tIOMutex);

        LOGERR << "CRealEPuckI2CDevice::ReadRegister(): "
               << "Unable to send data to the I2C device stream: "
               << ::strerror(errno);
    }

    nRetries = 0;
    while (nRetries < maxRetries && ::read(t_stream, &unData, n_count) != n_count) {nRetries++;}

    if(nRetries == maxRetries) {

        pthread_mutex_unlock(&m_tIOMutex);

        LOG << "CRealEPuckI2CDevice::ReadRegister(): "
            << "Unable to read data from the I2C device stream: "
            << ::strerror(errno);
    }

    pthread_mutex_unlock(&m_tIOMutex);


    return (unData[1] << 8) + unData[0];
}

/****************************************/
/****************************************/

void CRealEPuckI2CDevice::WriteRegister(TI2CDeviceStream t_stream,
                                        SInt8 n_register,
                                        SInt8 n_value) {

    SInt8 unData[2];
    unData[0] = n_register;
    unData[1] = n_value;
    WriteData(t_stream, &unData[0], 2);

}

void CRealEPuckI2CDevice::convertActuatorState(BaseActuatorState* baseState, I2CActuatorState* i2c_state) {

//  I2CActuatorState state;
//  I2CActuatorState* returnState = &state;

  i2c_state->LWheel     = baseState->LWheel;
  i2c_state->RWheel     = baseState->RWheel;
  i2c_state->Speaker    = 0xFF;
  i2c_state->BaseLEDs   = baseState->BaseLEDs;

  i2c_state->LEDRed_1   = baseState->LEDRed_1;
  i2c_state->LEDGreen_1 = baseState->LEDGreen_1;
  i2c_state->LEDBlue_1  = baseState->LEDBlue_1;

  i2c_state->LEDRed_2   = baseState->LEDRed_2;
  i2c_state->LEDGreen_2 = baseState->LEDGreen_2;
  i2c_state->LEDBlue_2  = baseState->LEDBlue_2;

  i2c_state->LEDRed_3   = baseState->LEDRed_3;
  i2c_state->LEDGreen_3 = baseState->LEDGreen_3;
  i2c_state->LEDBlue_3  = baseState->LEDBlue_3;

  i2c_state->LEDRed_4   = baseState->LEDRed_4;
  i2c_state->LEDGreen_4 = baseState->LEDGreen_4;
  i2c_state->LEDBlue_4  = baseState->LEDBlue_4;

  i2c_state->additional = 0x00;  //baseState->RequestImage;

  i2c_state->IRComEnabled = baseState->IRComEnabled;
  i2c_state->IRComMessageData = baseState->IRComMessageData;

 // return state;
}


void CRealEPuckI2CDevice::convertSensorState(I2CSensorState* i2c_state, BaseSensorState* base_state) {

//  BaseSensorState state;
//  BaseSensorState* baseState = &state;
//    LOG << "[JHS-5] in convertSensorState" << std::endl;

  for (int i = 0; i < 8; i++) {
    base_state->Proximity[i] = i2c_state->Proximity[i];
    base_state->Light[i] = i2c_state->Light[i];
//    base_state->RBMessage[i] = 0x00;
  }
  
  base_state->IRComMessage = i2c_state->IRComMessage;

  for (int i = 0; i < 4; i++) {
    base_state->Micro[i] = i2c_state->Micro[i];
  }

  base_state->Accel[0] = 0x0000;
  base_state->Accel[1] = 0x0000;
  base_state->Accel[2] = 0x0000;
  base_state->IRComHasReceived = i2c_state->IRComHasReceived;

//  base_state->RBhasReceived = 0x0000;
  base_state->Battery_LOW = 0x0000;

//  if (i2c_state->ImageReceived == 0x01) {
  //  LOG << "[JHS-5] image received" << std::endl;
    //memcpy(base_state->image, i2c_state->image, 4800);
  //} else {
   // LOG << "[JHS-5] no image received" << std::endl;
 // }
  //return state;
}





/****************************************/
/****************************************/

void CRealEPuckI2CDevice::WriteData(TI2CDeviceStream t_stream,
                                    const SInt8* n_buffer,
                                    SInt16 n_count) {


    pthread_mutex_lock(&m_tIOMutex);

    ssize_t nWritten = 0;
    UInt32 unRetries = 0;
    size_t unLeftToWrite = n_count;

//   LOG << "[JHS-2] to write: " << unLeftToWrite << std::endl;

    SInt8* pnCurrentPos = (SInt8*) n_buffer;
    do {
        nWritten = ::write(t_stream, pnCurrentPos, unLeftToWrite);
        if (nWritten < 0 && unRetries > maxRetries) {

            pthread_mutex_unlock(&m_tIOMutex);

            LOGERR << "CRealEPuckI2CDevice::WriteData(): "
                   << "Unable to send data to the I2C device stream: "
                   << ::strerror(errno);
	    break;
        } else if (nWritten < 0){
            ++unRetries;
        } else {
            unLeftToWrite -= nWritten;
            pnCurrentPos += nWritten;
        }
//        LOG << "[JHS-2] written: " << nWritten << std::endl;

    } while (unLeftToWrite != 0);

    pthread_mutex_unlock(&m_tIOMutex);


}

/****************************************/
/****************************************/

}
