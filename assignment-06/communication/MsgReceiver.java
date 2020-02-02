package communication;

import java.nio.charset.StandardCharsets;

import jssc.*;

public class MsgReceiver {
	
	final private SerialComm port;
	private int b1;
	private int b2;
	public MsgReceiver(String portname) throws SerialPortException {
		port = new SerialComm(portname);
	}
	private int count = 0;
	public enum State {
		check,
		timestamp,
		start, 
		temp,
		potential,
		debug,
		error,
	}
	private State currentState = State.check;
	private final double[] rolling = new double[5];
	
	public void run() throws SerialPortException {
		// insert FSM code here to read msgs from port
		// and write to console
		byte magic = port.readByte();

		while(true) {
			switch(currentState) {
			case check:
				//only read 
				while(magic != 33) {
					magic = port.readByte();
					currentState = State.check;
				} // break out when reads magic number
				magic = port.readByte();
				//System.out.println("magic number is " + magic);
				currentState = State.start;
				break;
			
			case start:
				if(magic == 48) {
					currentState = State.debug;
				} else if (magic == 49) {
					currentState = State.error;
				} else if (magic == 50) {
					currentState = State.timestamp;
				} else if (magic == 51) {
					currentState = State.potential;
				} else if (magic == 52) {
					currentState = State.temp;
				} else {
					currentState = State.check;
					System.out.println("error!");
				}
				break;
			
			case debug:
				//to do
				b1 = port.readByte();
				b2 = port.readByte();
				int debug_count = ((b1 << 8) + (b2 & 0xFF));
				byte[] byte_arr = new byte[debug_count];
				for(int error = 0; error < debug_count; ++error) {
					byte_arr[error] = port.readByte();
				}
				String debug_output = new String(byte_arr, StandardCharsets.UTF_8);
				System.out.println(debug_output);
				currentState = State.check;
				break;
			
			case error:
				b1 = port.readByte();
				b2 = port.readByte();
				int error_count = ((b1 << 8) + (b2 & 0xFF));
				//System.out.print("reading byte " + error_count);
				byte[] byte_arr1 = new byte[error_count];
				for(int error = 0; error < error_count; ++error) {
					byte_arr1[error] = port.readByte();
					//System.out.print("reading byte " + byte_arr[error]);
				}
				String error_output = new String(byte_arr1, StandardCharsets.UTF_8);
				System.out.println(error_output);
				currentState = State.check;
				break;
			
			case potential:
				//two bytes 
				b1 = port.readByte();
				b2 = port.readByte();
				int c = ((b1 << 8) + (b2 & 0xFF));
				System.out.println("raw voltage is " + c);
				double ret4 = c/ 1023.0 * 5;
				ret4 = ret4 * 100;
				ret4 = (int)ret4;
				ret4/=100;
				System.out.println("converted voltage is " + ret4);
				currentState = State.check;
				break;
		
			case temp:
				b1 = port.readByte();
				b2 = port.readByte();
				long t3 = ((b1 << 8) + (b2 & 0xFF));
				System.out.println("raw temperature is " + t3);
				double temp = (t3*(5/1023.0) - 0.75)*100.0 + 25.0;
				temp = temp * 100;
				temp = (int)temp;
				temp /= 100;
				System.out.println("converted temperature is " + temp);
				rolling[count%5] = temp;
				count++;
				double sum = 0;
				for(int i = 0; i < 5; ++i) {
					sum += rolling[i];
				}
				double ret = sum / 5.0;
				ret = ret *100;
				ret=(int)ret;
				ret/=100;
				currentState = State.check;
				System.out.println("filtered temperature is " + ret);
				break;
			
			case timestamp:
				b1 = port.readByte();
				b2 = port.readByte();
				byte b3 = port.readByte();
				byte b4 = port.readByte();
				long ret2 = ((b1<<24) + (b2<<16) + (b3<<8) + (b4 & 0xFF));
				currentState = State.check;
				System.out.println("number of milliseconds since reset: " + ret2);
				break;
			
			default:
				break;
				
			}
		}
	}

	public static void main(String[] args) throws SerialPortException {
		MsgReceiver msgr = new MsgReceiver("/dev/cu.usbserial-DN03FDM5"); // Adjust this to be the right port for your machine
		msgr.run();
	}
}
