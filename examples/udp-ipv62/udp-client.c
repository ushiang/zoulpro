#include "contiki.h"//bismillahirrahmanirrahim
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ip/resolv.h"
#include "appInclude.h"
//#include "powertrace.h"

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>//for atof

#define DEBUG DEBUG_PRINT
#include "net/ip/uip-debug.h"

#define SEND_INTERVAL		2 * CLOCK_SECOND//15
#define MAX_PAYLOAD_LEN		2//40//bunu 40 yapinca memory gocuyor

#define UDP_CONNECTION_ADDR       fe80::212:4b00:11f4:ead6//ben ekledim
#define _QUOTEME(x) #x
#define QUOTEME(x) _QUOTEME(x)

static struct uip_udp_conn *client_conn;
/*---------------------------------------------------------------------------*/
PROCESS(udp_client_process, "UDP client process");
AUTOSTART_PROCESSES(/*&resolv_process,*/&udp_client_process);
/*---------------------------------------------------------------------------*/
static double * tcpip_handler(void)
{
  double *str;

  if(uip_newdata()) {
    str = uip_appdata;
    str[uip_datalen()] = '\0';
    //printf("Response from the server: '%s'\n", str);//powertrace_print("POWERCONSUMPTION for communication:");
  }
  return str;
}
/*---------------------------------------------------------------------------*/
static char buf[MAX_PAYLOAD_LEN];
static void timeout_handler(void)
{
  static int seq_id;

  printf("Client sending to: ");
  PRINT6ADDR(&client_conn->ripaddr);
  sprintf(buf, "Hello %d from the client", ++seq_id);
  printf(" (msg: %s)\n", buf);

  uip_udp_packet_send(client_conn, buf, strlen(buf));//alttaki koddan aldim buraya
/*#if SEND_TOO_LARGE_PACKET_TO_TEST_FRAGMENTATION
  uip_udp_packet_send(client_conn, buf, UIP_APPDATA_SIZE);
#else // SEND_TOO_LARGE_PACKET_TO_TEST_FRAGMENTATION 
  uip_udp_packet_send(client_conn, buf, strlen(buf));
#endif*/ // SEND_TOO_LARGE_PACKET_TO_TEST_FRAGMENTATION 
}
/*---------------------------------------------------------------------------*/
static void print_local_addresses(void)
{
  int i;
  uint8_t state;

  PRINTF("Client IPv6 addresses: ");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) 
  {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused && (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) 
    {
      PRINT6ADDR(&uip_ds6_if.addr_list[i].ipaddr);
      PRINTF("\n");
    }
  }
}
/*---------------------------------------------------------------------------*/
/*#if UIP_CONF_ROUTER
static void set_global_address(void)
{
  uip_ipaddr_t ipaddr;

  uip_ip6addr(&ipaddr, UIP_DS6_DEFAULT_PREFIX, 0, 0, 0, 0, 0, 0, 0);
  uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
  uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);
}
#endif *//* UIP_CONF_ROUTER */
/*---------------------------------------------------------------------------*/
/*static resolv_status_t set_connection_address(uip_ipaddr_t *ipaddr)
{

//#ifndef UDP_CONNECTION_ADDR
//#if RESOLV_CONF_SUPPORTS_MDNS
//#define UDP_CONNECTION_ADDR       contiki-udp-server.local
//#elif UIP_CONF_ROUTER
//#define UDP_CONNECTION_ADDR       fd00::212:4b00:11e6:5995//fd00:0:0:0:0212:7404:0004:0404 
//#else
//#define UDP_CONNECTION_ADDR       fe80::212:4b00:11f4:ead6//fe80:0:0:0:6466:6666:6666:6666
//#endif
//#endif // !UDP_CONNECTION_ADDR 

#define UDP_CONNECTION_ADDR       fe80::212:4b00:11f4:ead6//ben ekledim

#define _QUOTEME(x) #x
#define QUOTEME(x) _QUOTEME(x)

  resolv_status_t status = RESOLV_STATUS_ERROR;

  if(uiplib_ipaddrconv(QUOTEME(UDP_CONNECTION_ADDR), ipaddr) == 0) 
  {
    uip_ipaddr_t *resolved_addr = NULL;
    status = resolv_lookup(QUOTEME(UDP_CONNECTION_ADDR),&resolved_addr);
    if(status == RESOLV_STATUS_UNCACHED || status == RESOLV_STATUS_EXPIRED) 
    {
      PRINTF("Attempting to look up %s\n",QUOTEME(UDP_CONNECTION_ADDR));
      resolv_query(QUOTEME(UDP_CONNECTION_ADDR));
      status = RESOLV_STATUS_RESOLVING;
    } 
    else if(status == RESOLV_STATUS_CACHED && resolved_addr != NULL) 
    {
      PRINTF("Lookup of \"%s\" succeded!\n",QUOTEME(UDP_CONNECTION_ADDR));
    } 
    else if(status == RESOLV_STATUS_RESOLVING) 
    {
      PRINTF("Still looking up \"%s\"...\n",QUOTEME(UDP_CONNECTION_ADDR));
    } 
    else 
    {
      PRINTF("Lookup of \"%s\" failed. status = %d\n",QUOTEME(UDP_CONNECTION_ADDR),status);
    }
    if(resolved_addr)
      uip_ipaddr_copy(ipaddr, resolved_addr);
  } 
  else 
  {
    status = RESOLV_STATUS_CACHED;PRINTF("buraaya gelmistir\n");
  }

  return status;
}*/
/*---------------------------------------------------------------------------*/
PROCESS_THREAD(udp_client_process, ev, data)
{
  static struct etimer et;
  static double *challengeFromServer;
  static int response[4]={0,0,0,0};
  static int ri=0;
  uip_ipaddr_t ipaddr;

  PROCESS_BEGIN();
  //powertrace_start(CLOCK_SECOND*2);//every 2 second print powertrace
  PRINTF("UDP client process started response#\n");
  


/*#if UIP_CONF_ROUTER
  set_global_address();//gereksiz
#endif*/

  print_local_addresses();

//ip configuration
  uiplib_ipaddrconv(QUOTEME(UDP_CONNECTION_ADDR), &ipaddr);//IP adresine baglaniyor bununla calisiyor alttaki kodun yerine
  
////

/*
  static resolv_status_t status = RESOLV_STATUS_UNCACHED;//burada set connection adresi cagiracaksin ve calisacak Allahin izniyle
  while(status != RESOLV_STATUS_CACHED) {
    status = set_connection_address(&ipaddr);

    if(status == RESOLV_STATUS_RESOLVING) {
      PROCESS_WAIT_EVENT_UNTIL(ev == resolv_event_found);
    } else if(status != RESOLV_STATUS_CACHED) {
      PRINTF("Can't get connection address.\n");
      PROCESS_YIELD();
    }
  }*/

  /* new connection with remote host */
  client_conn = udp_new(&ipaddr, UIP_HTONS(3000), NULL);
  udp_bind(client_conn, UIP_HTONS(3001));

  PRINTF("Created a connection with the server ");//powertrace_print("POWERCONSUMPTION for authentication:");
  PRINT6ADDR(&client_conn->ripaddr);
  PRINTF(" local/remote port %u/%u\n",UIP_HTONS(client_conn->lport), UIP_HTONS(client_conn->rport));

  etimer_set(&et, SEND_INTERVAL);
  while(1) 
  {
    PROCESS_YIELD();
    if(etimer_expired(&et)) 
    {
      timeout_handler();ri=0;
      etimer_restart(&et);
    } 
    else if(ev == tcpip_event) 
    {
      challengeFromServer = tcpip_handler();

      printf("\nchallengeFromServer;");
      int i;for(i=0;i<16;i++){printf("%d",(int)challengeFromServer[i]);}/*challenge[i]=(double)(challengeFromServer[i]-'0');*/

      response[ri]=PUFmodel(challengeFromServer);
      printf("get %d. response=%d\n", ri,response[ri]);ri++;

      if(ri==3)
        break;
    }
  }
  ////////sending response////////
  printf("Client sending responses to: ");
  PRINT6ADDR(&client_conn->ripaddr);
  sprintf(buf, "%d%d%d", response[0],response[1],response[2]);
  printf(" (responses: %s)\n", buf);
  uip_udp_packet_send(client_conn, response, sizeof(response));
  ////////sending response////////

  PROCESS_END();
}
/*---------------------------------------------------------------------------*/
