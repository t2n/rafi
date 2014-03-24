//////////////////////////////////////////////////////////////////
//
//     B T T e r r a
//
//     Bluetooth functions
//
//     Rafał Zawadzki
//
//////////////////////////////////////////////////////////////////

#define BT_KEYPIN 10
byte BT_DEVICESNO = 0;

void init_BT()
{
  // set the master/slave switch pin low (normal setup)
  digitalWrite(BT_KEYPIN, LOW); 
  Serial.begin(9600);
  Serial.println("^BTTerra");
  Serial.println("Available command(s):");
  Serial.println("$1 - get number of devices");
  Serial.print("$2;N - get data from device N#");
  
//  Serial.flush();
  BT[0] = new BTDevice(0);
}

// rodzaje przesyłanych informacji
// HC-06 <-> komputer
// ID odbiornika (musi być unikalne ID ale możliwe do rozpoznania)
// aktualne parametry (temperatura, wilgotność, stan przekaźników)
// konfiguracja (set i get)

// paczka podstawowych danych których ma żądać serwer:
// char buf[] = "ID;cT;cH;p1;p2"

void check_BT()
{
  if (Serial.available()>0)
  {
    char buf = Serial.read();

    if (buf==BT_CMDCHAR)
    {  
      int cmd = Serial.parseInt();
      
      switch (cmd)
      {
        case 1:
        Serial.print("^");
        Serial.print(BT_DEVICESNO+1);
        Serial.print(" urzadzenia#");
        break;      
        case 2:
        int dev_id = Serial.parseInt();
        if (dev_id <= BT_DEVICESNO)
        {
          Serial.print('^');
          Serial.print(BT[dev_id]->ID);
          Serial.print(';');
          Serial.print(BT[dev_id]->cT);
          Serial.print(';');
          Serial.print(BT[dev_id]->cH);
          Serial.print(';');
          Serial.print(BT[dev_id]->p1);
          Serial.print(';');
          Serial.print(BT[dev_id]->p2);
          Serial.print('#');
        } else Serial.println("^There is no such device.#");
        break;  
      }    
    }
    else
      Serial.write(buf);
    
  }
  Serial.flush();
}

void BT_scan()
{ 
 // put the BT into master mode by pulling pin to VCC
 // and sending proper command
 digitalWrite(BT_KEYPIN, HIGH);
 Serial.println("^AT+CMODE=0#");
 Serial.println("^AT+ROLE=1#"); 
 // look for other BT devices
 // next intructions to iclude:
 // AT+INIT (returns OK)
 // AT+INQ (returns:+INQ:4D65:4D:CA6612,5A0204,7FFF and OK)
 // AT+BIND=4D65,4D,CA6612 (returns OK)
 // AT+PAIR=4D65,4D,CA6612,30 (returns OK) 
 
 // if there is PC connect to it and ask for master device
 

}

/*
          bluetooth commands

1 AT 			Test UART Connection 
2 AT+RESET 		Reset Device 
3 AT+VERSION 		Querry ﬁrmware version 
4 AT+ORGL 		Restore settings to Factory Defaults 
5 AT+ADDR 		Query Device Bluetooth Address 
6 AT+NAME 		Query/Set Device Name 
7 AT+RNAME 		Query Remote Bluetooth Device’s Name 
8 AT+ROLE 		Query/Set Device Role 
9 AT+CLASS 		Query/Set Class of Device CoD
10 AT+IAC 		Query/Set Inquire Access Code 
11 AT+INQM 		Query/Set  Inquire Access Mode 
12 AT+PSWD 		Query/Set Pairing Passkey 
13 AT+UART 		Query/Set UART parameter 
14 AT+CMODE 		Query/Set Connection Mode 
15 AT+BIND 		Query/Set Binding Bluetooth Address 
16 AT+POLAR 		Query/Set LED Output Polarity 
17 AT+PIO 		Set/Reset a User I/O pin 
18 AT+MPIO 		Set/Reset multiple User I/O pin
19 AT+MPIO? 		Query User I/O pin 
20 AT+IPSCAN 		Query/Set Scanning Parameters 
21 AT+SNIFF 		Query/Set SNIFF Energy Savings Parameters 
22 AT+SENM 		Query/Set Security & Encryption Modes 
23 AT+RMSAD 		Delete Authenticated Device from List 
24 AT+FSAD 		Find Device from Authenticated Device List 
25 AT+ADCN 		Query Total Number of Device from Authenticated Device List
26 AT+MRAD 		Query Most Recently Used Authenticated Device
27 AT+STATE 		Query Current Status of the Device 
28 AT+INIT 		Initialize SPP Proﬁle 
29 AT+INQ 		Query Nearby Discoverable Devices 
30 AT+INQC 		Cancel Search for Discoverable Devices 
31 AT+PAIR 		Device Pairing 
32 AT+LINK 		Connect to a Remote Device 
33 AT+DISC 		Disconnect from a Remote Device 
34 AT+ENSNIFF 		Enter Energy Saving mode 
35 AT+EXSNIFF 		Exit Energy Saving mode

*/
