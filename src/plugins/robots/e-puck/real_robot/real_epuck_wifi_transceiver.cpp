

#include "real_epuck_wifi_transceiver.h"
#include <argos3/core/utility/logging/argos_log.h>
#include <sys/socket.h>
#include <vector>
#include <errno.h>
// set up thread that reads from UDP socket (unless we cna set up a callback/interrupt)

namespace argos {
typedef void * (*THREADFUNCPTR)(void *);

CRealEPuckWifiTransceiver::CRealEPuckWifiTransceiver() {

}

CRealEPuckWifiTransceiver::~CRealEPuckWifiTransceiver() {
  m_bExitThread = true;
  close(m_socket_in);
 // close(m_socket_out);
}

void CRealEPuckWifiTransceiver::Init(CRealEPuckWifiTransceiver* this_transceiver) {
  if ((m_socket_in = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    LOGERR << "cannot create socket 1" << std::endl;
    return;
  }
//  if ((m_socket_out = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
//    LOGERR << "cannot create socket 2" << std::endl;
 //   return;
 // }

  memset((char*)&myaddr, 0, sizeof(myaddr));
  myaddr.sin_family = AF_INET;
  myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  myaddr.sin_port = htons(SERVICE_PORT);

  if (bind(m_socket_in, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
  	LOGERR << "bind 1 failed" << std::endl;
  }

  LOG << "Wifi receiver setup" << std::endl;

  memset((char*)&broadcastaddr, 0, sizeof(broadcastaddr));
  broadcastaddr.sin_family = AF_INET;
//  broadcastaddr.sin_addr.s_addr = htonl();
  broadcastaddr.sin_port = htons(SERVICE_PORT);
  broadcastaddr.sin_addr.s_addr = inet_addr("255.255.255.255"); //, &broadcastaddr.sin_addr);
//192.168.1.255", &broadcastaddr.sin_addr);
  int broadcast = 1;
  int err = setsockopt(m_socket_in, SOL_SOCKET, SO_BROADCAST, &broadcast,sizeof(broadcast));
   int errsv = errno;
  if (err < 0) {
      LOGERR << "sockopt fail: " << errsv << std::endl;
  }
//  int err = bind(m_socket_out, (struct sockaddr *)&broadcastaddr, sizeof(broadcastaddr));
  err = connect(m_socket_in, (struct sockaddr *)&broadcastaddr, sizeof(broadcastaddr));
  errsv = errno;
  if (err < 0) {
  	LOGERR << "connect failed: " << errsv << std::endl;
  }
  m_bExitThread = false;
//*this?
  pthread_create(&receiveThread, NULL, (THREADFUNCPTR) &thread_helper, this_transceiver);

  Enable();
}

void * CRealEPuckWifiTransceiver::thread_helper(void* context) {

  ((CRealEPuckWifiTransceiver*)context)->receive_thd();
  return NULL;
}

void * CRealEPuckWifiTransceiver::receive_thd() {

  LOG << "Wifi receive thread starting" << std::endl;
  UInt8 buf[BUFSIZE];
  struct sockaddr_in src_addr;
  socklen_t addr_len = sizeof(src_addr);
  while (!m_bExitThread) {
    if (m_wifiEnabled) {
      // check if any messages waiting, if so push into buffer
      int recvlen = recvfrom(m_socket_in, buf, BUFSIZE, MSG_DONTWAIT, (sockaddr*)&src_addr, &addr_len);
      if (recvlen > 0) {
        for (int i = 0; i < recvlen; i++) {
	  BaseWifiMessage msg;
	  msg.data = buf[i];
	  std::string str = inet_ntoa(src_addr.sin_addr);
	  msg.source = atoi(str.substr(str.find_last_of('.') + 1).c_str());
  	  m_unMessageBuffer.push_back(msg);
        }
      }
    }

    // sleep
    usleep(100);
  }
  pthread_exit(NULL);
  return NULL;


}

void CRealEPuckWifiTransceiver::Enable() {
  m_wifiEnabled = true;
}

void CRealEPuckWifiTransceiver::Disable() {
  m_wifiEnabled = false;
}

void CRealEPuckWifiTransceiver::BroadcastMessage(UInt8 data) {
  char temp_buf[1];
  temp_buf[0] = data;
//  temp_buf[1] = my_id;
  int err = sendto(m_socket_in, &temp_buf, sizeof(char), 0, (struct sockaddr *)&broadcastaddr, sizeof(broadcastaddr));

  int errsv = errno;
  if (err < 0) {
    LOGERR << "broadcast failed: " << errsv << std::endl;
  }
}

void CRealEPuckWifiTransceiver::GetLatestMessage(BaseWifiMessage* message_out) {
  if (GotNewMessage()) {
    BaseWifiMessage message = m_unMessageBuffer.back();

    message_out->data   = message.data;
    message_out->source = message.source;
    m_unMessageBuffer.pop_back();
  }
}


void CRealEPuckWifiTransceiver::GetMessages(std::vector<BaseWifiMessage>* buf_out) {
//  memcpy(buf_out, m_unMessageBuffer, sizeof(m_unMessageBuffer));
  *buf_out = m_unMessageBuffer;

}


bool CRealEPuckWifiTransceiver::GotNewMessage() {
  return (m_unMessageBuffer.size() > 0);
}

void CRealEPuckWifiTransceiver::ClearMessages() {
  m_unMessageBuffer.clear();
}


}

