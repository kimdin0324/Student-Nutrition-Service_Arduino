#include <AddicoreRFID.h>
#include <SPI.h>
 
#define    uchar    unsigned char
#define    uint    unsigned int


uchar serNumA[5];
 
uchar fifobytes;
uchar fifoValue;
 
AddicoreRFID myRFID;

 String a[] ={"콩,땅콩,우유"};
 String b[] ={"사과,토마토"};
 String c[] ={"옥수수"};
 String d[] ={"없음"};

 int number = 1;
 

const int chipSelectPin = 10;
const int NRSTPD = 5;
const int speakerPin = 8; //스피커가 연결된 디지털핀 설정
 
//Maximum length of the array
#define MAX_LEN 16
 
void setup() {                
  Serial.begin(9600);            
  SPI.begin();
  
  pinMode(chipSelectPin,OUTPUT);            
  digitalWrite(chipSelectPin, LOW);      
  pinMode(NRSTPD,OUTPUT);                    
  digitalWrite(NRSTPD, HIGH);
 
  myRFID.AddicoreRFID_Init();  
}
 
void loop()
{
  uchar i, tmp, checksum1;
    uchar status;
  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr;    //Selection operation block address 0 to 63
  String mynum = "";
  str[1] = 0x4400;
        
    //RFID 태그의 타입을 리턴
    status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);    
    if (status == MI_OK)    //MIFARE 카드일때만 작동
    {
          tone(speakerPin,2000,100);

    }
 
  //RFID 충돌방지, RFID 태그의 ID값(시리얼넘버) 등 저장된 값을 리턴함. 4Byte
    status = myRFID.AddicoreRFID_Anticoll(str);
    if (status == MI_OK)      //MIFARE 카드일때만 작동
    {
          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];

       
            if(str[0] == 204){

              Serial.println("김동현 학생"); 
              Serial.print("오늘은 ");
              Serial.print(number);
              Serial.println("번째 순서이시네요!");
              Serial.print("오늘의 주의식품은 : ");
              for(int i=0; i<5; i++){
                  Serial.println(a[i]);
                  if(a[i] == NULL){
                    break;
                  }
                  break;
                  
                }
                
                Serial.println("--------------------------------------");
                   
            } else if(str[0] == 85) {            
                Serial.println("강신희 학생");
               Serial.print("오늘은 ");
              Serial.print(number);
              Serial.println("번째 순서이시네요!");
                Serial.print("오늘의 주의식품 : ");
                for(int i=0; i<5; i++){
                  Serial.println(b[i]);
                  if(b[i] == NULL){
                    break;
                  }
                  break;
                  
                }

                Serial.println("--------------------------------------");
                
            }else if(str[0] == 62) {            
                Serial.println("탁우진 학생");
                Serial.print("오늘은 ");
              Serial.print(number);
              Serial.println("번째 순서이시네요!");
                Serial.print("오늘의 주의식품 : ");
                for(int i=0; i<5; i++){
                  Serial.println(c[i]);
                  if(c[i] == NULL){
                    break;
                  }
                  break;
                  
                }
                
                Serial.println("--------------------------------------");
                
            } else if(str[0] == 226) {            
                Serial.println("유재하 학생");
                Serial.print("오늘은 ");
              Serial.print(number);
              Serial.println("번째 순서이시네요!");
                Serial.print("오늘의 주의식품 : ");
                for(int i=0; i<5; i++){
                  Serial.println(d[i]);
                  if(d[i] == NULL){
                    break;
                  }
                  break;
                  
                }
                 Serial.println("--------------------------------------");
               
            }
            number += 1; 

    
     if(str[0] == 42){
        number = 1;
        Serial.println("####################################");
        Serial.println("            순서 초기화");
        Serial.println("####################################");
        
     }

        Serial.println();
        delay(1000);  
            
    }
        myRFID.AddicoreRFID_Halt();             
}



