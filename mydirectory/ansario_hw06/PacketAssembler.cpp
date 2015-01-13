#include "PacketAssembler.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'PacketAssembler' for assembling packets.
 *
 * Author: Duncan A. Buell modified by Omar A. Ansari
 * Date last modified: 4 November 2014
**/

/******************************************************************************
 * Constructor
**/
PacketAssembler::PacketAssembler()
{
}

/******************************************************************************
 * Destructor
**/
PacketAssembler::~PacketAssembler()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'dumpMessage'.
 *
 * Parameter:
 *   messageID - the ID of the message to be dumped
 *
 * Returns:
 *   the dumped message
**/
string PacketAssembler::dumpMessage(int messageID)
{
#ifdef EBUG
  Utils::logStream << "enter dumpMessage\n"; 
  Utils::logStream.flush();
#endif
  ///Create iterator and temp Message.
  map<int, Message>::iterator it;
  Message tempMessage;
  string s = "";

  //Check if messagesMap contains messageID.
  if (messagesMapContains(messageID))
  {
    it = messagesMap.find(messageID);
    tempMessage = it->second;  //Get iterator and value of second part of map key.
    s += tempMessage.toString();
    messagesMap.erase(messageID);

  } else //If no ID is found.
  {
    s += ("NO MESSAGE WITH ID: " + (messageID));
  }

return s;

#ifdef EBUG
  Utils::logStream << "leave dumpMessage\n"; 
  Utils::logStream.flush();
#endif
}

/******************************************************************************
 * Function 'messagesMapContains'.
 *
 * Parameter:
 *   messageID - the ID of the message to be tested
 *
 * Returns:
 *   the answer to the question
**/
bool PacketAssembler::messagesMapContains(int messageID) const
{
#ifdef EBUG
  Utils::logStream << "enter messagesMapContains\n"; 
#endif

  map<int, Message>::const_iterator it; //Create iterator to find if messageID
                                        //exists.
  for (it = messagesMap.begin(); it != messagesMap.end(); ++it )
    if (it->first == messageID)
    {
        return true;
    } else 
    {
      return false;
    }

#ifdef EBUG
  Utils::logStream << "leave messagesMapContains\n"; 
#endif
}

/******************************************************************************
 * Function 'readPacket'.
 *
 * Parameter:
 *   scanner - the 'Scanner' from which to read 
 *   outStream - the stream to which to write
 *
 * Returns:
 *   the 'packetID' of the packet read, or else the dummy value 
*/
int PacketAssembler::readPacket(Scanner& scanner, ofstream& outStream)
{
#ifdef EBUG
  Utils::logStream << "enter readPacket\n"; 
#endif
  //Create local vairables. 
  int returnValue = 0;
  int messageID = 0;
  int packetID = 0;
  Message msg;
  Packet p;

  p = Packet(scanner);


  messageID = p.getMessageID();
  //cout << messageID << endl;
  
  
  if (!messagesMapContains(messageID)){ //If map does not contain messageID
    //create new message and insert packet.
    msg = Message();
    msg.insert(p);

    messagesMap.insert(pair<int, Message>(messageID, msg));
  } else  
  {
    //If map does contain messageID, insert packet.
    map<int, Message>::iterator it = messagesMap.find(messageID);
    (*it).second.insert(p);

  }

  if (messagesMap.find(messageID)->second.isComplete())
  {
    
    returnValue = messageID;

  }

  return returnValue;


#ifdef EBUG
  Utils::logStream << "leave readPacket\n"; 
#endif
}

/******************************************************************************
 * Function 'runForever'.
 *
 * Parameter:
 *   scanner - the 'Scanner' from which to read 
 *   outStream - the stream to which to write
**/
void PacketAssembler::runForever(Scanner& scanner, ofstream& outStream)
{
#ifdef EBUG
  Utils::logStream << "enter runForever\n"; 
#endif

//While there is more input, read and dump data.
while(scanner.hasNext())
{
	int messageID = -1;
  messageID = this->readPacket(scanner, outStream);

  if (messageID > -1)
  {
    outStream << dumpMessage(messageID) << endl;
  }
 
}

#ifdef EBUG
  Utils::logStream << "leave runForever\n"; 
#endif
}
