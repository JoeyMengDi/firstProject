/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   XMLNode.h
 * Author: Administrator
 *
 * Created on 2017年8月22日, 上午9:10
 */

#ifndef XMLNODE_H
#define XMLNODE_H


/*Parameter Config XML*/
//Parameter Config XML file Node & Name
#define CONFIG_XML_NAME        "CastlesPay.xml"
#define CONFIG_XML_ROOT_NODE    "Config"
#define CONFIG_XML_COMM_NODE    "COMM_Config"
#define CONFIG_XML_DEBUG_NODE    "Debug_Mode"
#define CONFIG_XML_PLATFORM_NODE    "Platform_Config"

//AppNode & KeyNode in Debug_Mode
#define MODULE_MENULIB             "MenuLib"
#define MODULE_COMMLIB            "CommLib"
#define MODULE_MSGQUEUELIB    "MsgQueueLib"
#define MODULE_UILIB                     "UILib"
#define MODULE_TXNLIB                 "TXNLib" 
#define VALUE                                    "Value"

//AppNode & KeyNode in Platform_Config
#define PF_DISPLAY_MODE             "DisplayMode"
#define PF_PROTOCOL_MODE        "ProtocolMode"
#define PF_DEF_COMM_TYPE          "DefCommType"
#define PF_DEVICE_TYPE                  "DeviceType"
#define PF_COMM_TYPE                  "CommType"
#define PF_DEV_TYPE                        "Type"

//Platform config parameters
#define ENABLE                   "Enable"
#define DISABLE                  "Disable"
#define DISPLAY_MODE_TEXT                          "Text"
#define DISPLAY_MODE_GRAPHIC                   "Graphic"
#define DEVICE_TYPE_MP200                            "MP200"
#define DEVICE_TYPE_V3                                    "Vega3000"



/*Menu XML*/
//Menu XML file Node & Name
#define MENU_XML_NAME                          "./RES/LANG/EN/Text/MENU_CFG.xml"
#define MENU_XML_NODE                           "Menu"
#define MENU_XML_NODE_COMM             "Comm_Menu"
#define MENU_XML_NODE_DEBUG             "Debug_Mode_Menu"
#define MENU_XML_NODE_PLATFORM      "Platform_Menu"

//AppNode in Platform_Menu
#define PLATFORM_CONFIG_LIST      "PlatformConfig"
#define DISPLAY_MODE                     "DisplayMode"
#define DEFCOMM_TYPE                   "DefCommType"
#define PROTOCOL_MODE                "ProtocolMode"
#define DEVICETYPE                         "DeviceType"

//AppNode of MenuTitle in Menu 
#define MENTTITLE     "MenuTitle"
#define TITLE1              "Title1"
#define TITLE2              "Title2"
#define TITLE3              "Title3"

//AppNode & KeyNode in Debug_Mode_Menu
#define MODULE_LIST                      "ModuleList"
#define DEBUG_MODE_NODE         "DebugMode"

//AppNode & KeyNode in Menu 
#define APP_MENU_NODE             "APPMenu"
#define TITLE                                    "Title"
#define APP_LIST_APP1                   "APP1"
#define APP_LIST_APP2                   "APP2"
#define APP_LIST_APP3                   "APP3"
#define APP_LIST_APP4                   "APP4"

//Options Node
#define OPTION_1                            "Option1"
#define OPTION_2                            "Option2"
#define OPTION_3                            "Option3"
#define OPTION_4                            "Option4"
#define OPTION_5                            "Option5"
#define OPTION_6                            "Option6"
#define OPTION_7                            "Option7"
#define OPTION_8                            "Option8"

//Communication List
#define COMM_PARAM_CONFIG                         "Comm_Param_Config"
#define CFG_COMM_BT                                        "BT"
#define CFG_COMM_ETH                                     "ETH"
#define CFG_COMM_WIFI                                     "WIFI"
#define CFG_COMM_RS232                                 "RS232"
#define CFG_COMM_GPRS                                  "GPRS"
#define CFG_COMM_USB                                     "USB"
#define CFG_COMM_GSM                                    "GSM"
#define CFG_COMM_MODEM                             "MODEM"

