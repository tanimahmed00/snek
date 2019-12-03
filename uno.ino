#include <Servo.h>
#include <Pixy2.h>

Servo s1;
Servo s2;
Servo s3;
Servo s4;
Servo s5;
Servo s6;

Pixy2 snakeEyes;

//servo pins named differently than servo objects
int sp1 = 10;
int sp2 = 9;
int sp3 = 8;
int sp4 = 7;
int sp5 = 4;
int sp6 = 2;

//pins for the tails, r is for red b is for black. Red powered and black not should be forward motion
int t3r = 13;
int t3b = 12;
//now for the engaging pins
int t1 = 6;
int t3 = 5;
int t5 = 3;

//pins for communicating with dos
int ud = 11;
int du = A5;

//positions for the servos to be in
int pos1=90;
int pos2=45;
int pos3=135;

//ints to track servo
int sa1[] = {pos3,0};
int sa2[] = {pos1,0};
int sa3[] = {pos2,0};
int sa4[] = {pos1,1};
int sa5[] = {pos3,1};
int sa6[] = {pos1,0};

int startT = millis();

void setup() {
  s1.attach(sp1);
  s1.write(pos3);
  s2.attach(sp2);
  s2.write(pos1);
  s3.attach(sp3);
  s3.write(pos2);
  s4.attach(sp4);
  s4.write(pos1);
  s5.attach(sp5);
  s5.write(pos3);
  s6.attach(sp6);
  s6.write(pos1);
 
  //setting the motor controllers controlled by uno to max speed
  pinMode(t1, OUTPUT);
  analogWrite(t1, 255);
  pinMode(t3, OUTPUT);
  analogWrite(t3, 255);
  pinMode(t5, OUTPUT);
  analogWrite(t5, 255);

  //setting rest of pins to output
  pinMode(t3r, OUTPUT);
  pinMode(t3b, OUTPUT);
  pinMode(ud, OUTPUT);
}

void loop() {
  //create code for the entire shit to move
  forward();
}

void forward(){
  sa1 = wiggle(s1, sa1[0], sa1[1]);
  sa2 = wiggle(s2, sa2[0], sa2[1]);
  sa3 = wiggle(s3, sa3[0], sa3[1]);
  sa4 = wiggle(s4, sa4[0], sa4[1]);
  sa5 = wiggle(s5, sa5[0], sa5[1]);
  sa6 = wiggle(s6, sa6[0], sa6[1]);
  bounce(1,sa1[0],sa1[1]);
  bounce(2,sa2[0],sa2[1]);
  bounce(3,sa3[0],sa3[1]);
  bounce(4,sa4[0],sa4[1]);
  bounce(5,sa5[0],sa5[1]);
  bounce(6,sa6[0],sa6[1]);
}

int[] wiggle(Servo sv, int sa, int inc){
  if (sa<=45){
    sv.write(++sa);
    inc = 1;
  }else if (sa>=145){
    sv.write(--sa);
    inc = 0;
  }else if (inc == 1){
    sv.write(++sa);
  }else{
    sv.write(--sa);
  }
  return {sa,inc};
}

void bounce (int i, int ang, int inc){
  switch (i){
    case 1: if (ang>90)
            analogWrite(ud, inc == 0?16:32);
            else
            analogWrite(ud,48);
            break;
    case 2: if (ang>90)
            analogWrite(ud, inc == 0?64:80);
            else
            analogWrite(ud,96);
            break;
    case 3: if (ang>90){
              if (inc == 0){
                digitalWrite(t3r,HIGH);
                digitalWrite(t3b,LOW);
              }else{
                digitalWrite(t3r,LOW);
                digitalWrite(t3b,HIGH);
              }
            }else{
            digitalWrite(t3r,LOW);
            digitalWrite(t3b,LOW);
            }
            break;
    case 4: if (ang>90)
            analogWrite(ud, inc == 0?112:128);
            else
            analogWrite(ud,144);
            break;
    case 5: if (ang>90)
            analogWrite(ud, inc == 0?160:176);
            else
            analogWrite(ud,192);
            break;
    case 6: if (ang>90)
            analogWrite(ud, inc == 0?208:224);
            else
            analogWrite(ud,240);
    default: break;        
  }
}
