#include <AddicoreRFID.h>
#include <SPI.h>
#define  uchar unsigned char
#define  uint  unsigned int
#define MAX_LEN 16

const int chipSelectPin = 10;
const int NRSTPD = 5;
const int speakerPin = 8;
 
uchar serNumA[5];
uchar fifobytes;
uchar fifoValue;
AddicoreRFID myRFID; 

int count = 0;

void setup() {   
  Serial.begin(9600);         
  SPI.begin();
  
  pinMode(chipSelectPin,OUTPUT); 
  pinMode(NRSTPD,OUTPUT);               
  digitalWrite(chipSelectPin, LOW);             
  digitalWrite(NRSTPD, HIGH);
 
  myRFID.AddicoreRFID_Init();  
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}
 
void loop()
{
  digitalWrite(7,HIGH);
  digitalWrite(6,LOW);
  uchar i, tmp, checksum1;
  uchar status;
  uchar str[MAX_LEN];
  uchar RC_size;
  uchar blockAddr;    
  String mynum = "";
  str[1] = 0x4400;
        
    status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);    
    if (status == MI_OK)  
    {
          tone(speakerPin,2000,100);
    }
    status = myRFID.AddicoreRFID_Anticoll(str);
    if (status == MI_OK)      
    {
       count  =  count + 1;
          checksum1 = str[0] ^ str[1] ^ str[2] ^ str[3];
          //Serial.print("The tag's number is  : ");
          //Serial.println(str[0]);
            if (status == MI_OK){
              tone(speakerPin,2000,100);
              digitalWrite(7,LOW);
              digitalWrite(6,HIGH);
              delay(500);
              digitalWrite(6,LOW);
              digitalWrite(7,HIGH);
            }
            
       if(str[0] == 102)                      
            {
               Serial.println("---------------------------------------------------");
               Serial.println("안녕하세요! 강신희님");
               Serial.print(count);
               Serial.println("번째 급식순서입니다!");
              add(0,14,22);
              add(NULL,NULL,55); 
              Serial.println("---------------------------------------------------"); 
            } else if(str[0] == 100) {      
              Serial.println("---------------------------------------------------");
              Serial.println("안녕하세요! 정갈렙님");  
              Serial.print(count);
              Serial.println("번째 급식순서입니다!"); 
              add(1,16,11); 
              Serial.println("---------------------------------------------------");    
            }  else if(str[0] == 195) {      
              Serial.println("---------------------------------------------------");
              Serial.println("안녕하세요! 김동현님");  
              Serial.print(count);
              Serial.println("번째 급식순서입니다!"); 
              add(1,15,NULL); 
              Serial.println("---------------------------------------------------");    
            } else if(str[0] == 42) {      
              count = 0;
             Serial.println("");
             Serial.println("############################");
             Serial.println("리셋완료");
             Serial.println("############################");
             Serial.println("");
            } 
            else if(str[0] == 35) {  
              for(int i=0; i <10; i++){
                Serial.println("배려대상자입니다. 먼저 먹도록 양보해주세요!");  
               tone(speakerPin,2000,100);
               delay(50);
               tone(speakerPin,2000,300);
               delay(50);
               tone(speakerPin,2000,100);
               delay(50);
              }
              Serial.println("");
              Serial.println("---------------------------------------------------");
              Serial.println("안녕하세요! 윤영우님");  
              Serial.print(count);
              Serial.println("번째 급식순서입니다!"); 
               
              add(1,16,33);
              add(NULL,NULL,44);  
              Serial.println("---------------------------------------------------");
            } 
            Serial.println();
            //Serial.println("");  
            Serial.println("***************************************************");
            Serial.println("***************************************************");
            delay(1000);
    }  
        myRFID.AddicoreRFID_Halt();      
                    
}

int add(int a, int b, int c)  
{
  if(a == 1){
    if(b == 14){
      add_2(2650,50);
       Serial.println("당신(14세,남자)의 표준 칼로리는 2650kacl입니다.");
       Serial.println("당신(14세,남자)의 표준 단백질은 50g입니다.");
    }
    if(b == 15){
       add_2(2700,55);
       Serial.println("당신(15세,남자)의 표준 칼로리는 2700kacl입니다.");
       Serial.println("당신(15세,남자)의 표준 단백질은 55g입니다.");
    }
    if(b == 16){
       add_2(2750,55);
       Serial.println("당신(16세,남자)의 표준 칼로리는 2750kacl입니다.");
       Serial.println("당신(16세,남자)의 표준 단백질은 55g입니다.");
    }
  }
/////////
  if(a == 0){
    if(b == 14){
      add_2(2300,45);
       Serial.println("당신(14세,여자)의 표준 칼로리는 2300kacl입니다.");
       Serial.println("당신(14세,여자)의 표준 단백질은 45g입니다.");
    }
    if(b == 15){
       add_2(2300,45);
        Serial.println("당신(15세,여자)의 표준 칼로리는 2300kacl입니다.");
        Serial.println("당신(15세,여자)의 표준 단백질은 45g입니다.");
    }
    if(b == 16){
       add_2(2250,45);
        Serial.println("당신(16세,여자)의 표준 칼로리는 2250kacl입니다.");
        Serial.println("당신(16세,여자)의 표준 단백질은 45g입니다.");
    }
  }
  Serial.println("---------------------------------------------------");  
  Serial.print("오늘 알레르기 주의 식품: ");
  if(c == 11){
    Serial.println("갑각류");
  }if(c == 22){
    Serial.println("콩류"); 
  }if(c == 33){
    Serial.println("생선류");
  }if(c == 44){
    Serial.println("견과류"); 
  }if(c == 55){
    Serial.println("우유");
  }if(c == 66){
    Serial.println("곡류"); 
  }if(c == NULL){
    Serial.println("없음"); 
  }
  
}
int add_2(float  a, float  b)
{
  Serial.println("---------------------------------------------------");  
  Serial.println("###오늘의 식단###");
  Serial.println("돼지고기덮밥");
  Serial.println("해물탕");
  Serial.println("단호박고구마범벅");
  Serial.println("깍두기");
  Serial.println("견과샐러드");
  Serial.println("---------------------------------------------------");  
  float  today_kcal = 510.2;
  float  today_dan = 19.7;
  float c= 0; 
  float  g = 0;
  c= today_kcal*100/a;
  g= today_dan*100/b;
  
  Serial.print("권장 칼로리의 ");
  Serial.print(c);
  Serial.print("% 섭취하셨습니다.");
  Serial.print("(");
  Serial.print(today_kcal);
  Serial.print("Kcal");
  Serial.println(")");
  
  Serial.print("권장 단백질의 ");
  Serial.print(g);
  Serial.print("% 섭취하셨습니다.");
  Serial.print("(");
  Serial.print(today_dan);
  Serial.print("g");
  Serial.println(")");
   Serial.println("");
}
