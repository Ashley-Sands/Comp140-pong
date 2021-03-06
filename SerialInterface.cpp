#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>

SerialInterface::SerialInterface()
{
	std::vector <serial::PortInfo> devicesFound = serial::list_ports();

	std::vector <serial::PortInfo>::iterator iter = devicesFound.begin();

	while (iter != devicesFound.end())
	{
		serial::PortInfo device = *iter++;
		std::string port = device.port.c_str();

		if (TryConnection(port))
			break;
		
	}
}



SerialInterface::SerialInterface(int port)
{
	std::string comPort = "COM" + std::to_string(port);
	TryConnection(comPort);
}


SerialInterface::~SerialInterface()
{}
bool SerialInterface::TryConnection(std::string port)
{
	try {
		mySerial = new serial::Serial(port, 9600, serial::Timeout::simpleTimeout(25));

		if (mySerial->isOpen())
		{
			std::cout << "Connection success: " << port << "\n";
			connect = true;
			return true;
		}
	}
	catch (std::exception &e) {

	}

	std::cout << "Failed to connecnt to " << port << "\n";
	return false;

}

void SerialInterface::send( std::string msg )
{
	if (connect)
	{
		mySerial->write( msg );
	}
}

void SerialInterface::getButton()
{
	if (connect)
	{
		mySerial->write( "B" );

		std::string result = mySerial->readline();

		std::string b1 = result.substr( 0, 1 );
		std::string b2 = result.substr( 2, 1 );

		button1 = std::stoi( b1 );
		button2 = std::stoi( b2 );
		
	}
}

void SerialInterface::getPositions()
{
	if (connect)
	{
		mySerial->write( "P" );

		std::string result = mySerial->readline();

		//std::cout << result << std::endl;


		if (result.length() > 5) {
			std::string sub1 = result.substr( 0, 4 );
			pot1 = std::stoi( sub1 );

			std::string sub2 = result.substr( 5, 9 );
			pot2 = std::stoi( sub2 );
		}

	}
}  

void SerialInterface::close()
{
	mySerial->flush();
	mySerial->close();
}