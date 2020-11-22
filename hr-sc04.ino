
const int trigger=8; 
const int echo=7; 
float dist;
 
void setup(){
  Serial.begin(9600);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
}

// CICLO PRINCIPAL 
void loop(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);         
  
  digitalWrite(trigger,HIGH);   
  delayMicroseconds(10);        
  digitalWrite(trigger,LOW);    
  
  dist=pulseIn(echo,HIGH);       
                                
                                
  dist = dist;               
                                
  Serial.print ("Distancia = " + dist);                        
  Serial.print (dist);          
  Serial.print ("cm");          
  Serial.write (10);            
  delay (200);                 
}                              
