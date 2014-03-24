

//////////////////////////////////////////////////////////////////
//
//     B T T e r r a
//
//     main module
//
//     Rafał Zawadzki
//
//////////////////////////////////////////////////////////////////

char BT_CMDCHAR = '$';


#define DHTTYPE DHT22     // DHT 22  (AM2302)
#define DHTPIN 6          // pin sensora


#define BT_KEYPIN 10

class BTDevice{
  
  public:
  BTDevice(int id);
  int ID;
  int cT, cH;
  boolean p1, p2;  
};

BTDevice::BTDevice(int id)
{
 ID = id; 
}

// array
BTDevice *BT[8];

//----------------------------------------------------------------------

void setup() 
{
  init_BT();
}

void loop()
{
  readSensors();
  updateRelays();
  check_BT();  
}

void readSensors()
{
  BT[0]->cT = random(100);
  BT[0]->cH = random(50);
  BT[0]->p1 = random(2);
  BT[0]->p2 = random(2);
}

void updateRelays()
{
  //
}