//Lable of ETH
#define ETH_LABLE_NODE                                   "ETHLabel"
#define ETH_LABLE_IP                                           "IP"
#define ETH_LABLE_MASK                                    "Mask"
#define ETH_LABLE_GATEWAY                             "GATEWAY"
#define ETH_LABLE_DNS                                       "DNS"
#define ETH_LABLE_DHCP                                     "DHCP"
#define ETH_LABLE_HOSTIP                                  "HostIP"
#define ETH_LABLE_HOSTPORT                           "HostPort"

//Lable of GPRS
#define GPRS_LABLE_NODE                                  "GPRSLabel"
#define GPRS_LABLE_PINCODE                            "PINCode"
#define GPRS_LABLE_APN                                     "APN"
#define GPRS_LABLE_HOSTIP                                "HostIP"
#define GPRS_LABLE_HOSTPORT                          "HostPort"
#define GPRS_LABLE_SLOT                                    "Slot"
#define GPRS_LABLE_USERNAME                         "UserName"
#define GPRS_LABLE_PWD                                     "Password"
#define GPRS_LABLE_REGGSM_TIMEOUT            "RegisterGSMTimeout"
#define GPRS_LABLE_INITGPRS_TIMEOUT           "InitGPRSTimeout"
#define GPRS_LABLE_CONNHOST_TIMEOUT      "ConnectHostTimeout"

//Lable of wifi
#define WIFI_LABLE_NODE               "WifiLabel"
#define WIFI_LABLE_ESSID                  "ESSID"
#define WIFI_LABLE_PWD                 "Password"
#define WIFI_LABLE_PORT                "Port"
#define WIFI_LABLE_HOSTIP             "HostIP"
#define WIFI_LABLE_IP                       "IP"
#define WIFI_LABLE_MASK                "Mask"
#define WIFI_LABLE_GATEWAY         "GateWay"
#define WIFI_LABLE_DNS                   "DNS"
#define WIFI_LABLE_AUTOCON        "AUTOCON"
#define WIFI_LABLE_AUTOCON_Y        "YES"
#define WIFI_LABLE_AUTOCON_N        "NO"
#define WIFI_AUTOCON_ENABLE       1
#define WIFI_AUTOCON_DISABLE      2

//Lable of RS232
#define RS232_LABLE_NODE            "RS232Label"
#define RS232_LABLE_PORTID         "PortId"
#define RS232_LABLE_BAUD            "Baud"
#define RS232_LABLE_PARITY          "Parity"
#define RS232_LABLE_DATABITS     "DataBits"
#define RS232_LABLE_STOPBITS      "StopBits"

#define RS232_COM_1  "COM1"
#define RS232_COM_2  "COM2"
#define RS232_COM_3  "COM3"

#define RS232_Baud_1     "Baud1"
#define RS232_Baud_2     "Baud2"
#define RS232_Baud_3     "Baud3"
#define RS232_Baud_4     "Baud4"
#define RS232_Baud_5     "Baud5"

#define RS232_Parity_EVEN     "Evenparity"
#define RS232_Parity_ODD      "Oddparity"
#define RS232_Parity_NONE    "Noneparity"

#define RS232_1_DataBits      "DataBits_7"
#define RS232_2_DataBits      "DataBits_8"

#define RS232_1_StopBits      "StopBits_1"
#define RS232_2_StopBits      "StopBits_2"

//Lable of BT
#define BT_LABLE_NODE                      "BTLabel"
#define BT_LABLE_DEVICENAME          "DeviceName"
#define BT_LABLE_CONNTIMEOUT       "ConnTimeout"



#endif /* XMLNODE_H */

