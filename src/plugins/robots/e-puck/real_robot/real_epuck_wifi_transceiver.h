#ifndef REAL_EPUCK_WIFI_TRANSCEIVER_H
#define REAL_EPUCK_WIFI_TRANSCEIVER_H

namespace argos {
  class CRealEPuckWifiTransceiver;
}
#include <argos3/plugins/robots/e-puck/real_robot/real_epuck_base.h>
#include <sys/socket.h>
#include <netdb.h>
#include <vector>
#include <argos3/core/utility/datatypes/datatypes.h>
#include <arpa/inet.h>
#include <pthread.h>

// set up thread that reads from UDP socket (unless we cna set up a callback/interrupt)

namespace argos {

#define BUFSIZE 16 // max number of messages we can buffer
#define SERVICE_PORT 5000
class CRealEPuckWifiTransceiver {

public:
    CRealEPuckWifiTransceiver();
    virtual ~CRealEPuckWifiTransceiver();

    virtual void Init(CRealEPuckWifiTransceiver* this_transceiver);

    virtual void Enable();
    virtual void Disable();
   // virtual void SendMessage(UInt8 data, UInt8 destination);
    virtual bool GotNewMessage();
    virtual void BroadcastMessage(UInt8 data);
    virtual void GetLatestMessage(BaseWifiMessage* message_out);
    virtual void GetMessages(std::vector<BaseWifiMessage>* buf_out);
    virtual void ClearMessages();
    virtual void* receive_thd();
    static void* thread_helper(void* context);
private:
    UInt8 m_socket_in; // our socket
    UInt8 m_socket_out; // our socket
    std::vector<BaseWifiMessage> m_unMessageBuffer;
    bool m_wifiEnabled;
    struct sockaddr_in myaddr;
    struct sockaddr_in broadcastaddr;
    socklen_t addrlen;// = sizeof(myaddr);
    bool m_bExitThread;
    pthread_t receiveThread;
};




}


#endif
