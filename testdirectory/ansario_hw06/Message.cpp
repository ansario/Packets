#include "Message.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Message' for a single message.
 *
 *This class represents a message which will be sent by being broken down into  
 * packets. It is the storage container which will be used to separate the dif-
 * ferent messages sent at different times.
 *
 * Author: Duncan A. Buell Edited by Omar A. Ansari
 * Date last modified: 4 November 2014
**/

/******************************************************************************
 * Constructor
**/
Message::Message()
{
	messageID = 0;
	packetCount = 0;
}

/******************************************************************************
 * Destructor
**/
Message::~Message()
{
}

/******************************************************************************
 * Accessors and Mutators
**/

/******************************************************************************
 * Accessor 'getMessageID'.
 *
 * Returns:
 *   the 'messageID'
**/
int Message::getMessageID() const
{
	return messageID;
}

/******************************************************************************
 * General functions.
**/
/******************************************************************************
 * Method to test if a message contains a given packet.
 *
 * Parameters:
 *   p - the 'Packet' to be tested
 *
 * Returns:
 *   true if the message containes the packet parameter. False if not.
**/
bool Message::contains(const Packet& p) const
{
	if (message.count(p.getPacketID()) == 1)
	{
		return true;
	} else 
	{
		return false;
	}
}

/******************************************************************************
 * Method to insert a packet into a message. This will update the packet count 
 * and messageID.
 * Parameters:
 *   p - the 'Packet' to be tested
 *
 * Returns:
 *   nothing.
**/
void Message::insert(const Packet& p)
{
	message.insert(pair<int, Packet>(p.getPacketID(), p));
	this->packetCount=p.getPacketCount();
	this->messageID = p.getMessageID();
	//message.packetCount = p.getPacketCount();
}

/******************************************************************************
 * Method to test whether a message is complete. This will test if the packetCount
 * is equal to the overall size of the message.
 * Returns:
 *   true if size of message == packetCount. False if not.
**/
bool Message::isComplete() const
{
	if (message.size()-1 == this->packetCount)
	{
		return true;
	} else
	{
		return false;
	}
}

/******************************************************************************
 * Function 'toString'.
 *
 * Returns:
 *   the 'toString' of the message as a 'vector' of packets
**/
string Message::toString() const
{
	string s = "";
	s += ("MessageID: " + getMessageID());
	//s += ("Nodes: " + message.size() + "\n");

	map<int, Packet>::const_iterator iter;

	for (iter = this->message.begin(); iter != this->message.end(); ++iter)
	{
		s += Utils::Format((*iter).second.toString());
	}

	return s;
}
