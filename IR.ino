#include <SoftwareSerial.h>   // 引用程式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // 藍芽接收腳, 傳送腳
char val;  // 儲存接收資料的變數

const int irReceiver = 5;                // 紅外線接收器
const int irLed  = 3;                    // 紅外線發射器
int flag=0;
int count=0;
const unsigned int frequency = 38000;    // 發射頻率(單位: Hz)
 

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
  Serial.println("BT is ready!");
  pinMode(irReceiver, INPUT);           // 把 irReceiver 接腳設置為 INPUT
  pinMode(irLed, OUTPUT);  
  tone(irLed, frequency);   
  // 設定HC-05藍牙模組，AT命令模式的連線速率。
  BT.begin(9600);
}

void loop() {
  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.print(val);
  }
    
  int ir_status = digitalRead(irReceiver);
    
   if (ir_status == 0){   //遮蔽
      if(!flag){
        delay(1000); 
        flag=1;
      }
      else{
        delay(1000);        //延遲1秒             
        BT.print('b');      //加一分
        count++;
        Serial.println(count);
      }
    }
 //Serial.println(ir_status); //印出接收狀態 
      
   
}
