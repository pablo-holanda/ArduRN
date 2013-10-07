
char serialByte;

    void setup() 
    {
      Serial.begin(115200);
    }
    
    void loop() 
    {     
       while (Serial.available()>0)
      {  
       serialByte=Serial.read();
        
            
          if (serialByte == 'p')
              {
                 Serial.println("666");
               }  
  
      }
  }
  

