import java.awt.event.KeyEvent;
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
		
		debug = false; // Default is to NOT be in debug mode
	}
		
	
	public void writeByte(byte toWrite) throws SerialPortException, IOException {
		
		port.writeByte(toWrite);
		if(debug) {
			StringBuilder sb = new StringBuilder();
			char c = (char)toWrite;
			int i = (int) c;
			sb.append(Integer.toHexString(i).toUpperCase());
			if(i >=48 && i <= 57 || i >=97 && i <=102) {
				System.out.println(sb.toString());
			} else {
				System.out.println("only input between 0-9 or a-f");
			}
		}
		
	}
	
	// TODO: Add available() method
	public boolean available() throws SerialPortException {
		//return boolean true if at least one byte avilable to be read 
		try {
			if(port.getInputBufferBytesCount() >= 1) {
				return true;
			}
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return false;
	
	}
	
	// TODO: Add readByte() method	
	public byte readByte() throws SerialPortException {
		//read one byte and return a byte 
		byte ret = port.readBytes(1)[0];
		// second part, we add debug
		if(debug) {
			StringBuilder sb = new StringBuilder();
			char c = (char)ret;
			int i = (int) c;
			sb.append(Integer.toHexString(i).toUpperCase());
			System.out.println("0x" + sb.toString());
		}
		return ret;
	}
	
	
	static long previous = 600;

	public static void main(String[] args) throws IOException, SerialPortException {
		SerialComm sc;
		sc = new SerialComm("/dev/cu.usbserial-DN0512RK");
		sc.port.setParams(9600, 8, 1, 0);
		while (true) {
			long now = System.currentTimeMillis();
			if (now >= previous) {
				byte mybyte = 0;
				if (StdDraw.isKeyPressed(KeyEvent.VK_UP)) {
					mybyte = 38;
				} else if (StdDraw.isKeyPressed(KeyEvent.VK_DOWN)) {
					mybyte = 40;
				} else if (StdDraw.isKeyPressed(KeyEvent.VK_LEFT)) {
					mybyte = 37;
				} else if (StdDraw.isKeyPressed(KeyEvent.VK_RIGHT)) {
					mybyte = 39;
				}
				previous = now + 600;
				sc.writeByte(mybyte);

			}
		}
	}
	// TODO: Add writeByte() method 
	
	// TODO: Add available() method
	
	// TODO: Add readByte() method	
	
	// TODO: Add a main() method
}
