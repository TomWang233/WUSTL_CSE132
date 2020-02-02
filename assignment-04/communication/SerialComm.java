package communication;

import java.io.IOException;


import jssc.*;

public class SerialComm {
	
	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	

	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = true; // Default is to NOT be in debug mode
	}
		
	public void writeByte(byte toWrite) throws SerialPortException, IOException {
		try {
			port.writeByte(toWrite);
			if(debug) {
				StringBuilder sb = new StringBuilder();
				int i = toWrite; 
				sb.append(Integer.toHexString(i).toUpperCase());
				System.out.println("<" + sb.toString() + ">");
			}
		} catch (SerialPortException e) {
			e.printStackTrace();
		}
		
	}
	
	
}
