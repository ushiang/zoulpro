#include "contiki.h"//bismillahirrahmanirrahim
#include "contiki-lib.h"
#include "contiki-net.h"
#include "appInclude.h"

#include <stdio.h> /* For printf() */
#include <string.h>

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

#define MAX_PAYLOAD_LEN 120

static struct uip_udp_conn *server_conn;

PROCESS(udp_server_process, "UDP server process");
AUTOSTART_PROCESSES(/*&resolv_process,*/&udp_server_process);
/*---------------------------------------------------------------------------*/
static void tcpip_handler(void)
{
  static int seq_id;

  if(uip_newdata()) {
    
  }
}
/*---------------------------------------------------------------------------*/
static void print_local_addresses(void)
{
  int i;
  uint8_t state;

  PRINTF("Server IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
      PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
      PRINTF("\n");
    }
  }
}
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_server_process, ev, data)
{
/*
#if UIP_CONF_ROUTER
  uip_ipaddr_t ipaddr;
#endif // UIP_CONF_ROUTER */

  PROCESS_BEGIN();
  PRINTF("UDP server started response#\n");
  int i=0;
  static double *chl;//64 bits
  chl=generateRandChallenge();//int i;for(i=0;i<16;i++){printf("%d",(int)chl1[i]);}printf("\n");//shows challenge
  const double chl1[16]={chl[0],chl[1],chl[2],chl[3],chl[4],chl[5],chl[6],chl[7],chl[8],chl[9],chl[10],chl[11],chl[12],chl[13],chl[14],chl[15]};
  const double chl2[16]={!chl[0],chl[1],chl[2],!chl[3],chl[4],chl[5],!chl[6],chl[7],chl[8],!chl[9],chl[10],chl[11],!chl[12],chl[13],chl[14],!chl[15]};
  const double chl3[16]={chl[0],!chl[1],chl[2],chl[3],!chl[4],chl[5],chl[6],!chl[7],chl[8],chl[9],!chl[10],chl[11],chl[12],!chl[13],chl[14],chl[15]};
        
  printf("get response=%d\n", PUFmodel(chl1));
  printf("get response=%d\n", PUFmodel(chl2));
  printf("get response=%d\n", PUFmodel(chl3));
/*#if RESOLV_CONF_SUPPORTS_MDNS
  resolv_set_hostname("contiki-udp-server");
#endif

#if UIP_CONF_ROUTER
  uip_ip6addr(&ipaddr, UIP_DS6_DEFAULT_PREFIX, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
#endif // UIP_CONF_ROUTER */

  print_local_addresses();

  server_conn = udp_new(NULL, UIP_HTONS(3001), NULL);
  udp_bind(server_conn, UIP_HTONS(3000));

  static int seq_id=0;

  while(1) 
  {
    PROCESS_YIELD();
    if(ev == tcpip_event) 
    {
      //tcpip_handler();//herseyi dene ve burada sadace bu kod vardi unutma
      
      char buf[MAX_PAYLOAD_LEN];

      if(uip_newdata()&& seq_id==0) 
      {
        ((char *)uip_appdata)[uip_datalen()] = 0;
        PRINTF("Server received: '%s' from ", (char *)uip_appdata);
        PRINT6ADDR(&UIP_IP_BUF->srcipaddr);
        PRINTF("\n");
        ///////sending chl/////////////////////
        uip_ipaddr_copy(&server_conn->ripaddr, &UIP_IP_BUF->srcipaddr);
        PRINTF("Sending Challenges: \n");
        //sprintf(buf, "Hello from the server! (%d)", ++seq_id);
        //////challenge1 
        const double chl1[16]={chl[0],chl[1],chl[2],chl[3],chl[4],chl[5],chl[6],chl[7],chl[8],chl[9],chl[10],chl[11],chl[12],chl[13],chl[14],chl[15]};
        sprintf(buf, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",(int)chl1[0],(int)chl1[1],(int)chl1[2],(int)chl1[3],(int)chl1[4],(int)chl1[5],(int)chl1[6],(int)chl1[7],(int)chl1[8],(int)chl1[9],(int)chl1[10],(int)chl1[11],(int)chl1[12],(int)chl1[13],(int)chl1[14],(int)chl1[15]);
        PRINTF("%s\n", buf);
        uip_udp_packet_send(server_conn, chl1, sizeof(chl1));
        //////challenge2 
        const double chl2[16]={!chl[0],chl[1],chl[2],!chl[3],chl[4],chl[5],!chl[6],chl[7],chl[8],!chl[9],chl[10],chl[11],!chl[12],chl[13],chl[14],!chl[15]};
        sprintf(buf, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",(int)chl2[0],(int)chl2[1],(int)chl2[2],(int)chl2[3],(int)chl2[4],(int)chl2[5],(int)chl2[6],(int)chl2[7],(int)chl2[8],(int)chl2[9],(int)chl2[10],(int)chl2[11],(int)chl2[12],(int)chl2[13],(int)chl2[14],(int)chl2[15]);
        PRINTF("%s\n", buf);
        uip_udp_packet_send(server_conn, chl2, sizeof(chl2));
        //////challenge3
        const double chl3[16]={chl[0],!chl[1],chl[2],chl[3],!chl[4],chl[5],chl[6],!chl[7],chl[8],chl[9],!chl[10],chl[11],chl[12],!chl[13],chl[14],chl[15]};
        sprintf(buf, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",(int)chl3[0],(int)chl3[1],(int)chl3[2],(int)chl3[3],(int)chl3[4],(int)chl3[5],(int)chl3[6],(int)chl3[7],(int)chl3[8],(int)chl3[9],(int)chl3[10],(int)chl3[11],(int)chl3[12],(int)chl3[13],(int)chl3[14],(int)chl3[15]);
        PRINTF("%s\n", buf);
        uip_udp_packet_send(server_conn, chl3, sizeof(chl3));
        //////challenge4 

        //uip_udp_packet_send(server_conn, buf, strlen(buf));
        ///////sending challenge/////////////////////
        /* Restore server connection to allow data from any node */
        memset(&server_conn->ripaddr, 0, sizeof(server_conn->ripaddr));

        seq_id=1;//en sonda responslari clienttan  almak icin
      }
      int *rspsFromClient;

      if(uip_newdata()&& seq_id==1) 
      {
        rspsFromClient = uip_appdata;
        rspsFromClient[uip_datalen()] = '\0';
        printf("Responses from client:");
        for(i=0;i<3;i++){printf("%d",rspsFromClient[i]);}
        printf("\n");
      }
    }
  }
  PROCESS_END();
}
/*---------------------------------------------------------------------------*/





/*static void tcpip_handler(void)
{
  static int seq_id;
  char buf[MAX_PAYLOAD_LEN];

  if(uip_newdata()) {
    ((char *)uip_appdata)[uip_datalen()] = 0;
    PRINTF("Server received: '%s' from ", (char *)uip_appdata);
    PRINT6ADDR(&UIP_IP_BUF->srcipaddr);
    PRINTF("\n");

    uip_ipaddr_copy(&server_conn->ripaddr, &UIP_IP_BUF->srcipaddr);
    PRINTF("Responding with message: ");
    sprintf(buf, "Hello from the server! (%d)", ++seq_id);
    PRINTF("%s\n", buf);

    uip_udp_packet_send(server_conn, buf, strlen(buf));
    // Restore server connection to allow data from any node 
    memset(&server_conn->ripaddr, 0, sizeof(server_conn->ripaddr));
  }
}*/