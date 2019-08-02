package application;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.util.Arrays;
import java.util.ResourceBundle;

import gnu.io.CommPort;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.scene.paint.Color;

public class RootController implements Initializable {

	@FXML Label lb_00, lb_01, lb_02, lb_03, lb_04, lb_05, lb_06, lb_07;
	@FXML Label lb_10, lb_11, lb_12, lb_13, lb_14, lb_15, lb_16, lb_17;
	@FXML Label lb_20, lb_21, lb_22, lb_23, lb_24, lb_25, lb_26, lb_27;
	@FXML Label lb_30, lb_31, lb_32, lb_33, lb_34, lb_35, lb_36, lb_37;
	@FXML Label lb_40, lb_41, lb_42, lb_43, lb_44, lb_45, lb_46, lb_47;
	@FXML Label lb_50, lb_51, lb_52, lb_53, lb_54, lb_55, lb_56, lb_57;
	@FXML Label lb_60, lb_61, lb_62, lb_63, lb_64, lb_65, lb_66, lb_67;
	@FXML Label lb_70, lb_71, lb_72, lb_73, lb_74, lb_75, lb_76, lb_77;
	
	@FXML Button btn_tx_dot;
	
	boolean[][] labelFlag;
	Label[] labelRowArr;
	Label[][] labelArr;
	
	static InputStream in;
	static OutputStream out;
	static SerialPort serialPort;
	
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		try {
			new RootController().connect("COM7");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		labelArr = new Label[][] {
			{lb_00, lb_01, lb_02, lb_03, lb_04, lb_05, lb_06, lb_07},
			{lb_10, lb_11, lb_12, lb_13, lb_14, lb_15, lb_16, lb_17},
			{lb_20, lb_21, lb_22, lb_23, lb_24, lb_25, lb_26, lb_27},
			{lb_30, lb_31, lb_32, lb_33, lb_34, lb_35, lb_36, lb_37},
			{lb_40, lb_41, lb_42, lb_43, lb_44, lb_45, lb_46, lb_47},
			{lb_50, lb_51, lb_52, lb_53, lb_54, lb_55, lb_56, lb_57},
			{lb_60, lb_61, lb_62, lb_63, lb_64, lb_65, lb_66, lb_67},
			{lb_70, lb_71, lb_72, lb_73, lb_74, lb_75, lb_76, lb_77}
		};
		
		
		
		labelFlag = new boolean[8][8];
		

		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				labelFlag[i][j] = false;
			}
		}
		
		
	}


	public void dotlabelOnAction(MouseEvent event) {
		String LabelID = ((Label)event.getSource()).getId();
		
		for(int i = 0; i <8; i++) {
			for(int j = 0; j < 8; j++) {
				if(LabelID.equals(labelArr[i][j].getId())) {
					
					if(!labelFlag[i][j]) {
						labelFlag[i][j] = true;
						((Label)event.getSource()).setStyle("-fx-background-color: red;");
					}
					else {
						labelFlag[i][j] = false;
						((Label)event.getSource()).setStyle("-fx-background-color: white;");
					}
					
				}
			}
		}
	}
	
	public void btnTXdotOnAction(ActionEvent event) {
		try {
			int rowResult = 0;
			String strdotrow = "";
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 8; j++) {
					
					if(!labelFlag[i][j]) {
						if(j == 0) rowResult += 1;
						else rowResult += Math.pow(2, j);
					}
				}
				strdotrow += rowResult + "\n";
				rowResult = 0;
				//System.out.print(strdotrow);
		
			}
			//System.out.print(strdotrow);
			out.write(strdotrow.getBytes());
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
 
	//시리얼 연결을 하기위한 함수 
	private void connect(String portName) throws Exception{
		
		System.out.printf("Port : %s\n", portName);
		
		
		CommPortIdentifier portIdentifier = 
					CommPortIdentifier.getPortIdentifier(portName);
		
		if(portIdentifier.isCurrentlyOwned()) { //currentlyowned : 누가 쓰고있냐
			System.out.println("Error: Port is currently in use");
		}
		else {
			CommPort commPort = 
					portIdentifier.open(this.getClass().getName(), 2000);
			
			if(commPort instanceof SerialPort) {
				serialPort = (SerialPort) commPort;
				serialPort.setSerialPortParams( //시리얼 포트 설정
						9600, //통신 속도
						SerialPort.DATABITS_8, //몇비트 통신인가, 
						SerialPort.STOPBITS_1,  
						SerialPort.PARITY_NONE);
				
				in = serialPort.getInputStream();
				
				out = serialPort.getOutputStream();
				
				(new Thread(new SerialReader(in))).start();
				(new Thread(new SerialWriter(out))).start();
			}
		}
	}

	public static class SerialReader implements Runnable {
		InputStream in;
		
		public SerialReader(InputStream in) {
			this.in = in;
		}

		@Override
		public void run() {
			byte[] buffer = new byte[1024];
			int len = -1;
			
			try {
				while((len = this.in.read(buffer)) > -1) {
					System.out.print(new String(buffer, 0, len));
				}
			} catch (IOException e) {
		
				e.printStackTrace();
			}
			
		}
	}
	
	public static class SerialWriter implements Runnable{
		OutputStream out;
		
		public SerialWriter(OutputStream out) {
			this.out = out;
		}

		@Override
		public void run() {
			try {
				int c = 0;
				System.out.println("\n Keyboard Input Read!!!");//안내 문구 출력
				while((c = System.in.read()) > -1) {
					this.out.write(c);
				}
			} catch (IOException e) {
				
				e.printStackTrace();
			}
		}
	}
}
