#include "Packet.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Packet' for a single packet. The class houses a single packet of data
 * which is a larger part of an overall message. This class includes all the 
 * mutator and accessor methods needed to use the packets in a message.
 *
 * Author: Duncan A. Buell modified by Omar A. Ansari
 * Date last modified: 4 November 2014
**/

/******************************************************************************
 * Constructor
**/
Packet::Packet()
{	//Dummy values.
	this->messageID = 999;
	this->packetCount = 999;
	this->packetID = 999;
	this->payload = "DUMMY";
}

/******************************************************************************
 * Constructor with data supplied.
**/
Packet::Packet(Scanner& scanner)
{	//Read in data from Scanner.
	readPacket(scanner);
}

/******************************************************************************
 * Destructor
**/
Packet::~Packet()
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
int Packet::getMessageID() const
{
	return this->messageID;
}

/******************************************************************************
 * Accessor 'getPacketCount'.
 *
 * Returns:
 *   the 'packetCount'
**/
int Packet::getPacketCount() const
{
	return this->packetCount;
}

/******************************************************************************
 * Accessor 'getPacketID'.
 *
 * Returns:
 *   the 'packetID'
**/
int Packet::getPacketID() const
{
	return this->packetID;
}

/******************************************************************************
 * Accessor 'getPayload'.
 *
 * Returns:
 *   the 'payload'
**/
string Packet::getPayload() const
{
	return this->payload;
}

/******************************************************************************
 * General functions.
**/
/******************************************************************************
 * Method to compare two packets.
 *
 * Parameter:
 *   that - the packet to be tested against 'this' packet
 *
 * Returns:
 *   the integers -1, 0, 1 according as the comparison goes 
**/
int Packet::compareTo(const Packet& that) const
{
	int returnValue = -999;

	if (this->packetID < that.getPacketID())
	{
		returnValue = -1;

	} else if (this->packetID == that.getPacketID())
	{
		returnValue = 0;
	} else {
		returnValue = 1;
	}

	return returnValue;
}

/******************************************************************************
 * Method to test two packets for equality.
 *
 * Parameter:
 *   that - the packet to be tested against 'this' packet
 *
 * Returns:
 *   True if the compareTo(that) == 0
**/
bool Packet::equals(const Packet& that) const
{
	if (compareTo(that) == 0)
	{
		return true;
	} else
	{
		return false;
	}
}

/******************************************************************************
 * Method to read a packet.
 *
 * Parameter:
 *   scanner - the 'Scanner' to be read from
 *
 * Returns:
 *   the packet as read in from scanner.
**/
void Packet::readPacket(Scanner& scanner)
{
	this->messageID = scanner.nextInt();
	this->packetID = scanner.nextInt();
	this->packetCount = scanner.nextInt();
	this->payload = scanner.nextLine();
}


/******************************************************************************
 * Function 'toString'.
 *
 * Returns:
 *   the 'toString' of the class, that is, of the variables in this packet
**/
string Packet::toString() const
{
	string s = "";

	s += (Utils::Format(this->getMessageID()) + "	") ;
	s += (Utils::Format(this->getPacketID()) + "	") ;
	s += (Utils::Format(this->getPacketCount()) + "	") ;
	s += (Utils::Format(this->getPayload()) + "	") ;
	cout << s;
	return s;
}
