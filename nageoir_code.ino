
/*
 * fish_sweep v 0.2
 * роборыба: плаваем прямо и переиодически пытаемся поворачивать
 *
 * http://robocraft.ru
 */

// отладка
#define MY_DEBUG 1

// задерка по-умолчанию (определяет скорость)
#define DEFAULT_DELAY 10

#include <Servo.h> 

// типа класс робота
struct RoboFishs
{
  // у робота есть серва, которая машет хвостом
  Servo tail;
  // переменная для хранения положения сервомашинки
  int pos;
  
  // положения сервомашинки между которыми нужно "махать хвостом" 
  int pos_0;
  int pos_1;

  int speed;

  void setup(int servo_pin)
  {
    pos = 0;
    speed = 100;
    
    pos_0 = 1;
    pos_1 = 180;

    tail.attach(servo_pin);
  }
  
  
  int set_speed(int _speed=0)
  {
    int res = DEFAULT_DELAY;
    
    if(_speed > 0) {
      res = 1000/_speed;
    }
    
    return res;
  }

  void swim(int _speed=0)
  {
    int del = set_speed(_speed);

// переделываем пример Sweep
    for(pos = pos_0; pos < pos_1; pos++) {
      tail.write(pos);             
      delay(del);
    }
#if MY_DEBUG
      Serial.println("<");
#endif    
    for(pos = pos_1; pos >= pos_0; pos--) {                                
      tail.write(pos);
      delay(del);
    }
#if MY_DEBUG
      Serial.println(">");
#endif    
  }
  
  void forward(int _speed=0)
  {
#if MY_DEBUG
      Serial.println("forward");
#endif

    pos_0 = 45;
    pos_1 = 125;
    
    swim(_speed);
  }
  
  void left(int _speed=0)
  {
#if MY_DEBUG
      Serial.println("left");
#endif
    
    pos_0 = 20;
    pos_1 = 60;
    
    swim(_speed);
  }
  
  void right(int _speed=0)
  {
#if MY_DEBUG
      Serial.println("right");
#endif    
    
    pos_0 = 120;
    pos_1 = 160;
    
    swim(_speed);
  }  
};

RoboFishs robot;  // наш робот

int randnum = 0;
bool leftflag = false;
bool rightflag = false;

void setup() 
{ 
#if MY_DEBUG
  Serial.begin(9600);
#endif

  robot.setup(8);
  robot.speed = 25;

  // инициализация ГПСЧ
  randomSeed(analogRead(0));
} 


void loop() 
{
#if 0  
// тестирование

  robot.right(50);

#endif

#if 0
// плаваем только прямо (подбор оптимальных углов)
  robot.pos_0 = 55;//65
  robot.pos_1 = 115;//105
  robot.swim( robot.speed+40 ); 
#endif

#if 1
// плаваем прямо и периодически пытаемся поворачивать
  randnum = random(400);
  if(randnum > 380) {
    
    randnum = random(400);
    if(randnum > 200 && !rightflag)
    {
      leftflag=true;
      robot.left(robot.speed);   
    }
    else
    {
      rightflag=true;
      robot.right(robot.speed);  
    }
  }
  else {
    leftflag = false;
    rightflag = false;
    //robot.forward( robot.speed );  
    robot.pos_0 = 70;
    robot.pos_1 = 100;
    robot.swim( robot.speed+100 );
  }
#endif  
}
