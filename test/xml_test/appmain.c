 /* 
 * File:   main.cpp
 * Author: Wens Lo
 *
 * Created on 2014年2月19日, 下午 9:20111
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctosapi.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define d_Test_File       "test.xml"

void WenswriteXML(void)
{
    xmlDocPtr pdoc = NULL;
    xmlNodePtr proot_node = NULL, pnode = NULL, pnode1 = NULL;
    int i;
    CHAR *Name[3] = {"Wens", "Re-Wens", "Co-Wens"};
    CHAR *Sex[] = {"Man", "Female", "Man"};
    CHAR *Address[] = {"Who Care?", "I Care You.", "I Don't Care!"};
    CHAR *Tel[] = {"886-917519199", "06-3359999", "02-29050098"};
    CHAR *Mail[] = {"wens1@mail.com", "wens2@mail.com", "wens3@mail.com"};
    
    pdoc = xmlNewDoc(BAD_CAST"1.0");
    
    //layter1 root
    proot_node = xmlNewNode (NULL, BAD_CAST "root");
    xmlNewProp (proot_node, BAD_CAST "version", BAD_CAST "1.0");    
    xmlDocSetRootElement (pdoc, proot_node);
    
    for(i=0;i<3;i++)
    {
        //layer2
        pnode = xmlNewNode (NULL, BAD_CAST "Person");
        xmlNewProp(pnode, BAD_CAST "Name", BAD_CAST Name[i] );
        xmlNewProp(pnode, BAD_CAST "Sex", BAD_CAST Sex[i] );
        //add layer2 in layer1
        xmlAddChild (proot_node, pnode);
        //layer3 Address
        xmlNewChild (pnode, NULL, BAD_CAST "Address", BAD_CAST Address[i]);
        //layer3 Tel:
        pnode1 = xmlNewNode (NULL, BAD_CAST "Tel");
        xmlAddChild (pnode, pnode1);
        xmlAddChild (pnode1,xmlNewText (BAD_CAST Tel[i]));
        //layer3 Mail:
        xmlNewChild (pnode, NULL, BAD_CAST "Mail", BAD_CAST Mail[i]);
    }
    xmlSaveFormatFileEnc (d_Test_File, pdoc, "UTF-8", 1);
    
    xmlFreeDoc (pdoc);
    xmlCleanupParser ();
    xmlMemoryDump ();
}
void XmlWensTest(xmlNodePtr cur)
{
    BYTE key;
    int line;
    char buffer[128];
    if(!xmlStrcmp(cur->name, (const xmlChar *) "Person"))
    {
        CTOS_KBDGet(&key);
        CTOS_LCDTClearDisplay();
        line = 1;
        sprintf(buffer, "Name: %s", xmlGetProp(cur, (const xmlChar *)"Name"));
        CTOS_LCDTPrintXY(1, 1, buffer);
        sprintf(buffer, "Sex: %s", xmlGetProp(cur, (const xmlChar *)"Sex"));
        CTOS_LCDTPrintXY(1, 2, buffer);
    }
    if(!xmlStrcmp(cur->name, (const xmlChar *) "Address"))
    {
        CTOS_LCDTPrintXY(1, 3, "Address:");
        sprintf(buffer, "%s",xmlNodeGetContent(cur));
        CTOS_LCDTPrintXY(1, 4, buffer);
    }
    if(!xmlStrcmp(cur->name, (const xmlChar *) "Tel"))
    {
        CTOS_LCDTPrintXY(1, 5, "Tel:");
        sprintf(buffer, "%s",xmlNodeGetContent(cur));
        CTOS_LCDTPrintXY(1, 6, buffer);
    }
    if(!xmlStrcmp(cur->name, (const xmlChar *) "Mail"))
    {
        CTOS_LCDTPrintXY(1, 7, "Mail:");
        sprintf(buffer, "%s",xmlNodeGetContent(cur));
        CTOS_LCDTPrintXY(1, 8, buffer);
    }
    if(cur->children != NULL)
    {
        XmlWensTest(cur->children);
    }
    if(cur->next != NULL)
    {
        XmlWensTest(cur->next);
    }
}
void DumpAllXmlDoc(STR * FileName)
{
    BYTE key;
    xmlDocPtr doc = NULL;
    xmlNodePtr cur = NULL;
    
    doc = xmlParseFile(FileName);
    if (doc == NULL) 
        return;
    else
    {
        cur = xmlDocGetRootElement(doc);
        if (cur == NULL) {
            return;
        }
        XmlWensTest(cur);
        CTOS_KBDGet(&key);
    }
}

int main(int argc, char** argv) {
     WenswriteXML();
    
    CTOS_LCDTPrintXY(1, 1, "Any Key to Cont.");
    DumpAllXmlDoc(d_Test_File);
    
    return 0;
}
