package communication;

import java.io.IOException;
import java.util.Scanner;

import jssc.SerialPortException;

public class PCToMorseCode {
	public static void main(String[] args) throws SerialPortException {		

		// TODO:  Fix this: 
		//           a) Uncomment to create a SerialComm object
		//           b) Update the "the port" to refer to the serial port you're using
		//              (The port listed in the Arduino IDE Tools>Port menu.		
		//           c) Deal with the unresolved issue
		// SerialComm port = new SerialComm("the port");

		
		// TODO: Complete section 6 of the Studio (gather sanitized user input
		//       and send it to the Arduino)
		SerialComm comm = new SerialComm("/dev/cu.usbserial-DN03FDM5");
		boolean going = true;
		boolean valid = true;
		
		System.out.println("please input: ");
		
		Scanner in = new Scanner(System.in);
		String input = in.nextLine();
//		while(check) {
//			
//			System.out.println("input format wrong, please enter input in the size of 1");
//			input = in.nextLine();
//		}
		byte[] arr = input.getBytes();

		for(byte b : arr) {
			if(b >=44 && b <= 57 ||  //0-9
					b >=97 && b <=122 ||  // a-z
					b >=65 && b <=90 || //A-Z
					b== 34 || b == 58 ||
					b== 61 || b == 63 || b == 64 ||
					b == 92 || b == 32
					) {
				//System.out.println("sending byte...");
				//comm.writeByte(b);
				//going=true;
				valid = true;
			} else {
				//System.out.println("input not valid, please input 0-9, A-Z, a-z ...");
				valid = false;
				//going = false;
				//input = in.nextLine();
			}	
		}

		//System.out.println("here");
		if(valid) {
			for(byte b : arr) {
				System.out.println("sending byte...");
				try {
					comm.writeByte(b);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}else {
			System.out.println("input not valid, please input 0-9, A-Z, a-z ...");
		}
	}
}


