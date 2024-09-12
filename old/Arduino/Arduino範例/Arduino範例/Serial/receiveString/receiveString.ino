int data[2];
const byte numChars = 32;
char receivedChars[numChars];

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

//接收分解字串
boolean receiveString(int *data){
  int b = 0;                // b為空格位置
  String target = ",";      // 本次搜尋逗號
  String s = "";
  String s1 = "";          // Roll
  String s2 = "";          // Pitch
      
  while (mySerial.available())
    s = mySerial.readString();  
  
  if (s != "") {
    b = s.indexOf(target) ; 
    s1 = s.substring(0,b);
    s2 = s.substring(b+1,s.length());
        
    data[0] = s1.toInt();
    data[1] = s2.toInt(); 

    return 1;
  }
  return 0;
}

/*
 * 有起始、終止字元
 * 接收字元、複製字串、分解字串、轉換成整數
 */

boolean recvWithStartEndMarkers(int *data) {  
  boolean newData = true;
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  int b = 0;                // b為空格位置
  String target = ",";      // 本次搜尋逗號
  String s = "";
  String s1 = "";          // Roll
  String s2 = "";          // Pitch
  
  while (BT.available() > 0 && newData) {
    rc = BT.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) 
          ndx = numChars - 1;
        }
        else {
          receivedChars[ndx] = '\0'; // terminate the string
          recvInProgress = false;
          ndx = 0;
          newData = false;
        }
    }
    else if (rc == startMarker)
       recvInProgress = true;
  } 
  
  while ( BT.read() >= 0) {};  // 清空藍牙緩衝區
  
  if (newData == false) {      // 代表已經接收資料
    s = receivedChars;
    b = s.indexOf(target) ; 
    s1 = s.substring(0,b);
    s2 = s.substring(b+1,s.length());
        
    data[0] = s1.toInt();
    data[1] = s2.toInt();

    return true;
  }
  return false;
}
